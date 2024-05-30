#include "Application/ApplicationBase.h"
//#include "AppFrame.h"
//WinMain : �v���O�����N���֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ApplicationBase* app_base = ApplicationBase::GetInstance();
	if (!app_base) { return 0; }
	if (!app_base->Initialize(hInstance)) { return 0; }
	//1�t���[�����[�v��g��
	while (ProcessMessage() == 0)
	{
		app_base->Input();
		app_base->Process();
		//��ʏ�����
		ClearDrawScreen();
		app_base->Render();
		//����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}
	app_base->Terminate();
	return 0;
}