#**************************************************************************************************#
#                                               Deep Learning Developing Kit                                                    #
#								        		 	          Json Handler   	                                                           #
#                                                   www.tianshicangxie.com                                                         #
#                                      Copyright © 2015-2018 Celestial Tech Inc.                                           #
#**************************************************************************************************#

import os  
import json

test_json = '.\\test.json'

class JsonHandler:
    @staticmethod
    def open_file(str):
        if os.path.exists(str):
            with open(str, 'r', encoding='utf-8') as file:
                data = file.read()
            file.close()
            return data
        else:
            raise Exception("Invalid file path!")
            

    @staticmethod
    def open_json(str):
        if os.path.exists(str):
            with json.load(str) as file:
                data = file.read()
            file.close()
            return data

    @staticmethod
    def save_json(str):
        pass


if "__name__" == "__main__":
    try:
        data = JsonHandler.open_file(test_json)
    except ValueError:
        print("Open file failed!")
        
    print(data)



  
