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
	//球面座標系をデカルト座標系に変換するために必要な要素は半径(radius),垂直角度(angleのx成分),水平角度(angleのy成分)
	temp._x = radius * cos(angle._x) * sin(angle._y);
	temp._y = radius * sin(angle._x);
	temp._z = radius * cos(angle._x) * cos(angle._y);
	return temp;
}

float MyMath::DisPointAndLine(Vector3D& v1, Vector3D& v2s, Vector3D& v2e, Vector3D& mp, double& t)
{
	//v1:点の位置
	//v2s:直線の始点
	//v2e:直線の終点
	// 始点と終点があるため本来は線分なのだが今回は直線として扱う
	//mp:v1から直線に下した垂線の端点
	//t:直線v2(v2e-v2s)の長さを1とした時のv2sからmpまでの長さの割合

	//直線を求める
	Vector3D v2 = v2e - v2s;
	//内積を求める
	float dv = v2.Dot();
	//内積が0より大きいなら
	if (dv > 0.0) 
	{ 
		//点と線分の始点の内積から直線の内積で割ったものを垂線の端点とする
		Vector3D v = v1 - v2s;
		t = v2.Dot(v) / dv; 
	}
	//長さの割合=直線の始点+直線v2に端点でスケーリングしたもの
	mp = v2s + v2.Scale(t);
	//2点間の距離を求め、返す
	return (v1 - mp).Length();
}

float MyMath::DisPointAndSegment(Vector3D& v1, Vector3D& v2s, Vector3D& v2e, Vector3D& mp, double& t)
{
	//v1:点の位置
	//v2s:直線の始点
	//v2e:直線の終点
	//mp:v1から直線に下した垂線の端点
	//t:直線v2(v2e-v2s)の長さを1とした時のv2sからmpまでの長さの割合

	//点と直線の最短距離を求める
	float dist = DisPointAndLine(v1, v2s, v2e, mp, t);
	//割合が0.0より小さい
	if (t < 0.0)
	{
		//端点を線分の始点に
		mp = v2s;
		//2点間の距離を求め、返す
		return (v1 - mp).Length();
	}
	//割合が1.0より大きい
	if (t > 1.0)
	{
		//端点を線分の終点に
		mp = v2e;
		//2点間の距離を求め、返す
		return (v1 - mp).Length();
	}
	//どちらでもない(0 <= t <= 1)ならmpが線分内にあるのでそのまま返す
	return dist;
}

float MyMath::DisLineAndLine(Vector3D& v1s, Vector3D& v1e, Vector3D& v1m, double& t1, Vector3D& v2s, Vector3D& v2e, Vector3D& v2m, double& t2)
{
	//v1s:直線の始点の座標
	//v1e:直線の終点の座標
	//v1m:最短線の端点1
	//t1:線分v1(v1e-v1s)の長さを1とした時のv1sからv1mまでの長さの割合
	//v2s:直線の始点の座標
	//v2e:直線の終点の座標
	//v2m:最短線の端点2
	//t2:線分v2(v2e-v2s)の長さを1とした時のv2sからv2mまでの長さの割合
	//始点と終点の座標があるのでこれは線分なのだが、今回は直線として扱う

	//直線を求める
	Vector3D v1 = v1e - v1s;
	Vector3D v2 = v2e - v2s;
	//2直線が平行な場合
	Vector3D dot = v1.Cross(v2);
	if (v1.Dot(dot) < 0.000001 && v1.Dot(dot) > -0.000001)
	{
		//点と直線の最短距離を求める
		float dist = DisPointAndLine(v1s, v2s, v2e, v2m, t2);
		//直線v1の最短戦の端点をv1の始点とする
		v1m = v1s;
		//割合を0.0に
		t1 = 0.0;
		//最短距離を返す
		return dist;
	}
	//2直線が並行でないとき
	//互いが垂直になる最短戦の端点v1m,v2mを求める
	//直線v1とv2の内積を求める
	double dov1v2 = v1.Dot(v2);
	//直線v1の内積を求める
	double dov1v1 = v1.Dot();
	//直線v2の内積を求める
	double dov2v2 = v2.Dot();
	//各直線の始点で直線を求める
	Vector3D vp2p1 = v1s - v2s;
	//A:直線v1v2の内積とv2と始点の直線で内積を求めたものを足す
	//B:直線v2の内積とv1と始点の直線で内積を求めたものの積を求める
	//AとBの差を求める(A-B=C)
	//D:v1の内積とv2の内積の積を求める
	//E:各始点から求めた直線の2乗を求める
	//DとEの差を求める(D-E=F)
	//CとFの商を求める
	t1 = (dov1v2 + v2.Dot(vp2p1) - dov2v2 * v1.Dot(vp2p1)) / (dov1v1 * dov2v2 - dov1v2 * dov1v2);
	//v1の始点とv1の割合でスケーリングしたものを足してv1の端点とする
	v1m = v1s + v1.Scale(t1);
	//v1の端点とv2の始点で直線を求める
	Vector3D dom1v2 = v1m - v2s;
	//v2と端点と始点の直線で内積を求め、v2の内積との商を求めたものをv2の割合とする
	t2 = v2.Dot(dom1v2) / dov2v2;
	//v2の始点とv2の割合でスケーリングしたものを足してv2の端点とする
	v2m = v2s + v2.Scale(t2);
	//2点間の距離を求め、返す
	return (v2m - v1m).Length();
}

