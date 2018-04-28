#**************************************************************************************************#
#                                               Deep Learning Developing Kit                                                    #
#								        		 	          Json Handler   	                                                           #
#                                                   www.tianshicangxie.com                                                         #
#                                      Copyright © 2015-2018 Celestial Tech Inc.                                           #
#**************************************************************************************************#

# modules
import os  
import json


# Class : JsonHandler
# Used for handling Json files, loading and writing to Json files.
# Parsing and dumping data from all kinds of dara sources.
class JsonHandler:

    def __repr__(self):
        return 'JsonHandler()'

    def __str__(self):
        return 'A Json Handler from DeepLearningDevelopingKit.'

    # Open a common file. Such as plaintext.
    @staticmethod
    def open_file(file_path):
        dir_path = os.path.join(os.path.abspath(os.path.join(os.path.dirname(__file__),'..\\..')))
        file_path_abs = dir_path + file_path
        print(file_path_abs)
        if os.path.exists(file_path_abs):
            with open(file_path_abs) as file:
                file_data = file.read()
            file.close()
            return file_data
        else:
            raise Exception('Invalid file path!')

    # Open a Json file and grab all the data in to a python list.
    @staticmethod
    def open_json(file_path):
        dir_path = os.path.join(os.path.abspath(os.path.join(os.path.dirname(__file__),'..\\..')))
        file_path_abs = dir_path + file_path
        print(file_path_abs)
        if os.path.exists(file_path_abs):
            with open(file_path_abs, 'r', encoding='uft-8') as file:
                file_data = json.load(file) 
                return file_data
        else:
            raise Exception('Invalid file path!')

    # Dump a list of python object into a Json file in Json format.
    @staticmethod
    def save_json(file_path, file_data):
        dir_path = os.path.join(os.path.abspath(os.path.join(os.path.dirname(__file__),'..\\..')))
        file_path_abs = dir_path + file_path
        print(file_path_abs)
        if os.path.exists(file_path_abs):
            with open(file_path_abs, 'w', encoding='uft-8') as file:
                json.dump(file_data, file, indent=2)
        else:
            raise Exception('Invalid file path!')


if __name__ == '__main__':
    test_json_path = '\\data\\test\\test.json'
    test_data = JsonHandler.open_json(test_json_path)
        
    for person in test_data['persons']:
        print(person['name'])



  
