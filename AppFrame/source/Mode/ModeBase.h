#pragma once
#include<string>
class ModeServer;
class ModeBase
{
public:
	ModeBase();
	virtual ~ModeBase();
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();
	void StepTime(unsigned long tmnow);
	void StepCount();
	//�Q�b�^�[
	int	GetModeCount() { return _cntMode; }			
	unsigned long GetModeTm() { return _tmMode; }	
	unsigned long GetStepTm() { return _tmStep; }	
	int GetCallPerFrame() { return _callPerFrame; }
	int GetCallOfCount() { return _callOfCount; }
	//�Z�b�^�[
	void SetCallPerFrame(int frame) { _callPerFrame = _callPerFrame_cnt = frame; }
	void SetCallOfCount(int count) { _callOfCount = count; }		
private:
	//ModeServer�p
	friend ModeServer;
	//���O
	std::string _sName;
	//id
	int _uid;
	//���C���[
	int _layer;
	//���[�h������
	//�{���[�h�ɓ����Ă���̃J�E���^�B0�X�^�[�g
	int _cntMode;
	//�{���[�h�ɓ����Ă���̎��ԁB�P��ms
	unsigned long _tmMode;
	//�O�t���[������̌o�ߎ��ԁB�P��ms
	unsigned long _tmStep;
	//���̃��[�h���n�܂������ԁB�P��ms
	unsigned long _tmModeBase;
	//�|�[�Y���̃x�[�X���ԁB�P��ms
	unsigned long _tmPauseBase;
	//�|�[�Y���̐ώZ���ԁB�P��ms�A���쒆�A���̒l�� _tmMode �ɗp����
	unsigned long _tmPauseStep;
	//�O�t���[���̎��ԁBms
	unsigned long _tmOldFrame;
	// ���t���[����1��Process()���ĂԂ�(def:1)
	int		_callPerFrame, _callPerFrame_cnt;
	// 1��̌Ăяo���ɉ���Process()���ĂԂ�(def:1)
	int		_callOfCount;

};

