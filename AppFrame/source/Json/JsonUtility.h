#pragma once
#include "nlohmann/json.hpp"
#include <fstream>

class JsonUtility
{
public:
	JsonUtility();
	virtual ~JsonUtility();

	void Init() { json = nullptr; }
	//�ǂݍ��݁E��������
	//���̃N���X��json�f�[�^�ɊO����json�t�@�C����ǂݍ���
	nlohmann::json Import(const std::string& filepath);
	//json�f�[�^�̒��̈�v�f���w�肵�������o�ϐ��ɑ��
	template <typename T>
	void Read(const std::string& jmem, T& mem);
	//���N���X�ŕύX���ꂽ�f�[�^�����̃N���X�ŕێ����Ă���json�f�[�^�ɏ㏑���������͒ǉ�����
	//std::string jdata = R"({ ~�ʏ��json�t�@�C���̋L�q~ })"; �@�@�������ċL�q����
	void StrWrite(const std::string& jdata);
	template <typename T>
	// ���̃N���X�ŕۗL���Ă���json�t�@�C���Ɉ�v�f���㏑���������͒ǉ�
	void JsonWrite(const std::string& name, const T& variable);
	void Save(const std::string& filename);
	nlohmann::json GetJson() { return json; }
protected:
	nlohmann::json json;
};

template<typename T>
inline void JsonUtility::Read(const std::string& jmem, T& mem)
{
	json.at(jmem).get_to(mem);
}

template<typename T>
inline void JsonUtility::JsonWrite(const std::string& name, const T& variable)
{
	json[name] = variable;
}
