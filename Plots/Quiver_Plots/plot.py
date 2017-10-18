import matplotlib.pyplot as plt

import matplotlib.cm as cm
counter = 1
for k in range(30,55,10):
	
	plt.subplot(1, 3, counter)

	plt.xticks([], [])
	plt.yticks([], [])

	counter +=1
	f = open("quiver"+str(k)+".txt")
	lines = f.readlines()
	N = str(k)
	lines = lines[1:]
	j=0
	i=0
	fig = plt.gcf()
	ax = fig.gca()
	for line in lines:
		l = line.split(" ")
		if(len(l)>1):
			ax.arrow((18.2/20.0)*(19-i) - 9.1, (18.2/20.0)*(19-j) - 9.1, -float(l[0]), -float(l[1]),head_width=0.2)
		j += 1
		if(j==20):
			j=0
			i += 1


	ax.set_xlim((-10, 10))
	ax.set_ylim((-10, 10))
	bound = plt.Circle((-0.5,-0.5), 9.1, fill=False)
	ax.add_artist(bound)
	plt.title("N = "+N)

#plt.show()
plt.savefig("quiverpdf.svg", format='svg', dpi=1200)
#plt.legend([red_dot, (red_dot, white_cross)], ["Attr A", "Attr A+B"])
