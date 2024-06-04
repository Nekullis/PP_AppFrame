#pragma once
#include "../Vector3D/Vector3D.h"
#include "EffekseerForDXLib.h"
#include <string>
//Effekseer��p�����G�t�F�N�g�N���X
class Effect
{
public:
	Effect(std::string handle,float size);
	~Effect();
	//�Đ�
	bool Play();
	//��~
	bool Stop();
	//�v���Z�X
	bool Process();
	//�`��
	bool Draw();
	//�A�b�v�f�[�g
	//���̊֐��͉�����Ăяo���K�v�͂Ȃ����߃}�l�[�W���[���邢�̓Q�[�����C���֐���
	bool Update();
	//Effekseer�֐����g���₷������悤��
	void SetPosEffekseer(int playhandle, Vector3D& pos);
	void SetDirEffekseer(int playhandle, Vector3D& dir);
	//�Q�b�^�[
	bool GetUseFlag()  const { return _useFlag; }
	bool GetPlayFlag() const { return _playFlag; }
	//�Z�b�^�[
	void SetPos(const Vector3D& v)	{ _pos = v; }
	void SetSize(const float s)		{ _size = s; }
	void SetDir(const Vector3D& v)	{ _dir = v; }
	void SetUseFlag(bool f)			{ _useFlag = f; }
protected:
	//���[�h�n���h��
	int _effectHandle;
	//�Đ��n���h��
	int _playHandle;
	//�ʒu
	Vector3D _pos;
	//�T�C�Y
	float _size;
	//����
	Vector3D _dir;
	//�Đ��\�t���O
	bool _useFlag;
	//�Đ����t���O
	bool _playFlag;

};

