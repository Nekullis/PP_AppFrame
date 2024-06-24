#include "SoundItemBase.h"
#include "../SoundServer/SoundServer.h"


SoundItemBase::SoundItemBase(std::string filename) 
{
	_filename = filename;
	_snd = -1;
	_volume = 200;
	_pan = 0;
	_frequency = 0;		// �t�@�C���ɂ���ĕW�����Ⴄ�̂�
	_sndServer = NULL;
}
SoundItemBase::~SoundItemBase() 
{
	Unload();
}

void	SoundItemBase::Unload() 
{
	if (_snd != -1) 
	{
		DeleteSoundMem(_snd);
		_snd = -1;
	}
}

bool	SoundItemBase::IsLoad() 
{
	// �񓯊����[�h���I����Ă��邩�H
	if (_snd != -1 && CheckHandleASyncLoad(_snd) == false) 
	{
		return true;
	}
	return false;
}

bool	SoundItemBase::IsPlay() 
{
	if (_snd != -1 && CheckSoundMem(_snd) == 1) 
	{
		return true;
	}
	return false;
}

void	SoundItemBase::Stop() 
{
	if (_snd != -1) 
	{
		StopSoundMem(_snd);
	}
}

int		SoundItemBase::GetVolume() { return _volume; }
void	SoundItemBase::SetVolume(int volume) 
{
	_volume = volume;
	if (_snd != -1) 
	{
		ChangeVolumeSoundMem(_volume, _snd);
	}
}
int		SoundItemBase::GetPan() { return _pan; }
void	SoundItemBase::SetPan(int pan) 
{
	_pan = pan;
	if (_snd != -1) 
	{
		ChangePanSoundMem(_pan, _snd);
	}
}

int		SoundItemBase::GetFrequency() { return _frequency; }
void	SoundItemBase::SetFrequency(int frequency) 
{
	_frequency = frequency;
	if (_snd != -1 && _frequency != 0) 
	{
		SetFrequencySoundMem(_frequency, _snd);
	}
}
void	SoundItemBase::ResetFrequency() 
{
	_frequency = 0;
	if (_snd != -1) 
	{
		ResetFrequencySoundMem(_snd);
		_frequency = GetFrequencySoundMem(_snd);
	}
}

void	SoundItemBase::PlayMem(int flg) {
	// �Đ��O�ɉ��ʓ���ݒ�
	SetVolume(_volume);
	SetPan(_pan);
	SetFrequency(_frequency);
	PlaySoundMem(_snd, flg, TRUE);
}




void	SoundItemBGM::Play() {
	if (_sndServer) {
		_sndServer->StopType(TYPE::BGM);
	}
	// �X�g���[���Đ��̂��̂����[�h����
	StreamLoad();	
	if (IsPlay() == false) 
	{	
		// BGM�͍Đ�����Ă��Ȃ��ꍇ�̂�
		PlayMem(DX_PLAYTYPE_LOOP);
	}
}

void	SoundItemOneShot::Update() {
	int snd = _snd;
	base::Update();
	if (snd != -1 && _snd == -1) 
	{
		// �Đ�����Ă�����Unload()����Ă���ꍇ�A�������폜
		_sndServer->Del(this);
	}
}