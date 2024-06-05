#pragma once
#include "DxLib.h"
#include "../Vector3D/Vector3D.h"
#include <vector>
#include <string>
//オブジェクトの親クラス
//オブジェクトはこのクラス、またはこの派生クラスから生成
class ObjectBase
{
public:
	//状態
	enum class State
	{
		ACTIVE,
		PAUSE,
		DEAD
	};
	ObjectBase(class ModeBase* game);
	virtual ~ObjectBase();
	virtual void Initialize();
	virtual void Process();
	virtual void Render();
	virtual void Debug();
	//コンポーネント追加
	void AddComponent(class Component* component);
	//コンポーネント削除
	void RemoveComponent(class Component* component);
	//ゲッター
	Vector3D GetPos() { return mPos; }
	Vector3D GetRotation() const { return mRotation; }
	float GetScale() const { return mScale; }
	State GetState() const { return mState; }
	class ModeGame* GetGame() { return mGame; }
	//セッター
	void SetPos(const Vector3D& pos) { mPos = pos; }
	void SetRotation(Vector3D rot) { mRotation = rot; }
	void SetScale(float scale) { mScale = scale; }
	void SetState(State state) { mState = state; }
protected:
	//位置
	Vector3D mPos;
	//角度
	Vector3D mRotation;
	//スケール
	float mScale;
	//状態
	State mState;
	//コンポーネント
	std::vector<class Component*> mComponents;
	class ModeGame* mGame;

};

