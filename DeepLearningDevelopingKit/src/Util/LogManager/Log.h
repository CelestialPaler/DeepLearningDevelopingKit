/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        				              Port     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include <iostream>
#include <string>
#include <chrono>
#include <windows.h>

// Namespaces
using namespace std;

void PrintTitle(void)
{
	string temp;
	temp += "Project : Deep Learning Developing Kit\n";
	temp += "Branch  : Master\n";
	temp += "Version : Windows-x64-0.1.0-CPU\n";
	temp += "Copyright 2015-2018 Celestial Tech Inc.\nFor more check www.tianshicangxie.com\n";
	cout << temp << endl;
}

void PrintLocalTime(void)
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	printf("%4d/%02d/%02d %02d:%02d:%02d \n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
}