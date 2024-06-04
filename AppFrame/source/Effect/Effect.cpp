#include "Effect.h"

Effect::Effect(std::string handle, float size)
{
	//位置
	_pos = Vector3D(0, 0, 0);
	//サイズ
	_size = size;
	//向き
	_dir = Vector3D(0, 0, 0);
	//ハンドルのロード
	_effectHandle = LoadEffekseerEffect(handle.c_str(), _size);
	//再生可能フラグをtrueに
	_useFlag = true;
	//再生中フラグはfalseに
	_playFlag = false;
	//位置の更新
	SetPosEffekseer(_playHandle, _pos);
}

Effect::~Effect()
{
	//エフェクトリソースの削除
	DeleteEffekseerEffect(_effectHandle);
}

void Effect::SetPosEffekseer(int playhandle, Vector3D& pos)
{
	SetPosPlayingEffekseer3DEffect(playhandle, pos._x, pos._y, pos._z);
}

void Effect::SetDirEffekseer(int playhandle, Vector3D& dir)
{
	SetRotationPlayingEffekseer3DEffect(playhandle, dir._x, dir._y, dir._z);
}

bool Effect::Play()
{
	//再生可能ならエフェクトの再生
	if (_useFlag) { _playHandle = PlayEffekseer3DEffect(_effectHandle); }
	//再生中なら再生中フラグをtrueに
	if (_playHandle != -1) { _playFlag = true; }
	return true;
}

bool Effect::Stop()
{
	//再生の停止
	StopEffekseer3DEffect(_playHandle);
	return true;
}

bool Effect::Process()
{
	//位置の更新
	SetPosEffekseer(_playHandle, _pos);
	//角度の更新
	SetDirEffekseer(_playHandle, _dir);
	return true;
}

bool Effect::Draw()
{
	//エフェクトの描画
	DrawEffekseer3D();
	return true;
}

bool Effect::Update()
{
	//DXライブラリのカメラとEffekseerカメラの同期
	Effekseer_Sync3DSetting();
	//Effekseer更新
	UpdateEffekseer3D();
	return true;
}


