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
	//ゲッター
	int	GetModeCount() { return _cntMode; }			
	unsigned long GetModeTm() { return _tmMode; }	
	unsigned long GetStepTm() { return _tmStep; }	
	int GetCallPerFrame() { return _callPerFrame; }
	int GetCallOfCount() { return _callOfCount; }
	//セッター
	void SetCallPerFrame(int frame) { _callPerFrame = _callPerFrame_cnt = frame; }
	void SetCallOfCount(int count) { _callOfCount = count; }		
private:
	//ModeServer用
	friend ModeServer;
	//名前
	std::string _sName;
	//id
	int _uid;
	//レイヤー
	int _layer;
	//モード内処理
	//本モードに入ってからのカウンタ。0スタート
	int _cntMode;
	//本モードに入ってからの時間。単位ms
	unsigned long _tmMode;
	//前フレームからの経過時間。単位ms
	unsigned long _tmStep;
	//このモードが始まった時間。単位ms
	unsigned long _tmModeBase;
	//ポーズ中のベース時間。単位ms
	unsigned long _tmPauseBase;
	//ポーズ中の積算時間。単位ms、動作中、この値を _tmMode に用いる
	unsigned long _tmPauseStep;
	//前フレームの時間。ms
	unsigned long _tmOldFrame;
	// 何フレームに1回Process()を呼ぶか(def:1)
	int		_callPerFrame, _callPerFrame_cnt;
	// 1回の呼び出しに何回Process()を呼ぶか(def:1)
	int		_callOfCount;

};

