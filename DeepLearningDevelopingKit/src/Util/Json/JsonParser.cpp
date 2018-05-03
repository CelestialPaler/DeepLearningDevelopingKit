/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 			  Json Parser 	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#include "JsonParser.h"

void VectorParser::Serialize(const std::string & _filePath, const std::vector<MathLib::Vector<double>>& _vectors)
{
	std::vector<MathLib::Vector<double>> tempBuffer;
	JsonHandler jsonhandler;

	jsonhandler.documentWriteBuffer.SetObject();
	rapidjson::Document::AllocatorType& allocator = jsonhandler.documentWriteBuffer.GetAllocator();

	jsonhandler.documentWriteBuffer.AddMember("class", "vector", allocator);
	jsonhandler.documentWriteBuffer.AddMember("size", _vectors.size(), allocator);

	rapidjson::Value array1(rapidjson::kArrayType);
	for (auto & vec : _vectors)
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
	jsonhandler.documentWriteBuffer.AddMember("datablock", array1, allocator);

	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(jsonhandler.stringBuffer);
	jsonhandler.documentWriteBuffer.Accept(writer);

	jsonhandler.SaveJson(_filePath);
}

std::vector<MathLib::Vector<double>> VectorParser::Deserialize(const std::string & _filePath)
{
	std::vector<MathLib::Vector<double>> tempBuffer;
	JsonHandler jsonhandler;
	jsonhandler.OpenJson(_filePath);

	const unsigned dataSize = jsonhandler.documentReadBuffer["size"].GetUint();
	const rapidjson::Value& dataBlock = jsonhandler.documentReadBuffer["datablock"];

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
