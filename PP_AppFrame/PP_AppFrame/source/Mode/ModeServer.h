#pragma once
#include <list>
#include "ModeBase.h"
#include "DxLib.h"
class ModeServer
{
	using _listMode = std::list<ModeBase*>;
public:
	ModeServer();
	virtual ~ModeServer();
	static ModeServer* _sevInstance;
	static ModeServer* GetInstance() { return (ModeServer*)_sevInstance; }
	//登録予約
	int Add(ModeBase* mode, int layer, const char* name);
	//削除予約
	int Del(ModeBase* mode);
	//モードの取得
	ModeBase* Get(int uid);
	ModeBase* Get(const char* name);
	//モードID取得
	int GetID(ModeBase* mode);
	//モード名取得
	const char* GetName(ModeBase* mode);
	void Clear();
	static bool ModeSort(const ModeBase* x, const ModeBase* y) { return x->_layer < y->_layer; }
	//ゲッター
	int LayerTop() { return INT32_MAX; }
	int GetID(const char* name) { return GetID(Get(name)); }
	const char* GetName(int uid) { return GetName(Get(uid)); }
	//プロセスを回すための初期化
	int ProcessInit();
	//レイヤーの上から処理
	int Process();
	//プロセスを回した後の後始末
	int ProcessFinish();
	//描画を回すための初期化
	int RenderInit();
	//レイヤーの下から処理
	int Render();
	//描画を回した後の後始末
	int RenderFinish();
	//現processで今処理しているレイヤーより下のレイヤーは処理を呼ばない
	int SkipProcessUnderLayer();
	//現processで今処理しているレイヤーより下のレイヤーは描画を呼ばない
	int SkipRenderUnderLayer();
	//現processで今処理しているレイヤーより下のレイヤーは経過時間を止める
	int PauseProcessUnderLayer();
private:
	//削除&delete
	int Release(ModeBase* mode);
	//削除予約されているか
	bool IsDelRegist(ModeBase* mode);
	//リストにあるか
	bool IsAdd(ModeBase* mode);
	//モードリスト
	_listMode _vMode;
	//追加予約
	_listMode _vModeAdd;
	//削除予約
	_listMode _vModeDel;
	//uidカウンタ
	int _uidCnt;
	//現在呼び出し中のモード
	ModeBase* _nowMode;
	//このモードより下はprocessを呼ばない
	ModeBase* _skipProcessMode;
	//このモードより下はrenderを呼ばない
	ModeBase* _skipRenderMode;
	// このモードより下はProcess時に時間経過をさせない
	ModeBase* _pauseProcessMode;

};

