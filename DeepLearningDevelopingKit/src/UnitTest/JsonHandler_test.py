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
from JsonHandler import JsonHandler

sys.path.append(str(dir_path + '\\src\\PythonAPI'))
from Vector import Vector

if __name__ == '__main__':
    test_json_path = '\\data\\test\\vector.json'
    test_data = JsonHandler.open_json(test_json_path)

    vectors = list()
    for vector in test_data['datablock']:
        if vector['class'] == 'vector':
            vec_temp = Vector(vector['size'])
            vec_temp.data = np.array(vector['data'], np.float)
            vectors.append(vec_temp)
        else:
            raise Exception('Invalid data class!')

    for vec in vectors:
        print(vec.data)


