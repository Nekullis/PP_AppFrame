#pragma once
#include <string>
//コンポーネント(構成要素)の親クラス
class Component
{
public:
	Component(class ObjectBase* owner, int updateowder = 100);
	virtual ~Component();
	//更新
	virtual void Update();
	//ゲッター
	int GetUpdateOwder() const { return mUpdateOwder; }
protected:
	//所有オブジェクト
	class ObjectBase* mOwner;
	//更新順序
	int mUpdateOwder;
};

