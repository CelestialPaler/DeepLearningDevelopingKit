/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 			  Json Handler 	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include "..\..\external\rapidjson\document.h"

using namespace std;
using namespace rapidjson;

class JsonHandler
{
public:
	JsonHandler();

public:
	void OpenFile(const string & _filePath);
	void OpenJson(const string & _filePath);
	void SaveJson(const string & _filePath);

private:
	string fileBuffer;
	string jsonBuffer;
};