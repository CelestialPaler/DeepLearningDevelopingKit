/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 			    Data Saver                                                                  */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

#include <iostream>
#include <string>

#include "..\..\Util\Json\JsonParser.h"

class Save
{
public:
	static void SaveNode(const std::string & _filePath, const InputNode & _node);
};
