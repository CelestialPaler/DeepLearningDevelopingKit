/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	       Linear Regression     	                                                      */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#include "..\..\..\DataManager\Dataset\DataSet.h"
#include "..\..\..\MathLib\MathLib.h"
#include <iosfwd>

/***************************************************************************************************/
// Namespace : Regression
namespace Regression
{
	// Regression Methods
	enum class RegressionMethod
	{
		OrdinaryLeastSquares,
		GradientDescent
	};

	/***************************************************************************************************/
	// Class : LinearRegression
	/// One variable linear resgression.
	class LinearRegression
	{
	public: // Constructors

		// Default constructor
		/// Take no parameters.
		LinearRegression(void);

	public: 

		// Train the model
		void Train(void);
		// Test the model
		void Test(void) const;
		// Use the model to predict
		const double Predict(const double _x) const;

	public: // Configurations

		// Set dataset for training
		void SetTrainSet(Data::NumericSet * _trainset);
		// Set dataset for testing
		void SetTestSet(Data::NumericSet * _testset);
		// Set dataset for validation
		void SetValidationSet(Data::NumericSet * _validationset);

	private:

		// Ordinary least squares method
		void OrdinaryLeastSquares(void);

	private:
		// Basic
		double _weight;
		double _bias;
		Data::NumericSet * _trainset;
		Data::NumericSet * _testset;
		Data::NumericSet * _validationset;
	};
	
	/***************************************************************************************************/
	// Class : MultivariateLinearRegression (MLR)
	/// Multi variable linear resgression.
	class MultivariateLinearRegression
	{
	public: // Constructors

		MultivariateLinearRegression(const size_t _inputNum);

	public:

		// Train the model
		void Train(void);
		// Test the model
		void Test(void) const;
		// Use the model to predict
		const double Predict(void) const;

	public:

		// Set dataset for training
		void SetTrainSet(Data::NumericSet *  const _trainset);
		// Set dataset for testing
		void SetTestSet(Data::NumericSet * const _testset);
		// Set dataset for validation
		void SetValidationSet(Data::NumericSet * const _validationset);

	private:

		// Cost Function
		const double CostFunction(const MathLib::Matrix<double> & _predict, const MathLib::Matrix<double> & _lable) const;

	private:
		// Basic
		MathLib::Matrix<double> _theta;
		Data::NumericSet * _trainset;
		Data::NumericSet * _testset;
		Data::NumericSet * _validationset;
		RegressionMethod _method;
	};
}
