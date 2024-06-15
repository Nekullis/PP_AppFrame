#include "MyMath.h"
#include "../Vector3D/Vector3D.h"
MyMath::MyMath()
{
}

MyMath::~MyMath()
{
}

bool MyMath::NearZero(double vol, double epsiron)
{
	if (fabs(vol) <= epsiron) { return true; }
	else { return false; }
}

Vector3D MyMath::ConvertToCartesian(Vector3D angle, float radius)
{
	Vector3D temp;
	//���ʍ��W�n���f�J���g���W�n�ɕϊ����邽�߂ɕK�v�ȗv�f�͔��a(radius),�����p�x(angle��x����),�����p�x(angle��y����)
	temp._x = radius * cos(angle._x) * sin(angle._y);
	temp._y = radius * sin(angle._x);
	temp._z = radius * cos(angle._x) * cos(angle._y);
	return temp;
}

float MyMath::DisPointAndLine(Vector3D& v1, Vector3D& v2s, Vector3D& v2e, Vector3D& mp, double& t)
{
	//v1:�_�̈ʒu
	//v2s:�����̎n�_
	//v2e:�����̏I�_
	// �n�_�ƏI�_�����邽�ߖ{���͐����Ȃ̂�������͒����Ƃ��Ĉ���
	//mp:v1���璼���ɉ����������̒[�_
	//t:����v2(v2e-v2s)�̒�����1�Ƃ�������v2s����mp�܂ł̒����̊���

	//���������߂�
	Vector3D v2 = v2e - v2s;
	//���ς����߂�
	float dv = v2.Dot();
	//���ς�0���傫���Ȃ�
	if (dv > 0.0) 
	{ 
		//�_�Ɛ����̎n�_�̓��ς��璼���̓��ςŊ��������̂𐂐��̒[�_�Ƃ���
		Vector3D v = v1 - v2s;
		t = v2.Dot(v) / dv; 
	}
	//�����̊���=�����̎n�_+����v2�ɒ[�_�ŃX�P�[�����O��������
	mp = v2s + v2.Scale(t);
	//2�_�Ԃ̋��������߁A�Ԃ�
	return (v1 - mp).Length();
}

float MyMath::DisPointAndSegment(Vector3D& v1, Vector3D& v2s, Vector3D& v2e, Vector3D& mp, double& t)
{
	//v1:�_�̈ʒu
	//v2s:�����̎n�_
	//v2e:�����̏I�_
	//mp:v1���璼���ɉ����������̒[�_
	//t:����v2(v2e-v2s)�̒�����1�Ƃ�������v2s����mp�܂ł̒����̊���

	//�_�ƒ����̍ŒZ���������߂�
	float dist = DisPointAndLine(v1, v2s, v2e, mp, t);
	//������0.0��菬����
	if (t < 0.0)
	{
		//�[�_������̎n�_��
		mp = v2s;
		//2�_�Ԃ̋��������߁A�Ԃ�
		return (v1 - mp).Length();
	}
	//������1.0���傫��
	if (t > 1.0)
	{
		//�[�_������̏I�_��
		mp = v2e;
		//2�_�Ԃ̋��������߁A�Ԃ�
		return (v1 - mp).Length();
	}
	//�ǂ���ł��Ȃ�(0 <= t <= 1)�Ȃ�mp���������ɂ���̂ł��̂܂ܕԂ�
	return dist;
}

