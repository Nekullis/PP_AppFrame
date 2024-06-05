#pragma once
#include "DxLib.h"
#include "../Vector3D/Vector3D.h"
#include <vector>
#include <string>
//�I�u�W�F�N�g�̐e�N���X
//�I�u�W�F�N�g�͂��̃N���X�A�܂��͂��̔h���N���X���琶��
class ObjectBase
{
public:
	//���
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
	//�R���|�[�l���g�ǉ�
	void AddComponent(class Component* component);
	//�R���|�[�l���g�폜
	void RemoveComponent(class Component* component);
	//�Q�b�^�[
	Vector3D GetPos() { return mPos; }
	Vector3D GetRotation() const { return mRotation; }
	float GetScale() const { return mScale; }
	State GetState() const { return mState; }
	class ModeGame* GetGame() { return mGame; }
	//�Z�b�^�[
	void SetPos(const Vector3D& pos) { mPos = pos; }
	void SetRotation(Vector3D rot) { mRotation = rot; }
	void SetScale(float scale) { mScale = scale; }
	void SetState(State state) { mState = state; }
protected:
	//�ʒu
	Vector3D mPos;
	//�p�x
	Vector3D mRotation;
	//�X�P�[��
	float mScale;
	//���
	State mState;
	//�R���|�[�l���g
	std::vector<class Component*> mComponents;
	class ModeGame* mGame;

};

