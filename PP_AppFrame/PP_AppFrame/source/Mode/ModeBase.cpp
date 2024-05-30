#include "ModeBase.h"

ModeBase::ModeBase()
{
	_cntMode = 0;
	_tmMode = 0;
	_tmStep = 0;
	_tmModeBase = 0;
	_tmPauseBase = 0;
	_tmPauseStep = 0;
	_tmOldFrame = 0;
	SetCallPerFrame(1);
	SetCallOfCount(1);
}

ModeBase::~ModeBase()
{
}

bool ModeBase::Initialize()
{
	return true;
}

bool ModeBase::Terminate()
{
	return true;
}

bool ModeBase::Input()
{
	return true;
}

bool ModeBase::Process()
{
	return true;
}

bool ModeBase::Render()
{
	return true;
}

void ModeBase::StepTime(unsigned long tmnow)
{
	//éûä‘åoâﬂèàóù
	if (_cntMode == 0)
	{
		_tmMode = 0;
		_tmStep = 0;
		_tmModeBase = tmnow;
		_tmPauseBase = 0;
		_tmPauseStep = 0;
	}
	else
	{
		_tmMode = tmnow - _tmModeBase + _tmPauseStep;
		_tmStep = tmnow - _tmOldFrame;
	}
	_tmOldFrame = tmnow;
}

void ModeBase::StepCount()
{
	_cntMode++;
}
