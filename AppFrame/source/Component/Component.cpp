#include "Component.h"

Component::Component(ObjectBase* owner, int updateowder)
{
	mOwner = owner;
	mUpdateOwder = updateowder;
}

Component::~Component()
{
}

void Component::Update()
{

}
