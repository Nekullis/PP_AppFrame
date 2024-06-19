#include "Vector3D.h"
#include"../Matrix3D/Matrix3D.h"
#include <math.h>
// オペレータオーバーロード（クラス外）
Vector3D operator+(const Vector3D& left, const Vector3D& right)
{
	return Vector3D(left) += right;
}
Vector3D operator-(const Vector3D& left, const Vector3D& right)
{
	return Vector3D(left) -= right;
}
Vector3D operator*(const Vector3D& left, const double right)
{
	return Vector3D(left) *= right;
}
Vector3D operator*(const double left, const Vector3D& right)
{
	return Vector3D(right) *= left;
}
Vector3D operator*(const Vector3D& left, const Matrix3D& right)
{
	return Vector3D::Transform(left,right);
}
Vector3D operator/(const Vector3D& left, const double right)
{
	return Vector3D(left) /= right;
}
Vector3D operator/(const double left, const Vector3D& right)
{
	return Vector3D(right) /= left;
}

Vector3D	Vector3D::operator+=(const Vector3D& right)
{
	_x = _x + right._x;
	_y = _y + right._y;
	_z = _z + right._z;
	return (*this);
}
Vector3D	Vector3D::operator-=(const Vector3D& right)
{
	_x = _x - right._x;
	_y = _y - right._y;
	_z = _z - right._z;
	return (*this);
}
Vector3D	Vector3D::operator*=(const double right) 
{
	_x = _x * right;
	_y = _y * right;
	_z = _z * right;
	return (*this);
}
Vector3D	Vector3D::operator/=(const double right)
{
	_x = _x / right;
	_y = _y / right;
	_z = _z / right;
	return (*this);
}
bool Vector3D::operator==(const Vector3D& right)
{
	if (_x == right._x && _y == right._y && _z == right._z) { return true; }
	return false;
}
bool Vector3D::operator!=(const Vector3D& right)
{
	return !(*this == right);
}

Vector3D& Vector3D::operator=(const VECTOR& right)
{
	_x = right.x;
	_y = right.y;
	_z = right.z;
	return (*this);
}
VECTOR		Vector3D::dxl()
{
	VECTOR v;
	v.x = static_cast<float>(_x);
	v.y = static_cast<float>(_y);
	v.z = static_cast<float>(_z);
	return v;
}

double	Vector3D::Dot(Vector3D& in1, Vector3D& in2)
{
	return ((in1._x * in2._x) + (in1._y * in2._y) + (in1._z * in2._z));
}

double	Vector3D::Dot(Vector3D& in1)
{
	Vector3D temp = (*this);
	return ((temp._x * in1._x) + (temp._y * in1._y) + (temp._z * in1._z));
}

double Vector3D::Dot()
{
	return Dot(*this);
}

Vector3D Vector3D::Scale(double& d)
{
	Vector3D temp = (*this);
	temp._x *= d;
	temp._y *= d;
	temp._z *= d;
	return temp;
}

Vector3D	Vector3D::Cross(Vector3D& in1, Vector3D& in2)
{
	Vector3D tmp;
	tmp._x = in1._y * in2._z - in1._z * in2._y;
	tmp._y = in1._z * in2._x - in1._x * in2._z;
	tmp._z = in1._x * in2._y - in1._y * in2._x;
	return tmp;
}

Vector3D Vector3D::Cross(Vector3D& in1)
{
	//Vector3D temp = (*this);
	return Cross((*this), in1);
}

double	Vector3D::Length(Vector3D& in)
{
	return sqrt(Dot(in, in));
}
double Vector3D::Length()
{
	return Length((*this));
}
double	Vector3D::Length(Vector3D& in1, Vector3D& in2)
{
	Vector3D in = in1 - in2;
	return Length(in);
}

Vector3D Vector3D::Normalize(Vector3D& in)
{
	const double division = Length(in);
	if (division == 0.0) {
		// ゼロ除算発生
	}
	return in * (1.0 / division);
}

Vector3D Vector3D::Normalize()
{
	return Normalize(*this);
}

Vector3D Vector3D::Transform(const Vector3D& in, const Matrix3D& matrix)
{
	Vector3D temp;
	temp._x = in._x * matrix._m[0][0] + in._y * matrix._m[1][0] + in._z * matrix._m[2][0] + matrix._m[3][0];
	temp._y = in._x * matrix._m[0][1] + in._y * matrix._m[1][1] + in._z * matrix._m[2][1] + matrix._m[3][1];
	temp._z = in._x * matrix._m[0][2] + in._y * matrix._m[1][2] + in._z * matrix._m[2][2] + matrix._m[3][2];
	return temp;
}

