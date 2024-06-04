#pragma once
#include "DxLib.h"
#include "../Vector3D/Vector3D.h"
#include <math.h>
//3Dにおける行列関連のクラス
class Matrix3D
{
public:
	Matrix3D();
	~Matrix3D();
	Matrix3D Ident(Matrix3D& m);
	//オペレータオーバーロード
	Matrix3D  operator+=(const Matrix3D& right);
	Matrix3D  operator*=(const Matrix3D& right);
	bool      operator==(const Matrix3D& right);
	bool      operator!=(const Matrix3D& right);
	//DXライブラリのMATRIXを使えるように
	Matrix3D& operator= (const MATRIX& right);
	//matrix計算処理
	//スケーリング
	Matrix3D  MScale(Matrix3D m, double d);
	//ベクトルによる拡大縮小
	Matrix3D  MGetScale(Vector3D vec);
	//ベクトルによる平行移動
	Matrix3D  MGetTranslate(Vector3D vec);
	
public:
	double _m[4][4];
};
//クラス外オペレータオーバーロード
//加算
const Matrix3D operator+(const Matrix3D& left, const Matrix3D& right);
//乗算
const Matrix3D operator*(const Matrix3D& left, const Matrix3D& right);
//回転行列
//X軸
Matrix3D  MGetRotX(double d);
//y軸
Matrix3D  MGetRotY(double d);
//z軸
Matrix3D  MGetRotZ(double d);


