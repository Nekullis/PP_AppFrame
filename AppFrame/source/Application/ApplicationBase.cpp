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
	//�������߂��Ƃ���ł�������������邱�Ƃ�h������
	SetZBufferBitDepth(32);
	//���O�e�L�X�g�̏o��
#if _DEBUG
	SetOutApplicationLogValidFlag(true);
#else
	SetOutApplicationLogValidFlag(false);
#endif
	//�G���[���N�����ۂɒ����ɏI���o����悤��
	if (DxLib_Init() == -1) { return false; }
	//�G�t�F�N�V�A�p
	if (Effekseer_Init(20000) == -1)
	{
		DxLib_End();
		return -1;
	}
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	//�`����ʂ𗠉�ʂ�
	SetDrawScreen(DX_SCREEN_BACK);
	//����������
	srand((unsigned)time(NULL));
	//���[�h�T�[�o�[������
	//unique_ptr��new����ۂ�make_unique<>���g��
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
