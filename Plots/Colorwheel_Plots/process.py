import matplotlib.pyplot as plt
import numpy as np
import numpy.ma as ma
import scipy
from scipy.stats import probplot

import sys

## BIN 0 is M!!!! Then increasing bins goes counterclockwise around circle


bins = 100
if(len(sys.argv)<2):
	print "Input file?"
	exit(0)

f = open(sys.argv[1],"r")
lines = f.readlines()
lines = lines[1:]
img = np.empty((500,500))
data = [0 for i in range(bins)]
counts = [0 for i in range(bins)]

for j in range(bins):
	data[j] = float(lines[j])
for j in range(bins, 2*bins):
	counts[j-bins] = int(lines[j])


max_count = max(counts)
tots=0
for j in range(len(counts)):
	counts[j] = counts[j]*(2000.0/max_count)
for i in range(500):
	for j in range(500):
		#find ang wrt center
		x = i-250
		y = j-250
		dist = (x**2)+(y**2)
		ang = np.arctan2(y,x)
		#color with num from bin
#		ang += np.pi
		assert(ang<=2*np.pi and ang>=0)
		
		bin = np.floor(ang*(bins/(2.0*np.pi)))

		if(bin==100): #sometimes arctan2 returns 2pi exactly. whatever.
			bin=99
	
		d = data[int(bin)]
		if(dist<2500 or dist > counts[int(bin)]*20+2500):
		   img[i][j]=-555
		else:
			img[i][j] = d




#
mask = ma.masked_values(img, -555)
palette = plt.cm.jet
palette.set_bad("#4c4c4c", 1.0)


fig, ax = plt.subplots()
for i in range(1,11):
	circle = plt.Circle((250,250), i*50, color = 'w', fill = False)
	ax.add_artist(circle)


plt.imshow(mask, cmap = palette, vmin=-0.0001, vmax=0.0001)
plt.axis('off')
plt.colorbar()
axes = plt.gca()
plt.show()
#
##
