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
from JsonHandler import JsonHandler as jh
from JsonParser import VectorParser as vp

sys.path.append(str(dir_path + '\\src\\PythonAPI'))
from Vector import Vector


if __name__ == '__main__':
    test_json_path = '\\data\\test\\test2.json'
    jh.open_with_cache(test_json_path)
    vectors = vp.parse_all(jh.json_data)

    vecdict = vp.serialize(vectors)

    json_data = json.dumps(vecdict, indent=4, separators=(',', ':'))

    test_json_path = '\\data\\test\\test.json'
    jh.save_json(test_json_path, vecdict)


