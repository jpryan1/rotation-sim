import matplotlib.pyplot as plt
import numpy as np
import scipy
from scipy.stats import probplot


img = np.empty((100,100))

f = open("stats30.txt","r")
lines = f.readlines()

for i in range(100):
	for j in range(100):
		line = lines[100*i + j +1]
		img[i][99-j] = float(line)

plt.subplot(131)
plt.title("N=30")
plt.imshow(img)
plt.colorbar()

img1 = np.empty((100,100))

f = open("stats40.txt","r")
lines = f.readlines()

for i in range(100):
	for j in range(100):
		line = lines[100*i + j+1]
		img1[i][99-j] = float(line)

plt.subplot(132)
plt.title("N=40")
plt.imshow(img1)
plt.colorbar()

f = open("stats50.txt","r")
lines = f.readlines()
img2 = np.empty((100,100))

for i in range(100):
	for j in range(100):
		line = lines[100*i + j+1]
		img2[i][99-j] = float(line)

plt.subplot(133)
plt.title("N=50")
plt.imshow(img2)
plt.colorbar()
plt.show()






#
#
#
#
#
#
#
#f = open("stats45.txt","r")
#lines = f.readlines()
#img3 = np.empty((100,100))
#
#for i in range(100):
#	for j in range(100):
#		line = lines[100*i + j+1]
#		img3[99-i][j] = float(line)
#
#plt.subplot(234)
#plt.title("N=45")
#plt.imshow(img3)
#plt.colorbar()
#
#f = open("stats50.txt","r")
#lines = f.readlines()
#img4 = np.empty((100,100))
#
#for i in range(100):
#	for j in range(100):
#		line = lines[100*i + j+1]
#		img4[99-i][j] = float(line)
#
#plt.subplot(235)
#plt.title("N=50")
#plt.imshow(img4)
#plt.colorbar()
#
#f = open("stats55.txt","r")
#lines = f.readlines()
#img5 = np.empty((100,100))
#
#for i in range(100):
#	for j in range(100):
#		line = lines[100*i + j+1]
#		img5[99-i][j] = float(line)
#
#plt.subplot(236)
#plt.title("N=55")
#plt.imshow(img5)
#plt.colorbar()
#
#
#
#plt.show()
#
#
