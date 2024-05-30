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
	//�t�C�e���[�^�擾
	_listMode::reverse_iterator itr = _vMode.rbegin();
	for (; itr != _vMode.rend(); ++itr)
	{
		(*itr)->Terminate();
		delete (*itr);
	}
	//�C�e���[�^�擾
	_listMode::iterator itr_add = _vModeAdd.begin();
	for (; itr_add != _vModeAdd.end(); ++itr_add)
	{
		(*itr_add)->Terminate();
		delete (*itr_add);
	}
	//�e�R���e�i�̃N���A
	_vMode.clear();
	_vModeAdd.clear();
	_vModeDel.clear();
}

bool ModeServer::IsDelRegist(ModeBase* mode)
{
	//�폜�\�񂳂�Ă��邩
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
	//���[�h���X�g�̒��ɓ����Ă��邩
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
//�v���Z�X�Ɋւ��鏈��
int ModeServer::ProcessInit()
{
	//�폜�\�񂳂�Ă������̂��폜
	if (_vModeDel.size() > 0)
	{
		_listMode::iterator itr = _vModeDel.begin();
		for (; itr != _vModeDel.end(); ++itr) { Release((*itr)); }
		_vModeDel.clear();
	}
	//�o�^�\�񂳂�Ă��郂�[�h��L���ɂ���
	if (_vModeAdd.size() > 0)
	{
		_listMode::iterator itr = _vModeAdd.begin();
		for (; itr != _vModeAdd.end(); ++itr)
		{
			(*itr)->Initialize();
			_vMode.push_back((*itr));
		}
		_vModeAdd.clear();
		//���C���[�ɂ��\�[�g
		_vMode.sort(ModeSort);
	}
	//�X�L�b�v�ƃ|�[�Y�̉���
	_skipProcessMode = NULL;
	_skipRenderMode = NULL;
	_pauseProcessMode = NULL;
	return 0;
}

int ModeServer::Process()
{
	unsigned int t = GetNowCount();
	bool pause = false;
	//���C���[�̏ォ�珈��
	_listMode::reverse_iterator itr = _vMode.rbegin();
	for (; itr != _vMode.rend(); ++itr)
	{
		if (!IsDelRegist(*itr))
		{
			_nowMode = (*itr);
			if (!pause) { (*itr)->StepTime(t); }
		}
		//process�R�[��
		(*itr)->Process();
		//���[�h���Ȃ��ꍇ
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

