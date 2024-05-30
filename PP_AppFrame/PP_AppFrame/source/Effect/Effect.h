#pragma once
#include "../Vector3D/Vector3D.h"
#include "EffekseerForDXLib.h"
#include <string>
//Effekseerを用いたエフェクトクラス
class Effect
{
public:
	Effect(std::string handle,float size);
	~Effect();
	//再生
	bool Play();
	//停止
	bool Stop();
	//プロセス
	bool Process();
	//描画
	bool Draw();
	//アップデート
	//この関数は何回も呼び出す必要はないためマネージャーあるいはゲームメイン関数に
	bool Update();
	//Effekseer関数を使いやすくするように
	void SetPosEffekseer(int playhandle, Vector3D& pos);
	void SetDirEffekseer(int playhandle, Vector3D& dir);
	//ゲッター
	bool GetUseFlag()  const { return _useFlag; }
	bool GetPlayFlag() const { return _playFlag; }
	//セッター
	void SetPos(const Vector3D& v)	{ _pos = v; }
	void SetSize(const float s)		{ _size = s; }
	void SetDir(const Vector3D& v)	{ _dir = v; }
	void SetUseFlag(bool f)			{ _useFlag = f; }
protected:
	//ロードハンドル
	int _effectHandle;
	//再生ハンドル
	int _playHandle;
	//位置
	Vector3D _pos;
	//サイズ
	float _size;
	//向き
	Vector3D _dir;
	//再生可能フラグ
	bool _useFlag;
	//再生中フラグ
	bool _playFlag;

};

