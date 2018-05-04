#**************************************************************************************************#
#                                               Deep Learning Developing Kit                                                    #
#                                                                 Vector                                                                      #
#                                                   www.tianshicangxie.com                                                         #
#                                      Copyright © 2015-2018 Celestial Tech Inc.                                           #
#**************************************************************************************************#

# modules
from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt

x1 = [1, 2, 3, 4, 5, 6, 7, 8, 9]
y1 = [5, 0, 7, 3, 9, 4, 1 ,8, 5]
z1 = [3, 6, 1 ,8 ,2, 0 ,3, 7, 2]

fig = plt.figure()

axl = fig.add_subplot(111, projection = '3d')

axl.plot_wireframe(x1, y1, z1)

plt.show()