float MyMath::DisLineAndLine(Vector3D& v1s, Vector3D& v1e, Vector3D& v1m, double& t1, Vector3D& v2s, Vector3D& v2e, Vector3D& v2m, double& t2)
{
	//v1s:�����̎n�_�̍��W
	//v1e:�����̏I�_�̍��W
	//v1m:�ŒZ���̒[�_1
	//t1:����v1(v1e-v1s)�̒�����1�Ƃ�������v1s����v1m�܂ł̒����̊���
	//v2s:�����̎n�_�̍��W
	//v2e:�����̏I�_�̍��W
	//v2m:�ŒZ���̒[�_2
	//t2:����v2(v2e-v2s)�̒�����1�Ƃ�������v2s����v2m�܂ł̒����̊���
	//�n�_�ƏI�_�̍��W������̂ł���͐����Ȃ̂����A����͒����Ƃ��Ĉ���

	//���������߂�
	Vector3D v1 = v1e - v1s;
	Vector3D v2 = v2e - v2s;
	//2���������s�ȏꍇ
	Vector3D dot = v1.Cross(v2);
	if (v1.Dot(dot) < 0.000001 && v1.Dot(dot) > -0.000001)
	{
		//�_�ƒ����̍ŒZ���������߂�
		float dist = DisPointAndLine(v1s, v2s, v2e, v2m, t2);
		//����v1�̍ŒZ��̒[�_��v1�̎n�_�Ƃ���
		v1m = v1s;
		//������0.0��
		t1 = 0.0;
		//�ŒZ������Ԃ�
		return dist;
	}
	//2���������s�łȂ��Ƃ�
	//�݂��������ɂȂ�ŒZ��̒[�_v1m,v2m�����߂�
	//����v1��v2�̓��ς����߂�
	double dov1v2 = v1.Dot(v2);
	//����v1�̓��ς����߂�
	double dov1v1 = v1.Dot();
	//����v2�̓��ς����߂�
	double dov2v2 = v2.Dot();
	//�e�����̎n�_�Œ��������߂�
	Vector3D vp2p1 = v1s - v2s;
	//A:����v1v2�̓��ς�v2�Ǝn�_�̒����œ��ς����߂����̂𑫂�
	//B:����v2�̓��ς�v1�Ǝn�_�̒����œ��ς����߂����̂̐ς����߂�
	//A��B�̍������߂�(A-B=C)
	//D:v1�̓��ς�v2�̓��ς̐ς����߂�
	//E:�e�n�_���狁�߂�������2������߂�
	//D��E�̍������߂�(D-E=F)
	//C��F�̏������߂�
	t1 = (dov1v2 + v2.Dot(vp2p1) - dov2v2 * v1.Dot(vp2p1)) / (dov1v1 * dov2v2 - dov1v2 * dov1v2);
	//v1�̎n�_��v1�̊����ŃX�P�[�����O�������̂𑫂���v1�̒[�_�Ƃ���
	v1m = v1s + v1.Scale(t1);
	//v1�̒[�_��v2�̎n�_�Œ��������߂�
	Vector3D dom1v2 = v1m - v2s;
	//v2�ƒ[�_�Ǝn�_�̒����œ��ς����߁Av2�̓��ςƂ̏������߂����̂�v2�̊����Ƃ���
	t2 = v2.Dot(dom1v2) / dov2v2;
	//v2�̎n�_��v2�̊����ŃX�P�[�����O�������̂𑫂���v2�̒[�_�Ƃ���
	v2m = v2s + v2.Scale(t2);
	//2�_�Ԃ̋��������߁A�Ԃ�
	return (v2m - v1m).Length();
}

float MyMath::DisSegAndSeg(Vector3D& v1s, Vector3D& v1e, Vector3D& v1m, double& t1, Vector3D& v2s, Vector3D& v2e, Vector3D& v2m, double& t2)
{
	//��쓮�h�~�̂��߃N�����v����֐����쐬
	auto clamp0to1 = [](double& d)
		{
			if (d < 0.0) { d = 0.0; }
			else if (d > 1.0) { d = 1.0; }
		};
	//v1s:�����̎n�_�̍��W
	//v1e:�����̏I�_�̍��W
	//v1m:�ŒZ���̒[�_1
	//t1:����v1(v1e-v1s)�̒�����1�Ƃ�������v1s����v1m�܂ł̒����̊���
	//v2s:�����̎n�_�̍��W
	//v2e:�����̏I�_�̍��W
	//v2m:�ŒZ���̒[�_2
	//t2:����v2(v2e-v2s)�̒�����1�Ƃ�������v2s����v2m�܂ł̒����̊���

	//�����̍쐬
	Vector3D v1 = v1e - v1s;
	Vector3D v2 = v2e - v2s;
	float dist = 0.0f;
	//2�����Ԃ̍ŒZ���������߂�
	dist = DisLineAndLine(v1s, v1e, v1m, t1, v2s, v2e, v2m, t2);
	//v1m,v2m1�������Ƃ��������ɂ������Ȃ�Ԃ�
	if (0.0 <= t1 && t1 <= 1.0 && 0.0 <= t2 && t2 <= 1.0) { return dist; }
	//�����A�܂��͂ǂ��炩���Ȃ����ߎ���
	//�N�����v���Ă���
	clamp0to1(t2);
	//�[�_�����߂Ă���
	v2m = v2s + v2.Scale(t2);
	//�_�Ɛ����̍ŒZ���������߂�
	dist = DisPointAndSegment(v2m, v1s, v1e, v1m, t1);
	//v1m���������ɂ������Ȃ�Ԃ�
	if (0.0 <= t1 && t1 <= 1.0) { return dist; }
	//�N�����v���Ă���
	clamp0to1(t1);
	//�[�_�����߂Ă���
	v1m = v1s + v1.Scale(t1);
	//�_�Ɛ����̍ŒZ���������߂�
	dist = DisPointAndSegment(v1m, v2s, v2e, v2m, t2);
	//v2m���������ɂ������Ȃ�Ԃ�
	if (0.0 <= t2 && t2 <= 1.0) { return dist; }
	//�����܂łȂ�������v1m����v2m�܂ł��ŒZ�Ȃ̂ł����Ԃ�
	return (v2m - v1m).Length();
}

