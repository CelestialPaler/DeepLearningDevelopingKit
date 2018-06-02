/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	            NeuralLib 	                                                                  */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

#define NeuralNetwork
#define ConvolutionalNeuralNetwork

#ifdef NeuralNetwork
#include "BackpropagationNeuralNetwork\BNN_Node.h"
#include "BackpropagationNeuralNetwork\BNN_Layer.h"
#include "BackpropagationNeuralNetwork\BNN_Module.h"
#endif // NeuralNetwork

#ifdef ConvolutionalNeuralNetwork
#include "ConvolutionalNeuralNetwork\CNN_ConvolutionalLayer.h"
#include "ConvolutionalNeuralNetwork\CNN_PoolingLayer.h"
#include "ConvolutionalNeuralNetwork\CNN_ProcessLayer.h"
#include "ConvolutionalNeuralNetwork\CNN_SerializeLayer.h"
#include "ConvolutionalNeuralNetwork\CNN.h"
#endif // ConvolutionalNeuralNetwork
