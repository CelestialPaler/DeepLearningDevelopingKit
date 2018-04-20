/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	          Module Test   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#define ModuleDebug

#ifdef ModuleDebug
#include "..\Nerual\NerualLib.h"

using namespace Nerual;

int main()
{
	NumaricSet TrainSet;
	NumaricSet TestSet;

	Vector<double> input1(2, VectorType::Zero);
	input1(0) = 0;
	input1(1) = 0;
	Vector<double> target1(1, VectorType::Zero);
	target1(0) = 0;
	NumaricSet::Sample tempSample1;
	tempSample1.first = input1;
	tempSample1.second = target1;
	TrainSet.AddToSet(tempSample1);

	Vector<double> input2(2, VectorType::Zero);
	input2(0) = 0;
	input2(1) = 1;
	Vector<double> target2(1, VectorType::Zero);
	target2(0) = 1;
	NumaricSet::Sample tempSample2;
	tempSample2.first = input2;
	tempSample2.second = target2;
	TrainSet.AddToSet(tempSample2);

	Vector<double> input3(2);
	input3(0) = 1;
	input3(1) = 0;
	Vector<double> target3(1, VectorType::Random);
	target3(0) = 1;
	NumaricSet::Sample tempSample3;
	tempSample3.first = input3;
	tempSample3.second = target3;
	TrainSet.AddToSet(tempSample3);

	Vector<double> input4(2);
	input4(0) = 1;
	input4(1) = 1;
	Vector<double> target4(1, VectorType::Random);
	target4(0) = 0;
	NumaricSet::Sample tempSample4;
	tempSample4.first = input4;
	tempSample4.second = target4;
	TrainSet.AddToSet(tempSample4);

	/*
	Vector<double> input5(2);
	input5(0) = 0;
	input5(1) = 0;
	Vector<double> target5(1, VectorType::Random);
	target5(0) = 0;
	NumaricSet::Sample tempSample5;
	tempSample5.first = input5;
	tempSample5.second = target5;
	TestSet.AddToSet(tempSample5);

	Vector<double> input6(2);
	input6(0) = 1;
	input6(1) = 0;
	Vector<double> target6(1, VectorType::Random);
	target6(0) = 1;
	NumaricSet::Sample tempSample6;
	tempSample6.first = input6;
	tempSample6.second = target6;
	TestSet.AddToSet(tempSample6);
	*/

	InputLayer in(2, 2);
	HiddenLayer hidden1(2, 10), hidden2(10, 3), hidden3(3, 9);
	OutputLayer out(9, 1);

	BPNet TestBP1;
	TestBP1.PushLayer(&in);
	TestBP1.PushLayer(&hidden1);
	TestBP1.PushLayer(&hidden2);
	TestBP1.PushLayer(&hidden3);
	TestBP1.PushLayer(&out);

	TestBP1.SetTrainSet(&TrainSet);
	// TestBP1.SetTestSet(&TestSet);
	TestBP1.Train();

	system("pause");
	return 0;
}

#endif // ModuleDebug