float MyMath::DisPointAndAABB(Vector3D v1, double w1, double h1, double d1, Vector3D v2)
{
	double dist = 0.0;
	//�_v2��x���W��AABB�̈ʒu-AABB�̉���/2����������
	if(v2._x < v1._x - w1 / 2)
	{
		//�ŒZ�����ɓ�_�̍�+����/2�����Z
		dist += (v2._x - (v1._x - w1 / 2)) * (v2._x - (v1._x - w1 / 2));
	}
	//�_v2��y���W��AABB�̈ʒu-AABB�̍���/2����������
	if(v2._y < v1._y - h1 / 2)
	{
		//�ŒZ�����ɓ�_�̍�+����/2�����Z
		dist += (v2._y - (v1._y - h1 / 2)) * (v2._y - (v1._y - h1 / 2));
	}
	//�_v2��z���W��AABB�̈ʒu-AABB�̉��s/2����������
	if(v2._z < v1._z - d1 / 2)
	{
		//�ŒZ�����ɓ�_�̍�+���s/2�����Z
		dist += (v2._z - (v1._z - d1 / 2)) * (v2._z - (v1._z - d1 / 2));
	}
	//�_v2��x���W��AABB�̈ʒu+AABB�̉���/2�����傫��
	if(v2._x > v1._x + w1 / 2)
	{
		//�ŒZ�����ɓ�_�̍�+����/2�����Z
		dist += (v2._x - (v1._x + w1 / 2)) * (v2._x - (v1._x + w1 / 2));
	}
	//�_v2��y���W��AABB�̈ʒu+AABB�̉���/2�����傫��
	if(v2._y > v1._y + h1 / 2)
	{
		//�ŒZ�����ɓ�_�̍�+����/2�����Z
		dist += (v2._y - (v1._y + h1 / 2)) * (v2._y - (v1._y + h1 / 2));
	}
	//�_v2��z���W��AABB�̈ʒu+AABB�̉���/2�����傫��
	if(v2._z > v1._z + d1 / 2)
	{
		//�ŒZ�����ɓ�_�̍�+���s/2�����Z
		dist += (v2._z - (v1._z + d1 / 2)) * (v2._z - (v1._z + d1 / 2));
	}
	//�ŒZ������Ԃ�
	return dist;
}

bool MyMath::ColPointAndFan(Vector3D v1, Vector3D v2, float rad)
{
	//v1:�����x�N�g��
	//v2:��������̕����x�N�g��
	//rad:�p�x(�z��p�x�̔���)

	//���ς̌v�Z
	//�e�x�N�g���̐��K��
	v1 = v1.Normalize();
	v2 = v2.Normalize();
	float dot = v1.Dot(v2);
	//�v�Z���o�O��Ȃ��悤��
	if (dot < 0.00001 && dot > -0.00001) { return false; }
	//���ς��p�x���傫����ΏՓ˂��Ă���
	if (dot > rad) { return true; }
	return false;
}

