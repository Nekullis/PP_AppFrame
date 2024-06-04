#include "Matrix3D.h"

Matrix3D::Matrix3D()
{
	//要素を全て0にする
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_m[i][j] = 0;
		}
	}
	//単位行列の作成
	Ident(*this);
}

Matrix3D::~Matrix3D()
{
}

Matrix3D Matrix3D::Ident(Matrix3D& m)
{
	//行列の初期化、[0][0],[1][1],[2][2],[3][3]を1にしておく
	for (int i = 0; i < 4; i++)
	{
		m._m[i][i] = 1;
	}
	return m;
}

Matrix3D Matrix3D::operator+=(const Matrix3D& right)
{
	//一時的な行列の作成
	Matrix3D temp;
	//各行、各列で加算を行う
	//0行
	temp._m[0][0] = _m[0][0] + right._m[0][0];
	temp._m[0][1] = _m[0][1] + right._m[0][1];
	temp._m[0][2] = _m[0][2] + right._m[0][2];
	temp._m[0][3] = _m[0][3] + right._m[0][3];
	//1行
	temp._m[1][0] = _m[1][0] + right._m[1][0];
	temp._m[1][1] = _m[1][1] + right._m[1][1];
	temp._m[1][2] = _m[1][2] + right._m[1][2];
	temp._m[1][3] = _m[1][3] + right._m[1][3];
	//2行
	temp._m[2][0] = _m[2][0] + right._m[2][0];
	temp._m[2][1] = _m[2][1] + right._m[2][1];
	temp._m[2][2] = _m[2][2] + right._m[2][2];
	temp._m[2][3] = _m[2][3] + right._m[2][3];
	//3行
	temp._m[3][0] = _m[3][0] + right._m[3][0];
	temp._m[3][1] = _m[3][1] + right._m[3][1];
	temp._m[3][2] = _m[3][2] + right._m[3][2];
	temp._m[3][3] = _m[3][3] + right._m[3][3];
	return temp;
}

Matrix3D Matrix3D::operator*=(const Matrix3D& right)
{
	Matrix3D temp;
	temp._m[0][0] = _m[0][0] * right._m[0][0] + _m[0][1] * right._m[1][0] + _m[0][2] * right._m[2][0] + _m[0][3] * right._m[3][0];
	temp._m[0][1] = _m[0][0] * right._m[0][1] + _m[0][1] * right._m[1][1] + _m[0][2] * right._m[2][1] + _m[0][3] * right._m[3][1];
	temp._m[0][2] = _m[0][0] * right._m[0][2] + _m[0][1] * right._m[1][2] + _m[0][2] * right._m[2][2] + _m[0][3] * right._m[3][2];
	temp._m[0][3] = _m[0][0] * right._m[0][3] + _m[0][1] * right._m[1][3] + _m[0][2] * right._m[2][3] + _m[0][3] * right._m[3][3];

	temp._m[1][0] = _m[1][0] * right._m[0][0] + _m[1][1] * right._m[1][0] + _m[1][2] * right._m[2][0] + _m[1][3] * right._m[3][0];
	temp._m[1][1] = _m[1][0] * right._m[0][1] + _m[1][1] * right._m[1][1] + _m[1][2] * right._m[2][1] + _m[1][3] * right._m[3][1];
	temp._m[1][2] = _m[1][0] * right._m[0][2] + _m[1][1] * right._m[1][2] + _m[1][2] * right._m[2][2] + _m[1][3] * right._m[3][2];
	temp._m[1][3] = _m[1][0] * right._m[0][3] + _m[1][1] * right._m[1][3] + _m[1][2] * right._m[2][3] + _m[1][3] * right._m[3][3];

	temp._m[2][0] = _m[2][0] * right._m[0][0] + _m[2][1] * right._m[1][0] + _m[2][2] * right._m[2][0] + _m[2][3] * right._m[3][0];
	temp._m[2][1] = _m[2][0] * right._m[0][1] + _m[2][1] * right._m[1][1] + _m[2][2] * right._m[2][1] + _m[2][3] * right._m[3][1];
	temp._m[2][2] = _m[2][0] * right._m[0][2] + _m[2][1] * right._m[1][2] + _m[2][2] * right._m[2][2] + _m[2][3] * right._m[3][2];
	temp._m[2][3] = _m[2][0] * right._m[0][3] + _m[2][1] * right._m[1][3] + _m[2][2] * right._m[2][3] + _m[2][3] * right._m[3][3];

	temp._m[3][0] = _m[3][0] * right._m[0][0] + _m[3][1] * right._m[1][0] + _m[3][2] * right._m[2][0] + _m[3][3] * right._m[3][0];
	temp._m[3][1] = _m[3][0] * right._m[0][1] + _m[3][1] * right._m[1][1] + _m[3][2] * right._m[2][1] + _m[3][3] * right._m[3][1];
	temp._m[3][2] = _m[3][0] * right._m[0][2] + _m[3][1] * right._m[1][2] + _m[3][2] * right._m[2][2] + _m[3][3] * right._m[3][2];
	temp._m[3][3] = _m[3][0] * right._m[0][3] + _m[3][1] * right._m[1][3] + _m[3][2] * right._m[2][3] + _m[3][3] * right._m[3][3];
	return temp;
}

