/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	             Math Test   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header FIle
#include <iostream>

#include "..\Nerual\Node.h"

// #define NodeDebug
using namespace Nerual;

#ifdef NodeDebug
int main()
{
	cout << PrintInfo() << "Node Test" << endl;
	InputNode InputNode1;

	cout << InputNode1;

	system("pause");
	return 0;
}
#endif // NodeDebug

#ifdef LayerDebug
int main()
{
	cout << "Layer Uint Test" << endl;
	InputLayer<2, 2> inputLayer;
	HiddenLayer<2, 100> hiddenLayer1;
	HiddenLayer<100, 100> hiddenLayer2;
	HiddenLayer<100, 100> hiddenLayer3;
	HiddenLayer<100, 100> hiddenLayer4;
	HiddenLayer<100, 100> hiddenLayer5;
	OutputLayer<100, 1> outputLayer;

	double data[] = { 0.3, 0.7 };
	Vector<double, 2> input(data);

	inputLayer.SetInput(input);
	inputLayer.Forward();

	hiddenLayer1.SetInput(inputLayer.Output());
	hiddenLayer1.Forward();
	hiddenLayer2.SetInput(hiddenLayer1.Output());
	hiddenLayer2.Forward();
	hiddenLayer3.SetInput(hiddenLayer2.Output());
	hiddenLayer3.Forward();
	hiddenLayer4.SetInput(hiddenLayer3.Output());
	hiddenLayer4.Forward();
	hiddenLayer5.SetInput(hiddenLayer4.Output());
	hiddenLayer5.Forward();

	outputLayer.SetInput(hiddenLayer5.Output());
	outputLayer.Forward();

	outputLayer.Output().PrintToConsole();

	system("pause");
	return 0;
}
#endif // LayerDebug

#ifdef ModuleDebug

int main()
{
	InputLayer<2, 2> inputLayer;
	HiddenLayer<2, 5> hiddenLayer;
	OutputLayer<5, 1> outputLayer;

	InputPort<2, 1> inputPort;
	OutputPort<1, 1> outputPort;

	system("pause");
	return 0;
}
#endif // ModuleDebug
