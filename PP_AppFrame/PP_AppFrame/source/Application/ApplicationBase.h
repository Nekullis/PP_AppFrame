#pragma once
#include <stdio.h>
#include <time.h>
#include "dxlib.h"
#include "EffekseerForDXLib.h"
#include "../Mode/ModeServer.h"
class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();
	virtual bool Initialize(HINSTANCE hincetance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();
	//ゲッター
	static ApplicationBase* GetInstance() { return _appInstance; }
	virtual bool AppWindowed() { return true; }
//デバッグ時とリリース時で画面サイズを変更
#if _DEBUG
	int DispSizeW() { return 1280; }
	int DispSizeH() { return 720; }
#else
	int DispSizeW() { return 1920; }
	int DispSizeH() { return 1080; }
#endif
protected:
	//インスタンス
	static ApplicationBase* _appInstance;
	//ユニークポインタを用いて初期化
	std::unique_ptr<ModeServer> _server;
};

