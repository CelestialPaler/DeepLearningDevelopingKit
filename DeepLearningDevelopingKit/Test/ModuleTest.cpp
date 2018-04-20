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
	Vector<double> input(2);
	input(0) = 0;
	input(1) = 0;
	Vector<double> target(2, VectorType::Random);
	target(0) = 0;
	target(1) = 0;
	Vector<double> output(1);

	{
		InputLayer in(2, 2);
		HiddenLayer hidden1(2, 10), hidden2(10, 3), hidden3(3, 9);
		OutputLayer out(9, 1);

		BPNet TestBP1;
		TestBP1.PushLayer(&in);
		TestBP1.PushLayer(&hidden1);
		TestBP1.PushLayer(&hidden2);
		TestBP1.PushLayer(&hidden3);
		TestBP1.PushLayer(&out);
	}
	
	{
		BPNetInitor MyNewBP{ {2,10,15,12,13,1} };

		BPNet myBP;

		myBP.Train();
	}

	system("pause");
	return 0;
}

#endif // ModuleDebug
