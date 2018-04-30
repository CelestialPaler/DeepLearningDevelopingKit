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
#include "..\MathLib\MathLib.h"
#include "..\..\external\rapidjson\document.h"

using namespace std;
using namespace MathLib;
using namespace rapidjson;

/***************************************************************************************************/
// Class : JsonHandler
///
class JsonHandler
{
public:
	JsonHandler()
	{
		jsonBuffer = "";
	}

public:
	Vector<double> ParseVector(void);

public:
	void OpenFile(const string & _filePath);
	void OpenJson(const string & _filePath);
	void SaveJson(const string & _filePath, const string & _newdata);

private:
	string jsonBuffer;
	Document doc;
};