#**************************************************************************************************#
#                                               Deep Learning Developing Kit                                                    #
#                                                                 Vector                                                                      #
#                                                   www.tianshicangxie.com                                                         #
#                                      Copyright © 2015-2018 Celestial Tech Inc.                                           #
#**************************************************************************************************#

# modules
import numpy as np


# Class : Vector
# Vector implemented in Numpy
# Exchange data between C++ and Pyhton
class Vector:

        def __init__(self, size_n):
                self._data = np.zeros(size_n)

        def __repr__(self):
                return 'Vector( {} )'.format(np.size(self._data))

        def __str__(self):
                return 'A Vector from DeepLearningDevelopingKit.'

        # Data stored in vector
        @property
        def data(self):
                return self._data

        @data.setter
        def data(self, new_data):
                self._data = new_data
        

if __name__ == '__main__':
        test = Vector(5)
        print(test.data)
