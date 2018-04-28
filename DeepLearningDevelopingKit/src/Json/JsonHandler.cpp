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
	if (!infile.is_open())
		exit(0);
	string datatemp;
	while (getline(infile, datatemp))
	{
		fileBuffer += datatemp;
	}
	infile.close();

	Document document;
	document.Parse(fileBuffer.c_str());

	if (document.HasMember("persons"))
	{
		const Value& persons = document["persons"];
		for (SizeType i = 0; i < persons.Size(); i++)
		{
			cout << persons[i]["name"].GetString() << endl;
		}
	}
}
