#**************************************************************************************************#
#                                               Deep Learning Developing Kit                                                    #
#                                                                  Node                                                                      #
#                                                   www.tianshicangxie.com                                                         #
#                                      Copyright © 2015-2018 Celestial Tech Inc.                                           #
#**************************************************************************************************#

# modules
import sys
import os


dir_path = os.path.abspath(os.path.join(os.path.dirname(__file__),'..\\..'))
sys.path.append(str(dir_path + '\\src\\PythonAPI'))
from Vector import Vector

class Node:

        def __repr__(self):
            return 'Node()')
            
        def __str__(self):
                return 'A Node from DeepLearningDevelopingKit.'
