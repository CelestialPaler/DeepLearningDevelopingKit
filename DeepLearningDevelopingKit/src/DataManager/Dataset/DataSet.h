/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              DataSet     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include <vector>
#include <iomanip>
#include <string>

#include "..\..\MathLib\MathLib.h"
#include "..\..\Util\Json\JsonHandler.h"

// Namespaces
using namespace MathLib;

namespace Data
{
	class DataSet
	{
		virtual void LoadFromJson(const std::string & _filePath) = 0;
	};

	class NumericSet : public DataSet
	{
	public:

		typedef std::pair<Vector<double>, Vector<double>> Sample;

	public:

		NumericSet();

	public:

		void LoadFromJson(const std::string & _filePath);
		void AddToSet(const Sample & _sample);

	public:

		void Serialize(const std::string & _filePath, const std::vector<Sample> & _samples) const;
		void Deserialize(const std::string & _filePath);

	public:

		const Sample GetBatch(void) const;
		const Sample GetRandomSample(void) const;
		const Sample GetSample(const size_t _index) const;

	public:

		void PrintToConsole(void);

	private:

		std::string name;
		size_t sampleSize;
		size_t inputSize;
		size_t lableSize;

		std::vector<Sample> _samples;
	};

	class ImageSet : public DataSet
	{
	public:

	private:
	};

	class AudioSet : public DataSet
	{
	public:

	private:
	};

	class VideoSet : public DataSet
	{
	public:

	private:
	};
}
