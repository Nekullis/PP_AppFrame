#pragma once
#include <string>
#include <map>
#include "../SoundItem/SoundItemBase.h"

class SoundServer
{
public:
	SoundServer();
	virtual ~SoundServer();

	void Clear();
	void Add(SoundItemOneShot* snd);
	void Add(std::string name, SoundItemBase* snd);
	bool Del(std::string name);
	bool Del(SoundItemBase* snd);
	SoundItemBase* Get(std::string name);
	std::map<std::string, SoundItemBase*>& GetVector() { return _v; }
	void StopType(SoundItemBase::TYPE type);
	void Update();

protected:
	bool	_isUpdate;
	std::map<std::string, SoundItemBase*> _v;
	std::map<std::string, SoundItemBase*> _vAdd;
	std::map<std::string, SoundItemBase*> _vDel;
	int		_cntOneShot;
};

