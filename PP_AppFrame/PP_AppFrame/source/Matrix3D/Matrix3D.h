#pragma once
#include "DxLib.h"
#include "../Vector3D/Vector3D.h"
#include <math.h>
//3D�ɂ�����s��֘A�̃N���X
class Matrix3D
{
public:
	Matrix3D();
	~Matrix3D();
	Matrix3D Ident(Matrix3D& m);
	//�I�y���[�^�I�[�o�[���[�h
	Matrix3D  operator+=(const Matrix3D& right);
	Matrix3D  operator*=(const Matrix3D& right);
	bool      operator==(const Matrix3D& right);
	bool      operator!=(const Matrix3D& right);
	//DX���C�u������MATRIX���g����悤��
	Matrix3D& operator= (const MATRIX& right);
	//matrix�v�Z����
	//�X�P�[�����O
	Matrix3D  MScale(Matrix3D m, double d);
	//�x�N�g���ɂ��g��k��
	Matrix3D  MGetScale(Vector3D vec);
	//�x�N�g���ɂ�镽�s�ړ�
	Matrix3D  MGetTranslate(Vector3D vec);
	
public:
	double _m[4][4];
};
//�N���X�O�I�y���[�^�I�[�o�[���[�h
//���Z
const Matrix3D operator+(const Matrix3D& left, const Matrix3D& right);
//��Z
const Matrix3D operator*(const Matrix3D& left, const Matrix3D& right);
//��]�s��
//X��
Matrix3D  MGetRotX(double d);
//y��
Matrix3D  MGetRotY(double d);
//z��
Matrix3D  MGetRotZ(double d);


