#include "JsonUtility.h"

JsonUtility::JsonUtility()
{
	json = nullptr;
}

JsonUtility::~JsonUtility()
{
}

nlohmann::json JsonUtility::Import(const std::string& filepath)
{
	std::ifstream file(filepath);
	file >> json;
	return json;
}

void JsonUtility::StrWrite(const std::string& jdata)
{
	json = nlohmann::json::parse(jdata);
}

void JsonUtility::Save(const std::string& filename)
{
	std::ofstream file(filename);
	file << std::setw(3) << json << std::endl;
}
