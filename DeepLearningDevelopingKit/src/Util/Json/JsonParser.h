/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 			  Json Parser 	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

#include <iostream>
#include <string>
#include "..\..\MathLib\MathLib.h"
#include "JsonHandler.h"

class JsonParser {};

class VectorParser : public JsonParser
{
public:

	void Serialize(const std::string & _filePath, const std::vector<MathLib::Vector<double>> & _vectors);
	std::vector<MathLib::Vector<double>> Deserialize(const std::string & _filePath);

private:

};