#pragma once
#include <string>
#include "DxLib.h"

class SoundServer;

class SoundItemBase
{
public:
	enum class TYPE 
	{
		//�X�g���[�~���O�B���[�v�Đ�
		BGM = 0,
		//�P��̂ݍĐ�
		SE,
		//�X�g���[�~���O�B�P��̂ݍĐ�
		VOICE,
		//�X�g���[�~���O�B�P��̂ݍĐ��B�����Đ����A��~������T�[�o����폜
		ONESHOT,
	};
	SoundItemBase(std::string filename);
	virtual ~SoundItemBase();
	void SetSoundServer(SoundServer* sndServer) { _sndServer = sndServer; }

	virtual void	Unload();
	virtual bool	IsLoad();
	virtual void	Play() = 0;
	virtual bool	IsPlay();
	virtual void	Stop();
	virtual void	ResetFrequency();
	//�Q�b�^�[
	virtual int		GetVolume();
	virtual int		GetPan();
	virtual int		GetFrequency();
	virtual TYPE	GetType() = 0;
	virtual std::string GetFileName() { return _filename; }
	virtual int		GetSoundHandle() { return _snd; }
	//�Z�b�^�[
	virtual void	SetFrequency(int frequency);
	virtual void	SetVolume(int volume);
	virtual void	SetPan(int pan);
	
	virtual void	Update() {}
	
	

protected:
	virtual void	PlayMem(int flg);

	int		_snd;
	std::string	_filename;
	int		_volume;
	int		_pan;
	int		_frequency;
	SoundServer* _sndServer;
};

class SoundItemStatic : public SoundItemBase
{
	typedef	SoundItemBase	base;
public:
	SoundItemStatic(std::string filename) : base(filename) {
		SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
		_snd = LoadSoundMem(_filename.c_str());
		if (_frequency == 0) {
			_frequency = GetFrequencySoundMem(_snd);
		}
	}
	virtual ~SoundItemStatic() {}
};

class SoundItemSE : public SoundItemStatic
{
	typedef	SoundItemStatic	base;
public:
	SoundItemSE(std::string filename) : base(filename) {
	}
	virtual TYPE	GetType() { return TYPE::SE; }
	virtual void	Play() {
		Stop();		// SE�͈�x�~�߂Ă���
		PlayMem(DX_PLAYTYPE_BACK);
	}
};



class SoundItemStream : public SoundItemBase
{
	typedef	SoundItemBase	base;
public:
	SoundItemStream(std::string filename) : base(filename) {
	}
	virtual ~SoundItemStream() {}
	virtual bool	IsLoad() { return true; }	// �X�g���[���Đ��̂��̂́A���[�h����Ă�����̂Ƃ���
protected:
	void	StreamLoad() {
		if (_snd == -1) {
			SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
			_snd = LoadSoundMem(_filename.c_str());
			if (_frequency == 0) {
				_frequency = GetFrequencySoundMem(_snd);
			}
		}
	}
	virtual void	Update() {
		if (_snd != -1) {
			if (IsPlay() == false) {
				Unload();		// �X�g���[���Đ��̂��̂́A�Đ����Ă��Ȃ������烁��������A�����[�h����
			}
		}
	}
};

class SoundItemBGM : public SoundItemStream
{
	typedef	SoundItemStream	base;
public:
	SoundItemBGM(std::string filename) : base(filename) {
	}
	virtual TYPE	GetType() { return TYPE::BGM; }
	virtual void	Play();
};

class SoundItemVOICE : public SoundItemStream
{
	typedef	SoundItemStream	base;
public:
	SoundItemVOICE(std::string filename) : base(filename) {
	}
	virtual TYPE	GetType() { return TYPE::VOICE; }
	virtual void	Play() {
		StreamLoad();	// �X�g���[���Đ��̂��̂����[�h����
		if (IsPlay() == false) {	// VOICE�͍Đ�����Ă��Ȃ��ꍇ�̂�
			PlayMem(DX_PLAYTYPE_BACK);
		}
	}
};

class SoundItemOneShot : public SoundItemStream
{
	typedef	SoundItemStream	base;
public:
	SoundItemOneShot(std::string filename) : base(filename) {
	}
	virtual TYPE	GetType() { return TYPE::ONESHOT; }
	virtual void	Play() {
		StreamLoad();	// �X�g���[���Đ��̂��̂����[�h����
		PlayMem(DX_PLAYTYPE_BACK);
	}
	virtual void	Update();

};

