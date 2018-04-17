/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        				              Log     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#include <string>
#include <chrono>

using namespace std;

string PrintInfo(void)
{
	string temp;
	temp += "Copyright 2015-2018 Celestial Tech Inc.\n";
	temp += "www.tianshicangxie.com\n\n\n";
	temp += "Deep Learning Developing Kit\n";
	temp += "Version : alpha\n\n";
	chrono::system_clock::time_point now =chrono::system_clock::now();
	time_t now_c = chrono::system_clock::to_time_t(now - chrono::hours(24));
	struct tm t;   //tm结构指针
	return temp;
}