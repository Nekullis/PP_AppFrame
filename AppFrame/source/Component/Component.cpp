#include "Component.h"
#include "../Object/ObjectBase.h"
Component::Component(ObjectBase* owner, int updateowder)
{
	mOwner = owner;
	mUpdateOwder = updateowder;
	//mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::Update()
{

}
