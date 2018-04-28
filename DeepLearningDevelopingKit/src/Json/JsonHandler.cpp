/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 			  Json Handler 	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#include "JsonHandler.h"

Vector<double> JsonHandler::ParseVector(void)
{
	unsigned size = doc["size"].GetUint();
	Vector<double> tempVec(size);

	const Value& data = doc["data"];
	for (SizeType i = 0; i < data.Size(); i++)
	{
		tempVec(i) = data[i].GetDouble();
	}
	return tempVec;
}

void JsonHandler::OpenJson(const string & _filePath)
{
	ifstream infile;
	infile.open(_filePath);
	if (!infile.is_open())
		exit(0);
	string datatemp;
	while (getline(infile, datatemp))
	{
		jsonBuffer += datatemp;
	}
	infile.close();
	doc.Parse(jsonBuffer.c_str());
}
