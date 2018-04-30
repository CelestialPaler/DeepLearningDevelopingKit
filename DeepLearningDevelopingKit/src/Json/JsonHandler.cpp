/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 			  Json Handler 	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#include "JsonHandler.h"

JsonHandler::JsonHandler()
{

}

MathLib::Vector<double> JsonHandler::ParseVector(const size_t _index) const
{
	if (_index > document["size"].GetUint())
		exit(0);
	const unsigned dataSize = document["size"].GetUint();
	const rapidjson::Value& dataBlock = document["datablock"];

	const rapidjson::Value& vector = dataBlock[_index];

	unsigned size = vector["size"].GetUint();
	MathLib::Vector<double> resultVec(size);

	const rapidjson::Value& data = vector["data"];
	for (rapidjson::SizeType i = 0; i < data.Size(); i++)
		resultVec(i) = data[i].GetDouble();

	return resultVec;
}

std::vector<MathLib::Vector<double>> JsonHandler::ParseAllVector(void) const
{
	std::vector<MathLib::Vector<double>> tempBuffer;
	const unsigned dataSize = document["size"].GetUint();
	const rapidjson::Value& dataBlock = document["datablock"];

	for (size_t i = 0; i < dataSize; i++)
	{
		const rapidjson::Value& vector = dataBlock[i];

		unsigned size = vector["size"].GetUint();
		MathLib::Vector<double> tempVec(size);

		const rapidjson::Value& data = vector["data"];
		for (rapidjson::SizeType i = 0; i < data.Size(); i++)
			tempVec(i) = data[i].GetDouble();

		tempBuffer.push_back(tempVec);
	}
	return tempBuffer;
}

void JsonHandler::OpenFile(const string & _filePath)
{
	
}

void JsonHandler::OpenJson(const string & _filePath)
{
	ifstream infile;
	infile.open(_filePath);
	if (!infile.is_open())
		exit(0);
	string dataTemp;
	while (getline(infile, dataTemp))
	{
		jsonBuffer += dataTemp;
	}
	infile.close();
	document.Parse(jsonBuffer.c_str());
}

void JsonHandler::SaveJson(const string & _filePath, const string & _newdata)
{
	ofstream outfile;
	outfile.open(_filePath);
	if(!outfile.is_open())
		exit(0);
	string data;
}
