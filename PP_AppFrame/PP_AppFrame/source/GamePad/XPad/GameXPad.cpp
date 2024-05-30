#include "GameXPad.h"

GameXPad::GameXPad()
{
	//������
	for (int i = 0; i < MAX_PAD_BUTTON; i++)
	{
		_xTrg[i] = 0;
		_xRel[i] = 0;
	}
	_xTrgRt = 0;
	_xTrgLt = 0;
	_xRelRt = 0;
	_xRelLt = 0;
}

GameXPad::~GameXPad()
{
}

bool GameXPad::Input()
{
	//�L�[,�g���K�̕ϐ�
	uchar key_old[MAX_PAD_BUTTON];
	uchar trg_r_old = _xInput.RightTrigger;
	uchar trg_l_old = _xInput.LeftTrigger;
	for (int i = 0; i < MAX_PAD_BUTTON; i++)
	{
		//���[�J���ϐ��ɑ��
		key_old[i] = _xInput.Buttons[i];
	}
	//XInput���瓾������̑��
	GetJoypadXInputState(DX_INPUT_PAD1, &_xInput);
	//�g���K�A�����[�X�L�[�̍쐬
	for (int i = 0; i < MAX_PAD_BUTTON; i++)
	{
		_xTrg[i] = (_xInput.Buttons[i] ^ key_old[i]) & _xInput.Buttons[i];
		_xRel[i] = (_xInput.Buttons[i] ^ key_old[i]) & ~_xInput.Buttons[i];
	}
	_xTrgRt = (_xInput.RightTrigger ^ trg_r_old) & _xInput.RightTrigger;
	_xTrgLt = (_xInput.LeftTrigger ^ trg_l_old) & _xInput.LeftTrigger;
	_xRelRt = (_xInput.RightTrigger ^ trg_r_old) & ~_xInput.RightTrigger;
	_xRelLt = (_xInput.LeftTrigger ^ trg_l_old) & ~_xInput.LeftTrigger;
	return true;
}

bool GameXPad::IsInputStick(int i) 
{
	//�A�i���O�X�e�B�b�N����������Ă���Ȃ�true
	if (_xInput.ThumbLX || _xInput.ThumbLY != 0) { return true; }
	return false;
}
