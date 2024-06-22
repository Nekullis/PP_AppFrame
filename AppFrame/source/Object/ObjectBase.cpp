#include "ObjectBase.h"
#include <algorithm>
#include "../Component/Component.h"
ObjectBase::ObjectBase(ModeBase* game)
{
	//�ʒu
	mPos = { 0 };
	//�p�x
	mRotation = { 0 };
	//�X�P�[��
	mScale = 0;
	mIsTargetting = false;
}

ObjectBase::~ObjectBase()
{

}

void ObjectBase::Process()
{
	for(auto&& comp : mComponents)
	{
		comp->Update();
	}
}

void ObjectBase::Render()
{
	
	
#if _DEBUG
	Debug();
#endif
}

void ObjectBase::Debug()
{

}

void ObjectBase::AddComponent(Component* component)
{
	//�R���e�i�Ɋi�[����
	mComponents.push_back(component);
	//�i�[�����R���|�[�l���g�̕��ёւ�
	std::sort(mComponents.begin(), mComponents.end(), [](Component* a, Component* b) {return a->GetUpdateOwder() < b->GetUpdateOwder(); });
}

void ObjectBase::RemoveComponent(Component* component)
{
	//�����ɍ����R���|�[�l���g��T��
	auto itr = std::find(mComponents.begin(), mComponents.end(), component);
	//�T�����R���|�[�l���g�̏���
	if (itr != mComponents.end()) { mComponents.erase(itr); }
}

