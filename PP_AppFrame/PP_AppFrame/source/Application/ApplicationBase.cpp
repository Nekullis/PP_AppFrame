#include "ApplicationBase.h"
ApplicationBase* ApplicationBase::_appInstance = nullptr;
ApplicationBase::ApplicationBase()
{
	_appInstance = this;
}

ApplicationBase::~ApplicationBase()
{

}

bool ApplicationBase::Initialize(HINSTANCE hincetance)
{
	if (AppWindowed()) { ChangeWindowMode(true); }
	SetGraphMode(DispSizeW(), DispSizeH(), 32);
	//距離が近いところでちらつきが発生することを防ぐため
	SetZBufferBitDepth(32);
	//ログテキストの出力
#if _DEBUG
	SetOutApplicationLogValidFlag(true);
#else
	SetOutApplicationLogValidFlag(false);
#endif
	//エラーが起きた際に直ちに終了出来るように
	if (DxLib_Init() == -1) { return false; }
	//エフェクシア用
	if (Effekseer_Init(20000) == -1)
	{
		DxLib_End();
		return -1;
	}
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	//描画先画面を裏画面に
	SetDrawScreen(DX_SCREEN_BACK);
	//乱数初期化
	srand((unsigned)time(NULL));
	//モードサーバー初期化
	//unique_ptrをnewする際はmake_unique<>を使う
	_server = std::make_unique<ModeServer>();
	return true;
}

bool ApplicationBase::Terminate()
{
	Effkseer_End();
	DxLib_End();
	return true;
}

bool ApplicationBase::Input()
{
	return true;
}

bool ApplicationBase::Process()
{
	_server->ProcessInit();
	_server->Process();
	_server->ProcessFinish();
	return true;
}

bool ApplicationBase::Render()
{
	_server->RenderInit();
	_server->Render();
	_server->RenderFinish();
	return true;
}
