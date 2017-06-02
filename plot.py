import numpy as np
import matplotlib.pyplot as plt
import sys
import time

yaxis = "Angular Velocity"

f = open("D1W1.txt", "r")
g = open("D1W0.txt", "r")
h = open("D0W1.txt", "r")
r = open("rads.txt", "r")

#2*PI* (1- (9.1/RAD))/12.0;

lines = f.readlines()
lines1 = g.readlines()
lines2 = h.readlines()
lines3 = r.readlines()
x = []
y = []
y1 = []
y2 = []
y3 = []
counter = 10
PI = 3.1415926535897932
for line in lines[1:]:
	x.append(counter)
	counter+=1
	y.append(float(line))
for line in lines1[1:]:
	l = line.split(" ")
	y1.append(float(line))
for line in lines2[1:]:
	l = line.split(" ")
	y2.append(float(line))
for line in lines3:
	l = line.split(" ")
	tmp = (1-(9.1/float(line)))
	y3.append(tmp*(PI/6.0))
zeros = np.zeros(len(y))
plt.plot(x[25:],y[25:],'-r', label = "Disk/Disk and Disk/Wall friction")
plt.plot(x[25:], y1[25:], '-b', label = "Disk/Disk friction, no Disk/Wall friction")
plt.plot(x[25:], y2[25:], '-g', label = "Disk/Wall friction, no Disk/Disk friction")
plt.plot(x[25:], y3[25:], '-m', label = "Predicted by single disk model")
plt.plot(x[25:], zeros[25:], '--k')

plt.legend()
plt.title(yaxis+" vs N")
plt.xlabel("N")
plt.ylabel(yaxis)
#
axes = plt.gca()
axes.set_xlim([35, 56])
plt.show()






#Code for multi-data plots


#g = open("data1.txt", "r")
#h = open("data2.txt", "r")

#energies1 = []
#energies2 = []

#
#lines1 = g.readlines()
#for line in lines1:
#    l = line.split(" ")
#    energies1.append(float(l[1]))
#
#lines2 = h.readlines()
#for line in lines2:
#    l = line.split(" ")
#    energies2.append(float(l[1]))


#plt.plot(times,energies1,'-b', label = "WMu=1")
#plt.plot(times,energies2,'-g',label = "WMu=2" )
#plt.legend()
#plt.xscale('log')
#plt.yscale('log')
