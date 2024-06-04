#include "CFile.h"
#include <fstream>
#include <iostream>

//�ǂݍ���
CFile::CFile(const std::string filename)
{
	//������
	Init();
	_fileName = filename;
	//�t�@�C�����J��
	//���͂��o�C�i���`��(2�i���ɕϊ��ł������)��
	std::ifstream ifs(filename, std::ios::in | std::ios::binary);
	//�J�����Ƃ����s�����Ȃ�Ԃ�
	if (!ifs) { return; }
	//�t�@�C���T�C�Y���擾
	ifs.seekg(0, std::ios_base::end);
	_size = (int)ifs.tellg();
	ifs.seekg(0, std::ios_base::beg);
	//�������̊m��
	_data = new char[_size + 1];
	//�t�@�C�������[�h
	ifs.read(_data, _size);
	//�t�@�C�������
	ifs.close();
	//������Ƃ��ė��p�ł���悤��
	_data[_size] = '\0';
	//��������
	_success = true;
}

//��������
CFile::CFile(const std::string filename, void* data, int size)
{
	//������
	Init();
	_fileName = filename;
	//�t�@�C�����J��
	//���͂��o�C�i���`��(2�i���ɕϊ��ł������)��
	std::ofstream ofs(filename, std::ios::in | std::ios::binary);
	//�J�����Ƃ����s�����Ȃ�Ԃ�
	if (!ofs) { return; }
	//�f�[�^��������
	ofs.write((char*) data, size);
	//�t�@�C�������
	ofs.close();
	//��������
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
