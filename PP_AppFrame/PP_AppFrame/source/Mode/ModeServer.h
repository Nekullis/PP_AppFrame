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
	//�o�^�\��
	int Add(ModeBase* mode, int layer, const char* name);
	//�폜�\��
	int Del(ModeBase* mode);
	//���[�h�̎擾
	ModeBase* Get(int uid);
	ModeBase* Get(const char* name);
	//���[�hID�擾
	int GetID(ModeBase* mode);
	//���[�h���擾
	const char* GetName(ModeBase* mode);
	void Clear();
	static bool ModeSort(const ModeBase* x, const ModeBase* y) { return x->_layer < y->_layer; }
	//�Q�b�^�[
	int LayerTop() { return INT32_MAX; }
	int GetID(const char* name) { return GetID(Get(name)); }
	const char* GetName(int uid) { return GetName(Get(uid)); }
	//�v���Z�X���񂷂��߂̏�����
	int ProcessInit();
	//���C���[�̏ォ�珈��
	int Process();
	//�v���Z�X���񂵂���̌�n��
	int ProcessFinish();
	//�`����񂷂��߂̏�����
	int RenderInit();
	//���C���[�̉����珈��
	int Render();
	//�`����񂵂���̌�n��
	int RenderFinish();
	//��process�ō��������Ă��郌�C���[��艺�̃��C���[�͏������Ă΂Ȃ�
	int SkipProcessUnderLayer();
	//��process�ō��������Ă��郌�C���[��艺�̃��C���[�͕`����Ă΂Ȃ�
	int SkipRenderUnderLayer();
	//��process�ō��������Ă��郌�C���[��艺�̃��C���[�͌o�ߎ��Ԃ��~�߂�
	int PauseProcessUnderLayer();
private:
	//�폜&delete
	int Release(ModeBase* mode);
	//�폜�\�񂳂�Ă��邩
	bool IsDelRegist(ModeBase* mode);
	//���X�g�ɂ��邩
	bool IsAdd(ModeBase* mode);
	//���[�h���X�g
	_listMode _vMode;
	//�ǉ��\��
	_listMode _vModeAdd;
	//�폜�\��
	_listMode _vModeDel;
	//uid�J�E���^
	int _uidCnt;
	//���݌Ăяo�����̃��[�h
	ModeBase* _nowMode;
	//���̃��[�h��艺��process���Ă΂Ȃ�
	ModeBase* _skipProcessMode;
	//���̃��[�h��艺��render���Ă΂Ȃ�
	ModeBase* _skipRenderMode;
	// ���̃��[�h��艺��Process���Ɏ��Ԍo�߂������Ȃ�
	ModeBase* _pauseProcessMode;

};

