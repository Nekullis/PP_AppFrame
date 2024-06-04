#pragma once
#include <string>
#define	SAFE_DELETE(x)	if(x){delete x;x=NULL;}
//�e�L�X�g�t�@�C���̓ǂݍ��݁A�������݃N���X
class CFile
{
public:
	//�ǂݍ���
	CFile(const std::string filename);
	//��������
	CFile(const std::string filename, void* data, int size);
	CFile(const std::string filename, const std::string writestr) :CFile(filename, (void*)writestr.c_str(), writestr.size())
	{
		//�ϔC�R���X�g���N�^ : �R���X�g���N�^����A�����N���X�̑��̃R���X�g���N�^�ɏ������Ϗ�����@�\
	}
	~CFile();
	//�Q�b�^�[
	std::string GetName() { return _fileName; }
	void* GetData() { return _data; }
	std::string GetDataStr() { return std::string(_data); }
	int GetSize() { return _size; }
	bool GetSuccess() { return _success; }
private:
	//������
	void Init();
	//�t�@�C����
	std::string _fileName;
	//�T�C�Y
	int _size;
	//�f�[�^
	char* _data;
	//����������
	bool _success;
};

