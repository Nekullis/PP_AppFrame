#pragma once
#include <math.h>
//�v�Z�֘A�֐����܂Ƃ߂��N���X
class MyMath
{
	//�~����
	static constexpr double PI = 3.14159265;
public:
	MyMath();
	~MyMath();
	//�p�x�P�ʂ̕ϊ�
	//degree->rad
	template<typename T>
	static T DegToRad(T deg) { return deg * PI / 180.0; }
	//rad->degree
	template<typename T>
	static T RadToDeg(T rad) { return rad * 180.0 / PI; }
	//�����Ȓl�Ƃ̔�r
	static bool NearZero(double vol, double epsiron = 0.001);
	//�ŒZ�����n
	//�_�ƒ����̍ŒZ����
	static float DisPointAndLine(class Vector3D& v1, class Vector3D& v2s, class Vector3D& v2e, class Vector3D& mp, double& t);
	//�_�Ɛ����̍ŒZ����
	static float DisPointAndSegment(class Vector3D& v1, class Vector3D& v2s, class Vector3D& v2e, class Vector3D& mp, double& t);
	//�����ƒ����̍ŒZ����
	static float DisLineAndLine(class Vector3D& v1s, class Vector3D& v1e, class Vector3D& v1m, double& t1, class Vector3D& v2s, class Vector3D& v2e, class Vector3D& v2m, double& t2);
	//�����Ɛ����̍ŒZ����
	static float DisSegAndSeg(class Vector3D& v1s, class Vector3D& v1e, class Vector3D& v1m, double& t1, class Vector3D& v2s, class Vector3D& v2e, class Vector3D& v2m, double& t2);
	//�_��AABB�̍ŒZ����
	static float DisPointAndAABB(class Vector3D v1, double w1, double h1, double d1, class Vector3D v2);
	//�����蔻��n
	//�_�Ɛ�`�̓����蔻��
	static bool ColPointAndFan(class Vector3D v1, class Vector3D v2, float rad);
};
