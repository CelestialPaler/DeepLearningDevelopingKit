/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	             Math Test   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header FIle
#include <iostream>

#include "..\Nerual\Node.h"
#include "..\Nerual\Layer.h"

#define LayerDebug
using namespace Nerual;

#ifdef NodeDebug
int main()
{
	InputNode InputNode1;
	HiddenNode HiddenNode1(2);
	OutputNode OutputNode1(10);

	cout << OutputNode1;

	system("pause");
	return 0;
}
#endif // NodeDebug

#ifdef LayerDebug
int main()
{
	InputLayer inputLayer(2);
	HIddenLayer hiddenLayer(10, 2);

	cout << inputLayer;

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
