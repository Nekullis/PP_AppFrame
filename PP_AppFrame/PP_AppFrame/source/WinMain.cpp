#include "Application/ApplicationBase.h"
//#include "AppFrame.h"
//WinMain : プログラム起動関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ApplicationBase* app_base = ApplicationBase::GetInstance();
	if (!app_base) { return 0; }
	if (!app_base->Initialize(hInstance)) { return 0; }
	//1フレームループを組む
	while (ProcessMessage() == 0)
	{
		app_base->Input();
		app_base->Process();
		//画面初期化
		ClearDrawScreen();
		app_base->Render();
		//裏画面の内容を表画面に反映
		ScreenFlip();
	}
	app_base->Terminate();
	return 0;
}