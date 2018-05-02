/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 			  Json Handler 	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#include "JsonHandler.h"

void JsonHandler::OpenJson(const string & _filePath)
{
	ifstream infile;
	infile.open(_filePath);
	if (!infile.is_open()) exit(0);
	std::string dataTemp;	
	std::string jsonReadBuffer;
	while (getline(infile, dataTemp))
		jsonReadBuffer += dataTemp;
	infile.close();
	documentReadBuffer.Parse(jsonReadBuffer.c_str());
}

void JsonHandler::SaveJson(const string & _filePath)
{
	ofstream outfile;
	outfile.open(_filePath);
	if(!outfile.is_open()) exit(0);
	outfile << stringBuffer.GetString();
}

void JsonHandler::ClearBuffer(void)
{
	documentReadBuffer = 0;
	documentWriteBuffer = 0;
	stringBuffer = 0;
}


