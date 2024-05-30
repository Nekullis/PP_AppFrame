#pragma once
#include <string>
//�R���|�[�l���g(�\���v�f)�̐e�N���X
class Component
{
public:
	Component(class ObjectBase* owner, int updateowder = 100);
	virtual ~Component();
	//�X�V
	virtual void Update();
	//�Q�b�^�[
	int GetUpdateOwder() const { return mUpdateOwder; }
protected:
	//���L�I�u�W�F�N�g
	class ObjectBase* mOwner;
	//�X�V����
	int mUpdateOwder;
};

