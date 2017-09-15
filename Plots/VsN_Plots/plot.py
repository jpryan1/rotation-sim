import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import sys
import time


font = {'family' : 'normal',
	'weight' : 'bold',
	'size'   : 22}

matplotlib.rc('font', **font)

yaxis = "Angular Velocity"

f = open("D1W1.txt", "r")
g = open("D1W0.txt", "r")
h = open("D0W1.txt", "r")
pred = open("rads.txt", "r")
#2*PI* (1- (9.1/RAD))/12.0;

lines = f.readlines()
lines1 = g.readlines()
lines2 = h.readlines()
lines3 = pred.readlines()
d1w1 = []
d1w0 = []
d0w1 = []
predicted = []



PI = 3.1415926535897932

for line in lines:
	d1w1.append(float(line))
for line in lines1:
	d1w0.append(float(line))
for line in lines2:
	d0w1.append(float(line))
for line in lines3:
	predicted.append(2*PI* (1- (9.1/float(line)))/12.0);

x = [i for i in range(5,57)]
zeros = np.zeros(len(x))
snake = [0.523598776 for i in range(5,57)] #pi/6


plt.plot(x,d1w1,'-r', label = "All Friction", linewidth=8)
plt.plot(x, d1w0, '-b', label = "No Wall Friction", linewidth=8)
plt.plot(x, d0w1, '-g', label = "No Disk Friction", linewidth=8)
plt.plot(x, predicted, '-m', label = "Predicted", linewidth=8)
plt.plot(x, zeros, '--k', linewidth=4)
plt.plot(x, snake, '--k', linewidth=4)

plt.legend()
plt.title(yaxis+" vs N")
plt.xlabel("N")
plt.ylabel(yaxis)

axes = plt.gca()
axes.set_xlim([5, 56])
plt.show()
