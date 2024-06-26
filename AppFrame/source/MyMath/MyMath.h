#pragma once
#include <math.h>
//計算関連関数をまとめたクラス
class MyMath
{
	//円周率
	static constexpr double PI = 3.14159265;
public:
	MyMath();
	~MyMath();
	//角度単位の変換
	//degree->rad
	template<typename T>
	static T DegToRad(T deg) { return deg * PI / 180.0f; }
	//rad->degree
	template<typename T>
	static T RadToDeg(T rad) { return rad * 180.0 / PI; }
	//微小な値との比較
	static bool NearZero(double vol, double epsiron = 0.001);
	//球面座標系からデカルト座標系に変換する
	static class Vector3D ConvertToCartesian(class Vector3D angle, float radius);
	//最短距離系
	//点と直線の最短距離
	static float DisPointAndLine(class Vector3D& v1, class Vector3D& v2s, class Vector3D& v2e, class Vector3D& mp, double& t);
	//点と線分の最短距離
	static float DisPointAndSegment(class Vector3D& v1, class Vector3D& v2s, class Vector3D& v2e, class Vector3D& mp, double& t);
	//直線と直線の最短距離
	static float DisLineAndLine(class Vector3D& v1s, class Vector3D& v1e, class Vector3D& v1m, double& t1, class Vector3D& v2s, class Vector3D& v2e, class Vector3D& v2m, double& t2);
	//線分と線分の最短距離
	static float DisSegAndSeg(class Vector3D& v1s, class Vector3D& v1e, class Vector3D& v1m, double& t1, class Vector3D& v2s, class Vector3D& v2e, class Vector3D& v2m, double& t2);
	//点とAABBの最短距離
	static float DisPointAndAABB(class Vector3D v1, double w1, double h1, double d1, class Vector3D v2);
	//当たり判定系
	//点と扇形の当たり判定
	static bool ColPointAndFan(class Vector3D v1, class Vector3D v2, float rad);
};
