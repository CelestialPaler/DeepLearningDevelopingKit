/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              DataSet     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include <vector>
#include "..\MathLib\MathLib.h"

// Namespaces
using namespace std;
using namespace MathLib;

namespace Data
{
	class DataSet
	{
		
	};

	class NumaricSet : public DataSet
	{
	public:
		typedef pair<Vector<double>, Vector<double>> Sample;
		friend ostream & operator <<(ostream & _outstream, Sample & _sample);

		void printsdfsafsa(void){
			NumaricSet::Sample testSample;

			Vector<double> input(3, VectorType::Random);
			Vector<double> output(2, VectorType::Random);
			testSample.first = input;
			testSample.second = output;

			cout << testSample;
		}
	private:

	};
}