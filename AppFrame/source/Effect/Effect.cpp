#include "Effect.h"

Effect::Effect(std::string handle, float size)
{
	//�ʒu
	_pos = Vector3D(0, 0, 0);
	//�T�C�Y
	_size = size;
	//����
	_dir = Vector3D(0, 0, 0);
	//�n���h���̃��[�h
	_effectHandle = LoadEffekseerEffect(handle.c_str(), _size);
	//�Đ��\�t���O��true��
	_useFlag = true;
	//�Đ����t���O��false��
	_playFlag = false;
	//�ʒu�̍X�V
	SetPosEffekseer(_playHandle, _pos);
}

Effect::~Effect()
{
	//�G�t�F�N�g���\�[�X�̍폜
	DeleteEffekseerEffect(_effectHandle);
}

void Effect::SetPosEffekseer(int playhandle, Vector3D& pos)
{
	SetPosPlayingEffekseer3DEffect(playhandle, pos._x, pos._y, pos._z);
}

void Effect::SetDirEffekseer(int playhandle, Vector3D& dir)
{
	SetRotationPlayingEffekseer3DEffect(playhandle, dir._x, dir._y, dir._z);
}

bool Effect::Play()
{
	//�Đ��\�Ȃ�G�t�F�N�g�̍Đ�
	if (_useFlag) { _playHandle = PlayEffekseer3DEffect(_effectHandle); }
	//�Đ����Ȃ�Đ����t���O��true��
	if (_playHandle != -1) { _playFlag = true; }
	return true;
}

bool Effect::Stop()
{
	//�Đ��̒�~
	StopEffekseer3DEffect(_playHandle);
	return true;
}

bool Effect::Process()
{
	//�ʒu�̍X�V
	SetPosEffekseer(_playHandle, _pos);
	//�p�x�̍X�V
	SetDirEffekseer(_playHandle, _dir);
	return true;
}

bool Effect::Draw()
{
	//�G�t�F�N�g�̕`��
	DrawEffekseer3D();
	return true;
}

bool Effect::Update()
{
	//DX���C�u�����̃J������Effekseer�J�����̓���
	Effekseer_Sync3DSetting();
	//Effekseer�X�V
	UpdateEffekseer3D();
	return true;
}


