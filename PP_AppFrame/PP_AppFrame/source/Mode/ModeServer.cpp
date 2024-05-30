#include "ModeServer.h"
ModeServer* ModeServer::_sevInstance = nullptr;
ModeServer::ModeServer()
{
	_sevInstance = this;
	_uidCnt = 1;
	_nowMode = nullptr;
	_skipProcessMode = nullptr;
	_skipRenderMode = nullptr;
	_pauseProcessMode = nullptr;
}

ModeServer::~ModeServer()
{
	Clear();
	_sevInstance = nullptr;
}

int ModeServer::Add(ModeBase* mode, int layer, const char* name)
{
	_vModeAdd.push_back(mode);
	mode->_uid = _uidCnt;
	_uidCnt++;
	mode->_layer = layer;
	mode->_sName = name;
	return mode->_uid;
}

int ModeServer::Del(ModeBase* mode)
{
	_vModeDel.push_back(mode);
	return 0;
}

int ModeServer::Release(ModeBase* mode)
{
	_listMode::iterator itr = _vMode.begin();
	for (; itr != _vMode.end();)
	{
		if ((*itr) == mode)
		{
			(*itr)->Terminate();
			delete (*itr);
			itr = _vMode.erase(itr);
		}
		else { ++itr; }
	}
	return 1;
}

void ModeServer::Clear()
{
	//逆イテレータ取得
	_listMode::reverse_iterator itr = _vMode.rbegin();
	for (; itr != _vMode.rend(); ++itr)
	{
		(*itr)->Terminate();
		delete (*itr);
	}
	//イテレータ取得
	_listMode::iterator itr_add = _vModeAdd.begin();
	for (; itr_add != _vModeAdd.end(); ++itr_add)
	{
		(*itr_add)->Terminate();
		delete (*itr_add);
	}
	//各コンテナのクリア
	_vMode.clear();
	_vModeAdd.clear();
	_vModeDel.clear();
}

bool ModeServer::IsDelRegist(ModeBase* mode)
{
	//削除予約されているか
	if (_vModeDel.size() > 0)
	{
		_listMode::iterator itr_del = _vModeDel.begin();
		for (; itr_del != _vModeDel.end(); ++itr_del)
		{
			if ((*itr_del) == mode) { return true; }
		}
	}
	return false;
}

bool ModeServer::IsAdd(ModeBase* mode)
{
	//モードリストの中に入っているか
	_listMode::iterator itr;
	itr = _vMode.begin();
	for (; itr != _vMode.end(); ++itr)
	{
		if (!IsDelRegist((*itr)) && (*itr) == mode) { return true; }
	}
	itr = _vModeAdd.begin();
	for (; itr != _vModeAdd.end(); ++itr)
	{
		if (!IsDelRegist((*itr)) && (*itr) == mode) { return true; }
	}
	return false;
}

ModeBase* ModeServer::Get(int uid)
{
	_listMode::iterator ite;
	ite = _vMode.begin();
	for (; ite != _vMode.end(); ++ite) {
		if (!IsDelRegist((*ite)) && (*ite)->_uid == uid) { return (*ite); }
	}
	ite = _vModeAdd.begin();
	for (; ite != _vModeAdd.end(); ++ite) {
		if (!IsDelRegist((*ite)) && (*ite)->_uid == uid) { return (*ite); }
	}
	return nullptr;
}

ModeBase* ModeServer::Get(const char* name)
{
	_listMode::iterator ite;
	ite = _vMode.begin();
	for (; ite != _vMode.end(); ++ite) {
		if (!IsDelRegist((*ite)) && (*ite)->_sName == name) { return (*ite); }
	}
	ite = _vModeAdd.begin();
	for (; ite != _vModeAdd.end(); ++ite) {
		if (!IsDelRegist((*ite)) && (*ite)->_sName == name) { return (*ite); }
	}
	return nullptr;
}

int ModeServer::GetID(ModeBase* mode)
{
	if (IsAdd(mode)) { return mode->_uid; }
	return 0;
}

const char* ModeServer::GetName(ModeBase* mode)
{
	if (IsAdd(mode)) { return mode->_sName.c_str(); }
	return nullptr;
}
//プロセスに関する処理
int ModeServer::ProcessInit()
{
	//削除予約されていたものを削除
	if (_vModeDel.size() > 0)
	{
		_listMode::iterator itr = _vModeDel.begin();
		for (; itr != _vModeDel.end(); ++itr) { Release((*itr)); }
		_vModeDel.clear();
	}
	//登録予約されているモードを有効にする
	if (_vModeAdd.size() > 0)
	{
		_listMode::iterator itr = _vModeAdd.begin();
		for (; itr != _vModeAdd.end(); ++itr)
		{
			(*itr)->Initialize();
			_vMode.push_back((*itr));
		}
		_vModeAdd.clear();
		//レイヤーによるソート
		_vMode.sort(ModeSort);
	}
	//スキップとポーズの解除
	_skipProcessMode = NULL;
	_skipRenderMode = NULL;
	_pauseProcessMode = NULL;
	return 0;
}

int ModeServer::Process()
{
	unsigned int t = GetNowCount();
	bool pause = false;
	//レイヤーの上から処理
	_listMode::reverse_iterator itr = _vMode.rbegin();
	for (; itr != _vMode.rend(); ++itr)
	{
		if (!IsDelRegist(*itr))
		{
			_nowMode = (*itr);
			if (!pause) { (*itr)->StepTime(t); }
		}
		//processコール
		(*itr)->Process();
		//モードがない場合
		if (_vMode.empty())
		{
			break;
		}
		if (!pause) { (*itr)->StepCount(); }
		if (_skipProcessMode == (*itr)) { break; }
		if (_pauseProcessMode == (*itr)) { pause = true; }
	}
	_nowMode = NULL;
	return 0;
}

int ModeServer::ProcessFinish()
{
	return 0;
}

int ModeServer::RenderInit()
{
	return 0;
}

int ModeServer::Render()
{
	_listMode::iterator itr = _vMode.begin();
	for (; itr != _vMode.end(); ++itr)
	{
		if (_skipRenderMode && _skipRenderMode != (*itr)) { continue; }
		_skipRenderMode = NULL;
		if (!IsDelRegist(*itr))
		{
			_nowMode = (*itr);
			(*itr)->Render();
		}
	}
	_nowMode = NULL;
	return 0;
}

int ModeServer::RenderFinish()
{
	
	return 0;
}

int ModeServer::SkipProcessUnderLayer()
{
	_skipProcessMode = _nowMode;
	return 0;
}

int ModeServer::SkipRenderUnderLayer()
{
	_skipRenderMode = _nowMode;
	return 0;
}

int ModeServer::PauseProcessUnderLayer()
{
	_pauseProcessMode = _nowMode;
	return 0;
}

