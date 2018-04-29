#**************************************************************************************************#
#                                               Deep Learning Developing Kit                                                    #
#								        		 	          Json Handler   	                                                           #
#                                                   www.tianshicangxie.com                                                         #
#                                      Copyright © 2015-2018 Celestial Tech Inc.                                           #
#**************************************************************************************************#

# modules
import os  
import sys

dir_path = os.path.abspath(os.path.join(os.path.dirname(__file__),'..\\..'))
ads_path = dir_path + '\\Json'
print(ads_path)
sys.path.append(ads_path)
# from JsonHandler import JsonHandler

if __name__ == '__main__':
    test_json_path = '\\data\\test\\test.json'
    test_data = JsonHandler.open_json(test_json_path)
        
    for person in test_data['persons']:
        print(person['name'])



  
