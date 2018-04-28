/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              DataSet     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include "DataSet.h"

Data::NumaricSet::NumaricSet()
{

}

void Data::NumaricSet::InitWithXOR(void)
{
	Vector<double> input1(2, VectorType::Zero);
	input1(0) = 0;  input1(1) = 0;
	Vector<double> target1(1, VectorType::Zero);
	target1(0) = 0;
	NumaricSet::Sample tempSample1 = { input1 , target1 };
	AddToSet(tempSample1);

	Vector<double> input2(2, VectorType::Zero);
	input2(0) = 0;  input2(1) = 1;
	Vector<double> target2(1, VectorType::Zero);
	target2(0) = 1;
	NumaricSet::Sample tempSample2 = { input2 , target2 };
	AddToSet(tempSample2);

	Vector<double> input3(2, VectorType::Zero);
	input3(0) = 1;  input3(1) = 0;
	Vector<double> target3(1, VectorType::Zero);
	target3(0) = 1;
	NumaricSet::Sample tempSample3 = { input3 , target3 };
	AddToSet(tempSample3);

	Vector<double> input4(2, VectorType::Zero);
	input4(0) = 1;  input4(1) = 1;
	Vector<double> target4(1, VectorType::Zero);
	target4(0) = 0;
	NumaricSet::Sample tempSample4 = { input4 , target4 };
	AddToSet(tempSample4);
}

void Data::NumaricSet::AddToSet(const Sample & _sample)
{
	_data.push_back(_sample);
}

Data::NumaricSet::Sample Data::NumaricSet::GetBatch(void)
{
	static int x = 0;
	x++;
	if (x==_data.size())
		x = 0;
	return _data.at(x);
}

Data::NumaricSet::Sample Data::NumaricSet::GetRandomSample(void)
{
	return _data.at(floor((Random() + 1) * 3 - 1));
}

Data::NumaricSet::Sample Data::NumaricSet::GetSample(const size_t _index)
{
	return _data.at(_index);
}

