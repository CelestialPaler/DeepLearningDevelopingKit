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

	
}

void JsonHandler::AppendVectorToBuffer(const MathLib::Vector<double>& _vec)
{
	documentWriteBuffer.SetObject();
	rapidjson::Document::AllocatorType& allocator = documentWriteBuffer.GetAllocator();

	rapidjson::Value object(rapidjson::kObjectType);
	object.AddMember("id", i, allocator);
	object.AddMember("name", "test", allocator);
	object.AddMember("version", 1.01, allocator);
	object.AddMember("vip", true, allocator);


	document.AddMember("size", _vec., allocator);
	document.AddMember("players", array, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	outfile << buffer.GetString();
}
