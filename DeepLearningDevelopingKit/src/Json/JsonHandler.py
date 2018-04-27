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

    # Open a common file. Such as plaintext.
    @staticmethod
    def open_file(str):
        if os.path.exists(str):
            with open(str, 'r', encoding='utf-8') as file:
                data = file.read()
            file.close()
            return data
        else:
            raise Exception("Invalid file path!")
            
    # Open a Json file and grab all the data in to a python list.
    @staticmethod
    def open_json(str):
        if os.path.exists(str):
            with json.load(str) as file:
                data = file.read()
            file.close()
            return data

    # Dump a list of python object into a Json file in Json format.
    @staticmethod
    def save_json(str):
        pass


if "__name__" == "__main__":
    test_json = '..\\data\\test\\test.json'
    try:
        data = JsonHandler.open_json(test_json)
    except ValueError:
        print("Open file failed!")
        
    print(data)



  
