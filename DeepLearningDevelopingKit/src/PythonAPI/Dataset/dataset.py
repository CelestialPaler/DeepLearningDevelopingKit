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
        dict1['name'] = 'MultivariateLinearRegression Test'
        dict1['class'] = 'numeric_set'
        dict1['sample_size'] = sample_size
        dict1['input_size'] = input_size
        dict1['lable_size'] = lable_size
        dict1['datablock'] = []
        for _ in range(sample_size):
            dict2 = {}
            dict2['class'] = 'numeric_set::sample'
            dict2['input'] = []
            for _ in range(input_size):
                dict2['input'].append(random.random() * 10)
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
    # theta = [1.2, 2.9, 0.3, 0.35, 2.6, 1.36, 2.36, 3.26, 2.36]
    # theta = [1, 2, 3]
    theta = [1, 2, 3, 4, 5, 6]
    result = DataSetGenerator.MLR(10, 5, 1, theta)
    JsonHandler.save_json(file_path, result);
    