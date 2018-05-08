/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 			   Timer Test   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define TimerDebug

#ifdef TimerDebug
#include <iostream>
#include<windows.h>  
#include "..\Util\Timer\Time.hpp"

using namespace std;
using Util::Timer;

int main()
{
	Timer debugTimer;
	debugTimer.Start();
	for (size_t i = 0; i < 10; i++)
	{
		cout << debugTimer.GetTime() << endl;
		std::string tag = "Check Point";
		debugTimer.AddTimeCheckPoint();
		Sleep(100);
	}

	debugTimer.PrintTimeCheckPoint();

	system("pause");
	return 0;
}
#endif // TimerDebug

