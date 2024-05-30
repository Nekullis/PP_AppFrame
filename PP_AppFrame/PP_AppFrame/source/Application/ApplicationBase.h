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
	//�Q�b�^�[
	static ApplicationBase* GetInstance() { return _appInstance; }
	virtual bool AppWindowed() { return true; }
//�f�o�b�O���ƃ����[�X���ŉ�ʃT�C�Y��ύX
#if _DEBUG
	int DispSizeW() { return 1280; }
	int DispSizeH() { return 720; }
#else
	int DispSizeW() { return 1920; }
	int DispSizeH() { return 1080; }
#endif
protected:
	//�C���X�^���X
	static ApplicationBase* _appInstance;
	//���j�[�N�|�C���^��p���ď�����
	std::unique_ptr<ModeServer> _server;
};

