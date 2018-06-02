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
#include <iostream>

#include "..\..\MathLib\MathLib.h"
#include "..\..\Util\Json\JsonHandler.h"
#include "..\..\Visualizer\Visualize.h"

// Namespaces
using namespace MathLib;

/***************************************************************************************************/
// Namespace : Data
/// Used for management of data.
namespace Data
{
	/***************************************************************************************************/
	// Class : DataSet
	/// Base class of all datasets.
	class DataSet
	{
		virtual void LoadFromJson(const std::string & _filePath) = 0;
	};

	/***************************************************************************************************/
	// Class : NumericSet
	/// Stores all 
	class NumericSet : public DataSet
	{
	public:

		typedef std::pair<Vector<double>, Vector<double>> Sample;

	public:

		NumericSet();

	public:

		void LoadFromJson(const std::string & _filePath);
		void AddToSet(const Sample & _sample);
		inline const size_t GetSampleSize(void) const { return this->sampleSize; }

	public:

		void Serialize(const std::string & _filePath, const std::vector<Sample> & _samples) const;
		void Deserialize(const std::string & _filePath);

	public:

		inline size_t GetSize(void) const { return sampleSize; }

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

	/***************************************************************************************************/
	// Class : ImageSet
	class ImageSet : public DataSet
	{
	public:

		typedef std::pair<MathLib::Matrix<double>, MathLib::Vector<double>> Sample;

	public:

		ImageSet();

	public:

		const Sample GetBatch(void) const;
		const Sample GetRandomSample(void) const;
		const Sample GetSample(const size_t _index) const;
		inline const size_t GetSampleSize(void) const { return this->sampleSize; }

	public:

		void LoadFromJson(const std::string & _filePath);

	public:

		void PrintToConsole(void);

	private:

		std::string name;
		size_t sampleSize;
		size_t lableSize;

		std::vector<Sample> _samples;
	};

	/***************************************************************************************************/
	// Class : AudioSet
	class AudioSet : public DataSet
	{
	public:

	private:
	};

	/***************************************************************************************************/
	// Class : VideoSet
	class VideoSet : public DataSet
	{
	public:

	private:
	};
}
