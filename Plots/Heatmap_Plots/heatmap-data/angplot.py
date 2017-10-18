import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import scipy
from scipy.stats import probplot

font = {'family' : 'normal',
	'weight' : 'bold',
	'size'   : 22}
matplotlib.rc('font', **font)

img = np.empty((110,100))
for b in range(35,56,2):
	f = open("angvel"+str(b)+".txt","r")

	lines = f.readlines()
	lines = lines[1:]
	for i in range((b-35)*5,((b-35)*5)+10):
		for j in range(100):
			line = lines[j]
			img[109-i][99-j] = float(line)

#
#
#



plt.imshow(img, vmin=-0.30, vmax=0.30)
plt.colorbar()
axes = plt.gca()
axes.set_ylabel("Number of disks")
axes.set_xlabel("Angular position")
axes.set_xticks([i*(100.0/6.0) for i in range(7)])
axes.set_xticklabels([0,60,120,180,240, 300, 360])
axes.set_yticks([i*(10) for i in range(12)])
axes.set_yticklabels([i for i in range(55,34,-2)])
plt.show()
#
