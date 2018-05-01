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
	if (_index > documentReadBuffer["size"].GetUint())
		exit(0);
	const unsigned dataSize = documentReadBuffer["size"].GetUint();
	const rapidjson::Value& dataBlock = documentReadBuffer["datablock"];

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
	const unsigned dataSize = documentReadBuffer["size"].GetUint();
	const rapidjson::Value& dataBlock = documentReadBuffer["datablock"];

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
		jsonReadBuffer += dataTemp;
	}
	infile.close();
	documentReadBuffer.Parse(jsonReadBuffer.c_str());
}

void JsonHandler::SaveJson(const string & _filePath)
{
	ofstream outfile;
	outfile.open(_filePath);
	if(!outfile.is_open())
		exit(0);
	outfile << stringBuffer.GetString();
	
}

void JsonHandler::AppendVectorsToBuffer(const std::vector<MathLib::Vector<double>> & _vec)
{
	documentWriteBuffer.SetObject();
	rapidjson::Document::AllocatorType& allocator = documentWriteBuffer.GetAllocator();

	documentWriteBuffer.AddMember("class", "vector", allocator);
	documentWriteBuffer.AddMember("size", _vec.size(), allocator);

	rapidjson::Value array1(rapidjson::kArrayType);
	for (auto & vec : _vec)
	{
		rapidjson::Value array1obj(rapidjson::kObjectType);
		array1obj.AddMember("class", "vector", allocator);
		array1obj.AddMember("size", vec.Size(), allocator);

		rapidjson::Value array2(rapidjson::kArrayType);
		for (size_t i = 0; i < vec.Size(); i++)
		{
			array2.PushBack(vec(i), allocator);
		}
		array1obj.AddMember("data", array2, allocator);
		array1.PushBack(array1obj, allocator);
	}
	documentWriteBuffer.AddMember("datablock", array1, allocator);

	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(stringBuffer);
	documentWriteBuffer.Accept(writer);
}
