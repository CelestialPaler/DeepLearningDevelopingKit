import numpy as np,sys

from scipy.signal import convolve2d
from sklearn.utils import shuffle

from scipy.ndimage.filters import maximum_filter
import skimage.measure


np.random.seed(12314)

def ReLU(x):
    mask  = (x >0) * 1.0 
    return mask * x
def d_ReLU(x):
    mask  = (x >0) * 1.0 
    return mask 

def tanh(x):
    return np.tanh(x)
def d_tanh(x):
    return 1 - np.tanh(x) ** 2

def arctan(x):
    return np.arctan(x)
def d_arctan(x):
    return 1 / ( 1 + x ** 2)

def log(x):
    return 1 / (1 + np.exp(-1 * x))
def d_log(x):
    return log(x) * ( 1 - log(x))


# 1. Prepare Data
num_epoch = 1000
learning_rate = 0.1
total_error = 0

x1 = np.array([
    [0,0,0,-1],
    [-1,0,-1,0],
    [-1,0,-1,-1],
    [1,0,-1,-1]    
])

x2 = np.array([
    [0,0,0,0],
    [0,0,-1,0],
    [0,0,0,0],
    [1,0,0,-1]    
])

x3 = np.array([
    [0,0,0,-1],
    [0,0,-1,0],
    [-1,0,1,1],
    [1,0,-1,1]    
])

x4 = np.array([
    [0,0,0,1],
    [1,0,1,0],
    [1,0,1,1],
    [1,0,1,1]    
])

image_label=np.array([
    [-1.42889927219],
    [-0.785398163397],
    [0.0],
    [1.46013910562]    
])

image_matrix = np.array([x1,x2,x3,x4])

w1 = (np.random.randn(2,2) * 4.2 )-0.1
w2 = (np.random.randn(2,2)* 4.2)-0.1
w3 = (np.random.randn(4,1)* 4.2)-0.1


print('Prediction Before Training')
predictions = np.array([])
for image_index in range(len(image_matrix)):
    current_image  = image_matrix[image_index]

    l1 = convolve2d(current_image,w1,mode='valid')
    l1A = tanh(l1)

    l2 = convolve2d(l1A,w2,mode='valid')
    l2A = arctan(l2)

    l3IN = np.expand_dims(l2A.ravel(),0)

    l3 = l3IN.dot(w3)
    l3A = arctan(l3)

    predictions = np.append(predictions,l3A)
print('---Groud Truth----')
print(image_label.T)
print('--Prediction-----')
print(predictions.T)
print('--Prediction Rounded-----')
print(np.round(predictions).T)
print("\n")


for iter in range(num_epoch):

    for current_image_index in range(len(image_matrix)):
        
        current_image = image_matrix[current_image_index]
        current_image_label = image_label[current_image_index]

        l1 = convolve2d(current_image,w1,mode='valid')
        l1A = tanh(l1)

        l2 = convolve2d(l1A,w2,mode='valid')
        l2A = arctan(l2)

        l3IN = np.expand_dims(l2A.ravel(),0)

        l3 = l3IN.dot(w3)
        l3A = arctan(l3)

        cost = np.square(l3A - current_image_label).sum() * 0.5
        total_error += cost

        grad_3_part_1 = l3A - current_image_label
        grad_3_part_2 = d_arctan(l3)
        grad_3_part_3 =l3IN
        grad_3 =  grad_3_part_3.T.dot( grad_3_part_1 * grad_3_part_2)

        grad_2_part_IN = np.reshape((grad_3_part_1 * grad_3_part_2).dot(w3.T),(2,2))
        grad_2_part_1 = grad_2_part_IN
        grad_2_part_2 = d_arctan(l2)
        grad_2_part_3 = l1A
        grad_2=  np.rot90( convolve2d(grad_2_part_3,np.rot90(grad_2_part_1 * grad_2_part_2,2),mode='valid')     ,2)
        
        grad_1_part_IN_pad_weight = np.pad(w2,1,mode='constant')
        grad_1_part_IN = np.rot90(grad_2_part_1 * grad_2_part_2,2)

        grad_1_part_1 = convolve2d(grad_1_part_IN_pad_weight,grad_1_part_IN,mode='valid')
        grad_1_part_2 = d_tanh(l1)
        grad_1_part_3 = current_image
        grad_1 =  np.rot90( convolve2d(grad_1_part_3,np.rot90(grad_1_part_1 * grad_1_part_2,2),mode='valid')     ,2)

        w1 = w1 - learning_rate * grad_1
        w2 = w2 - learning_rate * grad_2
        w3 = w3 - learning_rate * grad_3
        
    #print('Current iter:  ', iter, ' current cost: ', cost, end='\r')
    total_error = 0

        
print('\n\n')
print('Prediction After Training')
predictions = np.array([])
for image_index in range(len(image_matrix)):
    current_image  = image_matrix[image_index]

    l1 = convolve2d(current_image,w1,mode='valid')
    l1A = tanh(l1)

    l2 = convolve2d(l1A,w2,mode='valid')
    l2A = arctan(l2)

    l3IN = np.expand_dims(l2A.ravel(),0)

    l3 = l3IN.dot(w3)
    l3A = arctan(l3)

    predictions = np.append(predictions,l3A)
print('---Groud Truth----')
print(image_label.T)
print('--Prediction-----')
print(predictions.T)
print('--Prediction Rounded-----')
print(np.round(predictions).T)
print("\n")