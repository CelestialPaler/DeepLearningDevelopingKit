#**************************************************************************************************#
#                                               Deep Learning Developing Kit                                                    #
#								        		 	          Json Handler   	                                                           #
#                                                   www.tianshicangxie.com                                                         #
#                                      Copyright © 2015-2018 Celestial Tech Inc.                                           #
#**************************************************************************************************#

# modules
import os  
import sys
import numpy as np

dir_path = os.path.abspath(os.path.join(os.path.dirname(__file__),'..\\..'))
sys.path.append(str(dir_path + '\\src\\Json'))
from JsonHandler import *

sys.path.append(str(dir_path + '\\src\\PythonAPI'))
from Vector import Vector

if __name__ == '__main__':
    test_json_path = '\\data\\test\\test2.json'
    JsonHandler.open_with_cache(test_json_path)
    vec = VectorParser.parse(JsonHandler.json_data, 0)
    print(vec.data)


