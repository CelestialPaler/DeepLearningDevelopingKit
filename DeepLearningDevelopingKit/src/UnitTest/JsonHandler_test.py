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
import json

dir_path = os.path.abspath(os.path.join(os.path.dirname(__file__),'..\\..'))

sys.path.append(str(dir_path + '\\src\\Json')) 
from JsonParser import VectorParser


if __name__ == '__main__':
    test_json_path = '\\data\\test\\test2.json'
    vectors = VectorParser.deserialize(test_json_path)
    for vec in vectors:
        print(vec.data)
    test_json_path = '\\data\\test\\test.json'
    VectorParser.serialize(test_json_path, vectors)



