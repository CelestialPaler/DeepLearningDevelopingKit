/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	       Linear Regression     	                                                      */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#include "..\..\..\DataManager\Dataset\DataSet.h"
#include "..\..\..\MathLib\MathLib.h"

namespace Regression
{
	enum class LinearRegressionMethod
	{
		OrdinaryLeastSquares,
		GradientDescent
	};

	class LinearRegression
	{
	public:
		LinearRegression();
		~LinearRegression();

	public:
		void Train(void);
		void Test(void);
		double Predict(void);

	public:
		void SetTrainSet(Data::NumericSet * _trainset);
		void SetTestSet(Data::NumericSet * _testset);
		void SetValidationSet(Data::NumericSet * _validationset);
		void SetMethod(const LinearRegressionMethod _method);

	private:
		void OrdinaryLeastSquares(void);
		void GradientDescent(void);

	public:
		// Basic
		double _weight;
		double _bias;
		Data::NumericSet * _trainset;
		Data::NumericSet * _testset;
		Data::NumericSet * _validationset;
		LinearRegressionMethod _method;
	};
	
	class MultivariateLinearRegression
	{
	public:
		MultivariateLinearRegression();
		~MultivariateLinearRegression();

	public:
		void Train(void);
		void Test(void);
		double Predict(void);

	public:
		void SetTrainSet(Data::NumericSet * _trainset);
		void SetTestSet(Data::NumericSet * _testset);
		void SetValidationSet(Data::NumericSet * _validationset);
		void SetMethod(const LinearRegressionMethod _method);

	private:

	public:
		// Basic
		double _weight;
		double _bias;
		Data::NumericSet * _trainset;
		Data::NumericSet * _testset;
		Data::NumericSet * _validationset;
		LinearRegressionMethod _method;
	};
}
