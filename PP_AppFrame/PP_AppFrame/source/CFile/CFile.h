#pragma once
#include <string>
#define	SAFE_DELETE(x)	if(x){delete x;x=NULL;}
//テキストファイルの読み込み、書き込みクラス
class CFile
{
public:
	//読み込み
	CFile(const std::string filename);
	//書き込み
	CFile(const std::string filename, void* data, int size);
	CFile(const std::string filename, const std::string writestr) :CFile(filename, (void*)writestr.c_str(), writestr.size())
	{
		//委任コンストラクタ : コンストラクタから、同じクラスの他のコンストラクタに処理を委譲する機能
	}
	~CFile();
	//ゲッター
	std::string GetName() { return _fileName; }
	void* GetData() { return _data; }
	std::string GetDataStr() { return std::string(_data); }
	int GetSize() { return _size; }
	bool GetSuccess() { return _success; }
private:
	//初期化
	void Init();
	//ファイル名
	std::string _fileName;
	//サイズ
	int _size;
	//データ
	char* _data;
	//成功したか
	bool _success;
};

