#pragma once
#include "DxLib.h"
//3D�ɂ�����x�N�g���̌v�Z�N���X
class Vector3D
{
public:
	Vector3D() : _x(0), _y(0), _z(0) {}
	Vector3D(double x, double y, double z) : _x(x), _y(y), _z(z) {}
	Vector3D(const VECTOR v) :_x(v.x), _y(v.y), _z(v.z) {}		// DX���C�u��������
	virtual ~Vector3D() {}
	// �I�y���[�^�I�[�o�[���[�h�i�N���X���j
	Vector3D	operator+=(const Vector3D& right);
	Vector3D	operator-=(const Vector3D& right);
	Vector3D	operator*=(const double right);
	Vector3D	operator/=(const double right);
	bool		operator==(const Vector3D& right);
	bool		operator!=(const Vector3D& right);
	// DX���C�u��������
	Vector3D& operator=(const VECTOR& right);
	//VECTOR�^�ɕϊ�
	VECTOR		dxl();
	// ����
	static double	Dot(Vector3D& in1, Vector3D& in2);
	// ����
	double			Dot(Vector3D& in1);
	// ���g�̃x�N�g���݂̂̓���
	double			Dot();
	// �X�P�[�����O
	Vector3D		Scale(double& d);
	// �O��
	static Vector3D	Cross(Vector3D& in1, Vector3D& in2);
	// �O��
	Vector3D		Cross(Vector3D& in1);
	// ����
	static double	Length(Vector3D& in);
	// ����
	double			Length();
	// ����(2�_��)
	static double	Length(Vector3D& in1, Vector3D& in2);
	// ���K��
	static Vector3D Normalize(Vector3D& in);
	// ���K��
	Vector3D		Normalize();
	// �x�N�g���̕ϊ�
	static Vector3D		Transform(const Vector3D& in,const class Matrix3D& matrix);

public:
	double	_x, _y, _z;
};

// �I�y���[�^�I�[�o�[���[�h�i�N���X�O�j
Vector3D operator+(const Vector3D& left, const Vector3D& right);
Vector3D operator-(const Vector3D& left, const Vector3D& right);
Vector3D operator*(const Vector3D& left, const double right);
Vector3D operator*(const double left, const Vector3D& right);
Vector3D operator*(const Vector3D& left, const class Matrix3D& right);
Vector3D operator/(const Vector3D& left, const double right);
Vector3D operator/(const double left, const Vector3D& right);


