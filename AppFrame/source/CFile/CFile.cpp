#include "CFile.h"
#include <fstream>
#include <iostream>

//読み込み
CFile::CFile(const std::string filename)
{
	//初期化
	Init();
	_fileName = filename;
	//ファイルを開く
	//入力をバイナリ形式(2進数に変換できるもの)で
	std::ifstream ifs(filename, std::ios::in | std::ios::binary);
	//開くことを失敗したなら返す
	if (!ifs) { return; }
	//ファイルサイズを取得
	ifs.seekg(0, std::ios_base::end);
	_size = (int)ifs.tellg();
	ifs.seekg(0, std::ios_base::beg);
	//メモリの確保
	_data = new char[_size + 1];
	//ファイルをロード
	ifs.read(_data, _size);
	//ファイルを閉じる
	ifs.close();
	//文字列として利用できるように
	_data[_size] = '\0';
	//処理成功
	_success = true;
}

//書き込み
CFile::CFile(const std::string filename, void* data, int size)
{
	//初期化
	Init();
	_fileName = filename;
	//ファイルを開く
	//入力をバイナリ形式(2進数に変換できるもの)で
	std::ofstream ofs(filename, std::ios::in | std::ios::binary);
	//開くことを失敗したなら返す
	if (!ofs) { return; }
	//データ書き込み
	ofs.write((char*) data, size);
	//ファイルを閉じる
	ofs.close();
	//処理成功
	_success = true;
}

CFile::~CFile()
{
	SAFE_DELETE(_data);
}

void CFile::Init()
{
	_size = 0;
	_data = NULL;
	_fileName = "";
	_success = false;
}
