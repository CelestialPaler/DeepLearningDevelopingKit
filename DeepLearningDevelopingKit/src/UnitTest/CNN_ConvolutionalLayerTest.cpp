
/*
int main(int argc, char ** argv)
{
	srand((unsigned)time(NULL));
	std::cout << "Unit Test : CNN-PaddingLayer" << std::endl;
	std::cout << "Project : DeepLearningDevelopingKit\n";
	std::cout << "Branch  : Master\n";
	std::cout << "Version : Windows-x64-1.0.0-CPU\n";
	std::cout << "Copyright 2015-2018 Celestial Tech Inc.\nFor more check www.tianshicangxie.com\n";

	MathLib::Matrix<double> input1(10, 10, MathLib::MatrixType::Identity);
	std::vector<MathLib::Matrix<double>> input;
	input.push_back(input1);

	// Convolutional Layer Init
	Neural::ConvLayerInitor convInitor;
	convInitor.InputSize = MathLib::Size(10, 10);
	convInitor.KernelSize = MathLib::Size(3, 3);
	convInitor.Stride = 1;
	convInitor.KernelNum = 5;
	convInitor.ActivationFunction = ActivationFunction::Linear;
	convInitor.PaddingMethod = Neural::PaddingMethod::Surround;
	convInitor.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::ConvolutionalLayer convLayer(convInitor);

	convLayer._convNodes.at(0).kernel.Clear();
	for (size_t i = 0; i < convLayer._convNodes.at(0).kernel.ColumeSize(); i++)
		for (size_t j = 0; j < convLayer._convNodes.at(0).kernel.RowSize(); j++)
			if (i == j)
				convLayer._convNodes.at(0).kernel(i, j) = 1.f;

	convLayer.SetInput(input);//

	std::cout << "Orignal Input : " << std::endl;
	for (auto mat : convLayer._input)
		std::cout << mat << std::endl;

	std::cout << "Orignal Kernels : " << std::endl << std::endl;
	std::vector<Neural::ConvKernel> conv1kernals = convLayer.GetKernelAll();
	for (auto mat : conv1kernals)
		std::cout << mat << std::endl;

	convLayer.ForwardPropagation();//

	std::vector<Neural::ConvFeature> conv1features = convLayer.GetFeatureAll();
	std::cout << "Output Features : " << std::endl << std::endl;
	for (auto mat : conv1features)
		std::cout << mat << std::endl;

	MathLib::Matrix<double> delta1(5, 5, MathLib::MatrixType::Identity);
	std::vector<MathLib::Matrix<double>> delta;
	delta.push_back(delta1);

	convLayer.SetDelta(delta);
	std::cout << "Delta : " << std::endl << std::endl;
	for (auto mat : delta)
		std::cout << mat << std::endl;

	convLayer.BackwardPropagation();//

	std::cout << "Out Delta : " << std::endl << std::endl;
	for (auto mat : convLayer._derivative)
		std::cout << mat << std::endl;

	convLayer.Update();

	convLayer.ForwardPropagation();//

	std::cout << "Updated kernel: " << std::endl << std::endl;
	std::vector<Neural::ConvKernel> conv1kernalss = convLayer.GetKernelAll();
	for (auto mat : conv1kernalss)
		std::cout << mat << std::endl;
	std::vector<Neural::ConvFeature> conv1featuress = convLayer.GetFeatureAll();
	std::cout << "Updated Output Features : " << std::endl << std::endl;
	for (auto mat : conv1featuress)
		std::cout << mat << std::endl;

	std::cout << "\n\nTest OK" << std::endl;

	system("pause");
	return 0;
}
*/