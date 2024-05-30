#pragma once
#include "dxlib.h"
//�萔
constexpr auto MAX_PAD_BUTTON = 16;
using uchar = unsigned char;
//XPad�{�^���̒��g
// 0  XINPUT_BUTTON_DPAD_UP
// 1  XINPUT_BUTTON_DPAD_DOWN
// 2  XINPUT_BUTTON_DPAD_LEFT
// 3  XINPUT_BUTTON_DPAD_RIGHT
// 4  XINPUT_BUTTON_START
// 5  XINPUT_BUTTON_BACK
// 6  XINPUT_BUTTON_LEFT_THUMB
// 7  XINPUT_BUTTON_RIGHT_THUMB
// 8  XINPUT_BUTTON_LEFT_SHOULDER
// 9  XINPUT_BUTTON_RIGHT_SHOULDER
// 10 XINPUT_BUTTON
// 11 XINPUT_BUTTON
//   (10,11��DX���C�u�����ɂ͋L�ڂ���Ă��Ȃ�)
// 12 XINPUT_BUTTON_A
// 13 XINPUT_BUTTON_B
// 14 XINPUT_BUTTON_X
// 15 XINPUT_BUTTON_Y

//X�C���v�b�g�^�C�v�̃Q�[���p�b�h�N���X
class GameXPad
{
public:
	GameXPad();
	~GameXPad();
	bool Input();
	//���͂���Ă��邩
	bool IsInputStick(int i);
	//�Q�b�^�[
	//�{�^��
	bool GetXKey(int index) { return _xInput.Buttons[index]; }
	bool GetXTrg(int index) { return _xTrg[index]; }
	bool GetXRel(int index) { return _xRel[index]; }
	//�A�i���O�p�b�h
	short GetXRx() { return _xInput.ThumbRX; }
	short GetXRy() { return _xInput.ThumbRY; }
	short GetXLx() { return _xInput.ThumbLX; }
	short GetXLy() { return _xInput.ThumbLY; }
	//�g���K
	uchar GetXRt() { return _xInput.RightTrigger; }
	uchar GetXLt() { return _xInput.LeftTrigger; }
	uchar GetXTrgRt() { return _xTrgRt; }
	uchar GetXTrgLt() { return _xTrgLt; }
	uchar GetXRelRt() { return _xRelRt; }
	uchar GetXRelLt() { return _xRelLt; }

protected:
	//X�C���v�b�g
	XINPUT_STATE _xInput;
	//�{�^��(�g���K)
	int _xTrg[MAX_PAD_BUTTON];
	//�{�^��(�����[�X)
	int _xRel[MAX_PAD_BUTTON];
	//�E�g���K
	int _xTrgRt;
	//���g���K
	int _xTrgLt;
	//�E�����[�X
	int _xRelRt;
	//�������[�X
	int _xRelLt;

};

