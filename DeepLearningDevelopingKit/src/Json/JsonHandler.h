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
#include "..\..\external\rapidjson\prettywriter.h"
#include "..\..\external\rapidjson\stringbuffer.h"

/***************************************************************************************************/
// Class : JsonHandler
/// Used for exchange data with other application or api.
/// Loading a json file and parsing data into other classes.
/// Saving data of other classes to json file.
class JsonHandler
{
public: // Constructors

	// Default constructor
	/// Take no parameters.
	JsonHandler();

public:
	MathLib::Vector<double> ParseVector(const size_t _index) const;
	std::vector<MathLib::Vector<double>> ParseAllVector(void) const;

public:
	//  Open a plain text file.
	void OpenFile(const std::string & _filePath);
	//  Open a Json file.
	void OpenJson(const std::string & _filePath);
	// Save data to a Json file.
	void SaveJson(const std::string & _filePath);
	
	void AppendVectorsToBuffer(const std::vector<MathLib::Vector<double>> & _vec);
	
public:
	// Clear the buffer.
	void ClearBuffer(void);

private:
	std::string jsonReadBuffer;
	std::string jsonWriteBuffer;
	rapidjson::Document documentReadBuffer;
	rapidjson::Document documentWriteBuffer;
	rapidjson::StringBuffer stringBuffer;
};