float MyMath::DisSegAndSeg(Vector3D& v1s, Vector3D& v1e, Vector3D& v1m, double& t1, Vector3D& v2s, Vector3D& v2e, Vector3D& v2m, double& t2)
{
	//誤作動防止のためクランプする関数を作成
	auto clamp0to1 = [](double& d)
		{
			if (d < 0.0) { d = 0.0; }
			else if (d > 1.0) { d = 1.0; }
		};
	//v1s:直線の始点の座標
	//v1e:直線の終点の座標
	//v1m:最短線の端点1
	//t1:線分v1(v1e-v1s)の長さを1とした時のv1sからv1mまでの長さの割合
	//v2s:直線の始点の座標
	//v2e:直線の終点の座標
	//v2m:最短線の端点2
	//t2:線分v2(v2e-v2s)の長さを1とした時のv2sからv2mまでの長さの割合

	//線分の作成
	Vector3D v1 = v1e - v1s;
	Vector3D v2 = v2e - v2s;
	float dist = 0.0f;
	//2直線間の最短距離を求める
	dist = DisLineAndLine(v1s, v1e, v1m, t1, v2s, v2e, v2m, t2);
	//v1m,v2m1が両方とも線分内にあったなら返す
	if (0.0 <= t1 && t1 <= 1.0 && 0.0 <= t2 && t2 <= 1.0) { return dist; }
	//両方、またはどちらかがないため次へ
	//クランプしておく
	clamp0to1(t2);
	//端点を求めておく
	v2m = v2s + v2.Scale(t2);
	//点と線分の最短距離を求める
	dist = DisPointAndSegment(v2m, v1s, v1e, v1m, t1);
	//v1mが線分内にあったなら返す
	if (0.0 <= t1 && t1 <= 1.0) { return dist; }
	//クランプしておく
	clamp0to1(t1);
	//端点を求めておく
	v1m = v1s + v1.Scale(t1);
	//点と線分の最短距離を求める
	dist = DisPointAndSegment(v1m, v2s, v2e, v2m, t2);
	//v2mが線分内にあったなら返す
	if (0.0 <= t2 && t2 <= 1.0) { return dist; }
	//ここまでなかったらv1mからv2mまでが最短なのでそれを返す
	return (v2m - v1m).Length();
}

float MyMath::DisPointAndAABB(Vector3D v1, double w1, double h1, double d1, Vector3D v2)
{
	double dist = 0.0;
	//点v2のx座標がAABBの位置-AABBの横幅/2よりも小さい
	if(v2._x < v1._x - w1 / 2)
	{
		//最短距離に二点の差+横幅/2を加算
		dist += (v2._x - (v1._x - w1 / 2)) * (v2._x - (v1._x - w1 / 2));
	}
	//点v2のy座標がAABBの位置-AABBの高さ/2よりも小さい
	if(v2._y < v1._y - h1 / 2)
	{
		//最短距離に二点の差+高さ/2を加算
		dist += (v2._y - (v1._y - h1 / 2)) * (v2._y - (v1._y - h1 / 2));
	}
	//点v2のz座標がAABBの位置-AABBの奥行/2よりも小さい
	if(v2._z < v1._z - d1 / 2)
	{
		//最短距離に二点の差+奥行/2を加算
		dist += (v2._z - (v1._z - d1 / 2)) * (v2._z - (v1._z - d1 / 2));
	}
	//点v2のx座標がAABBの位置+AABBの横幅/2よりも大きい
	if(v2._x > v1._x + w1 / 2)
	{
		//最短距離に二点の差+横幅/2を加算
		dist += (v2._x - (v1._x + w1 / 2)) * (v2._x - (v1._x + w1 / 2));
	}
	//点v2のy座標がAABBの位置+AABBの横幅/2よりも大きい
	if(v2._y > v1._y + h1 / 2)
	{
		//最短距離に二点の差+高さ/2を加算
		dist += (v2._y - (v1._y + h1 / 2)) * (v2._y - (v1._y + h1 / 2));
	}
	//点v2のz座標がAABBの位置+AABBの横幅/2よりも大きい
	if(v2._z > v1._z + d1 / 2)
	{
		//最短距離に二点の差+奥行/2を加算
		dist += (v2._z - (v1._z + d1 / 2)) * (v2._z - (v1._z + d1 / 2));
	}
	//最短距離を返す
	return dist;
}

bool MyMath::ColPointAndFan(Vector3D v1, Vector3D v2, float rad)
{
	//v1:方向ベクトル
	//v2:もう一方の方向ベクトル
	//rad:角度(想定角度の半分)

	//内積の計算
	//各ベクトルの正規化
	v1 = v1.Normalize();
	v2 = v2.Normalize();
	float dot = v1.Dot(v2);
	//計算がバグらないように
	if (dot < 0.00001 && dot > -0.00001) { return false; }
	//内積が角度より大きければ衝突している
	if (dot > rad) { return true; }
	return false;
}

