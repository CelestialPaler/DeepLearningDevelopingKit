/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              DataSet     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include "DataSet.h"

Data::NumericSet::NumericSet()
{

}

void Data::NumericSet::LoadFromJson(const std::string & _filePath)
{
	Deserialize(_filePath);
}

void Data::NumericSet::AddToSet(const Sample & _sample)
{
	_samples.push_back(_sample);
}

void Data::NumericSet::Serialize(const std::string & _filePath, const std::vector<Sample>& _samples) const
{

}

void Data::NumericSet::Deserialize(const std::string & _filePath)
{
	JsonHandler jsonhandler;
	jsonhandler.OpenJson(_filePath);

	name = jsonhandler.documentReadBuffer["name"].GetString();
	sampleSize = jsonhandler.documentReadBuffer["sample_size"].GetUint();
	inputSize = jsonhandler.documentReadBuffer["input_size"].GetUint();
	lableSize = jsonhandler.documentReadBuffer["lable_size"].GetUint();
	const rapidjson::Value& dataBlock = jsonhandler.documentReadBuffer["datablock"];

	for (size_t i = 0; i < sampleSize; i++)
	{
		const rapidjson::Value& sample = dataBlock[i];

		Vector<double> input(inputSize, VectorType::Zero);
		Vector<double> lable(lableSize, VectorType::Zero);

		const rapidjson::Value& data1 = sample["input"];
		for (rapidjson::SizeType i = 0; i < inputSize; i++)
			input(i) = data1[i].GetDouble();

		const rapidjson::Value& data2 = sample["lable"];
		for (rapidjson::SizeType i = 0; i < lableSize; i++)
			lable(i) = data2[i].GetDouble();

		Sample tempSample = { input, lable };
		_samples.push_back(tempSample);
	}
}

const Data::NumericSet::Sample Data::NumericSet::GetBatch(void) const
{
	static int x = 0;
	x++;
	if (x==_samples.size())
		x = 0;
	return _samples.at(x);
}

const Data::NumericSet::Sample Data::NumericSet::GetRandomSample(void) const
{
	return _samples.at(floor((Random() + 1) * 3 - 1));
}

const Data::NumericSet::Sample Data::NumericSet::GetSample(const size_t _index) const
{
	return _samples.at(_index);
}

void Data::NumericSet::PrintToConsole(void)
{
	std::cout << "Dataset Name: " << name << std::endl;
	std::cout << std::fixed << std::setprecision(5) << std::endl;
	for (size_t i = 0; i < sampleSize; i++)
	{
		std::cout << "No. "<< std::setw(4) << std::setfill('0') << i << "  Input: [";
		for (size_t j = 0; j < inputSize; j++)
			std::cout << _samples[i].first(j) << " ";
		std::cout << "]  |  Lable: [";
		for (size_t j = 0; j < lableSize; j++)
			std::cout << _samples[i].second(j) << " ";
		std::cout << "]" << std::endl;
	}
}

