import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import sys
import time


font = {'family' : 'normal',
	'weight' : 'bold',
	'size'   : 22}
fig = plt.figure(figsize=(14,9))
matplotlib.rc('font', **font)

yaxis = "Angular Velocity"

f = open("D1W1.txt", "r")
g = open("D1W0.txt", "r")
h = open("D0W1.txt", "r")
#2*PI* (1- (9.1/RAD))/12.0;

lines = f.readlines()
lines1 = g.readlines()
lines2 = h.readlines()
#lines3 = pred.readlines()
d1w1 = []
d1w0 = []
d0w1 = []



PI = 3.1415926535897932

for line in lines[1:]:
	d1w1.append(float(line))
for line in lines1[1:]:
	d1w0.append(float(line))
for line in lines2[1:]:
	d0w1.append(float(line))
#for line in lines3[1:]:
#	predicted.append(2*PI* (1- (8.6/float(line)))/12.0);

x = [i for i in range(5,49)]
zeros = np.zeros(len(x))
snake = [0.523598776 for i in range(5,49)] #pi/6

plt.plot(x,d1w1,'-r', label = "All Friction", linewidth=6)
plt.plot(x, d1w0, '--b', label = "No Wall Friction", linewidth=6)
plt.plot(x, d0w1, ':g', label = "No Disk Friction", linewidth=6)
#plt.plot(x, predicted, '-.m', label = "Predicted", linewidth=6)
plt.plot(x, zeros, '--k', linewidth=3)
plt.plot(x, snake, '--k', linewidth=3)

plt.legend()
plt.title(yaxis+" vs N - discs cannot spin")
plt.xlabel("N")
plt.ylabel(yaxis)

axes = plt.gca()
axes.set_xlim([5, 48])
axes.set_ylim([min(d1w1)-0.1, 0.8])
plt.show()

fig.savefig("cannot_spin_vsnpdf.pdf")
