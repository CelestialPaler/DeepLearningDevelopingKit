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
    
    json_data = str()

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
            with open(file_path_abs, 'r', encoding='utf-8') as file:
                file_data = json.load(file)
                return file_data
        else:
            raise Exception('Invalid file path!')

    # Dump serialized python object into a Json file.
    @staticmethod
    def save_json(file_path, file_data):
        dir_path = os.path.join(os.path.abspath(os.path.join(os.path.dirname(__file__),'..\\..')))
        file_path_abs = dir_path + file_path
        print(file_path_abs)
        if os.path.exists(file_path_abs):
            with open(file_path_abs, 'w', encoding='utf-8') as file:
                json.dump(file_data, file, indent=4)
        else:
            raise Exception('Invalid file path!')

    # Open a Json file and cache it in json_data.
    @staticmethod
    def open_with_cache(file_path):
        JsonHandler.json_data = JsonHandler.open_json(file_path)