bool Matrix3D::operator==(const Matrix3D& right)
{
	if (_m[0][0] == right._m[0][0] && _m[0][1] == right._m[0][1] && _m[0][2] == right._m[0][2] && _m[0][3] == right._m[0][3]
		&& _m[1][0] == right._m[1][0] && _m[1][1] == right._m[1][1] && _m[1][2] == right._m[1][2] && _m[0][3] == right._m[1][3]
		&& _m[2][0] == right._m[2][0] && _m[2][1] == right._m[2][1] && _m[2][2] == right._m[2][2] && _m[0][3] == right._m[2][3]
		&& _m[3][0] == right._m[3][0] && _m[3][1] == right._m[3][1] && _m[3][2] == right._m[3][2] && _m[0][3] == right._m[3][3])
	{
		return true;
	}
	return false;
}

bool Matrix3D::operator!=(const Matrix3D& right)
{
	return !(*this==right);
}

Matrix3D& Matrix3D::operator=(const MATRIX& right)
{
	
	_m[0][0] = right.m[0][0];
	_m[0][1] = right.m[0][1];
	_m[0][2] = right.m[0][2];
	_m[0][3] = right.m[0][3];

	_m[1][0] = right.m[1][0];
	_m[1][1] = right.m[1][1];
	_m[1][2] = right.m[1][2];
	_m[1][3] = right.m[1][3];

	_m[2][0] = right.m[2][0];
	_m[2][1] = right.m[2][1];
	_m[2][2] = right.m[2][2];
	_m[2][3] = right.m[2][3];

	_m[3][0] = right.m[3][0];
	_m[3][1] = right.m[3][1];
	_m[3][2] = right.m[3][2];
	_m[3][3] = right.m[3][3];
	return (*this);
}

Matrix3D Matrix3D::MScale(Matrix3D m, double d)
{
	Matrix3D temp;
	temp._m[0][0] = m._m[0][0] * d;
	temp._m[0][1] = m._m[0][1] * d;
	temp._m[0][2] = m._m[0][2] * d;
	temp._m[0][3] = m._m[0][3] * d;

	temp._m[1][0] = m._m[1][0] * d;
	temp._m[1][1] = m._m[1][1] * d;
	temp._m[1][2] = m._m[1][2] * d;
	temp._m[1][3] = m._m[1][3] * d;

	temp._m[2][0] = m._m[2][0] * d;
	temp._m[2][1] = m._m[2][1] * d;
	temp._m[2][2] = m._m[2][2] * d;
	temp._m[2][3] = m._m[2][3] * d;

	temp._m[3][0] = m._m[3][0] * d;
	temp._m[3][1] = m._m[3][1] * d;
	temp._m[3][2] = m._m[3][2] * d;
	temp._m[3][3] = m._m[3][3] * d;
	return temp;
}

Matrix3D Matrix3D::MGetScale(Vector3D vec)
{
	Matrix3D temp;
	temp._m[0][0] = vec._x;
	temp._m[1][1] = vec._y;
	temp._m[2][2] = vec._z;
	temp._m[3][3] = 1.0f;
	return temp;
}

Matrix3D Matrix3D::MGetTranslate(Vector3D vec)
{
	Matrix3D temp;
	temp._m[3][0] = vec._x;
	temp._m[3][1] = vec._y;
	temp._m[3][2] = vec._z;
	temp._m[3][3] = 1.0f;
	return temp;
}

const Matrix3D operator+(const Matrix3D& left, const Matrix3D& right)
{
	return Matrix3D(left) += right;
}

const Matrix3D operator*(const Matrix3D& left, const Matrix3D& right)
{
	return Matrix3D(left) *= right;
}

Matrix3D MGetRotX(double d)
{
	float _sin, _cos;
	_sin = sin(d);
	_cos = cos(d);
	Matrix3D temp;
	temp._m[1][1] = _cos;
	temp._m[1][2] = _sin;
	temp._m[2][1] = -_sin;
	temp._m[2][2] = _cos;
	return temp;
}

Matrix3D MGetRotY(double d)
{
	float _sin, _cos;
	_sin = sin(d);
	_cos = cos(d);
	Matrix3D temp;
	temp._m[0][0] = _cos;
	temp._m[0][2] = -_sin;
	temp._m[2][0] = _sin;
	temp._m[2][2] = _cos;
	return temp;
}

Matrix3D MGetRotZ(double d)
{
	float _sin, _cos;
	_sin = sin(d);
	_cos = cos(d);
	Matrix3D temp;
	temp._m[0][0] = _cos;
	temp._m[0][1] = _sin;
	temp._m[1][0] = -_sin;
	temp._m[1][1] = _cos;
	return temp;
}




