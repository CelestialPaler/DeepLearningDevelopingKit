#**************************************************************************************************#
#                                               Deep Learning Developing Kit                                                    #
#								        		 	            Dataset  	                                                           #
#                                                   www.tianshicangxie.com                                                         #
#                                      Copyright © 2015-2018 Celestial Tech Inc.                                           #
#**************************************************************************************************#

# modules
import os 
import sys
import json
import random

dir_path = os.path.join(os.path.abspath(os.path.join(os.path.dirname(__file__),'..\\..\\..')))
sys.path.append(str(dir_path + '\\src\\PythonAPI\\Json')) 
print(sys.path)
from JsonHandler import JsonHandler


class DataSetGenerator:

    @staticmethod
    def MLR(sample_size, input_size, lable_size, theta):
        dict1 = {}
        dict1['class'] = 'MultivariateLinearRegression Test'
        dict1['sample_size'] = sample_size
        dict1['input_size'] = input_size
        dict1['lable_size'] = lable_size
        dict1['datablock'] = []
        for _ in range(sample_size):
            dict2 = {}
            dict2['class'] = 'numeric_set::sample'
            dict2['input'] = []
            for _ in range(input_size):
                dict2['input'].append(random.random())
            dict2['lable'] = []
            temp=0
            for i in range(input_size):
                temp += theta[i] * dict2['input'][i]
            temp += theta[input_size]
            dict2['lable'].append(temp)
            dict1['datablock'].append(dict2)
        return dict1
        

if __name__ == '__main__':
    file_path = '\\data\\test\\MLR.json'
    theta = [1, 2, 3]
    result = DataSetGenerator.MLR(2, 2, 1, theta)
    JsonHandler.save_json(file_path, result);
    