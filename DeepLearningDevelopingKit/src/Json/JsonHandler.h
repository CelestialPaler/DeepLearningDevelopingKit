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

/***************************************************************************************************/
// Class : JsonHandler
///
class JsonHandler
{
public:
	JsonHandler();

public:
	MathLib::Vector<double> ParseVector(const size_t _index) const;
	std::vector<MathLib::Vector<double>> ParseAllVector(void) const;

public:
	void OpenFile(const std::string & _filePath);
	void OpenJson(const std::string & _filePath);
	void SaveJson(const std::string & _filePath, const std::string & _newdata);

private:
	std::string jsonBuffer;
	rapidjson::Document document;
	std::vector<MathLib::Vector<double>> tempBuffer;
};