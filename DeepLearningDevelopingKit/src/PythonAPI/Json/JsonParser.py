#**************************************************************************************************#
#                                               Deep Learning Developing Kit                                                    #
#								        		 	          Json Parser   	                                                           #
#                                                   www.tianshicangxie.com                                                         #
#                                      Copyright © 2015-2018 Celestial Tech Inc.                                           #
#**************************************************************************************************#

# modules
import sys
import os
import json
import numpy as np

dir_path = os.path.abspath(os.path.join(os.path.dirname(__file__),'..\\..'))
sys.path.append(str(dir_path + '\\src\\Json')) 
from JsonHandler import JsonHandler
sys.path.append(str(dir_path + '\\src\\PythonAPI'))
from Vector import Vector


# Class : VectorParser
# Used for parsing json data into Vector().
class VectorParser:

    def __repr__(self):
        return 'VectorParser()'

    def __str__(self):
        return 'A Vector Parser from DeepLearningDevelopingKit.'

    # Encode the a list of vectors into styled dictionary format.
    @staticmethod
    def encode(vectors):
        dict1 = {}
        dict1['class'] = 'vector'
        dict1['size'] = len(vectors)
        dict1['datablock'] = []
        for vector in vectors:
            dict2 = {}
            dict2['class'] = 'vector'
            dict2['size'] = len(vector.data)
            dict2['data'] = []
            for num in vector.data:
                dict2['data'].append(num)
            dict1['datablock'].append(dict2)
        return dict1

    # Decode styled dictionary back into a list of vectors.
    @staticmethod
    def decode(json_data):
        vectors = list()
        for i in range(json_data['size']):
            vector = json_data['datablock'][i]
            if vector['class'] == 'vector':
                vec_temp = Vector(vector['size'])
                vec_temp.data = np.array(vector['data'], np.float)
                vectors.append(vec_temp)
            else:
                raise Exception('Invalid data class!')
        return vectors

    # Save a list of vectors into a .json file.
    @staticmethod
    def serialize(file_path, vectors):
        vec_dict = VectorParser.encode(vectors)
        JsonHandler.save_json(file_path, vec_dict);

    # Load a list of vectors from a .json file.
    @staticmethod
    def deserialize(file_path):
        json_data = JsonHandler.open_json(file_path)
        vectors = VectorParser.decode(json_data)
        return vectors

    # Parsing the json data, return the vectors in the indexed range.
    @staticmethod
    def parse_in_range(json_data, index_low, index_high):
        vectors = list()
        for i in range(index_low, index_high):
            vector = json_data['datablock'][i]
            if vector['class'] == 'vector':
                vec_temp = Vector(vector['size'])
                vec_temp.data = np.array(vector['data'], np.float)
                vectors.append(vec_temp)
            else:
                raise Exception('Invalid data class!')
        return vectors




    