AFLAGS =  -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
LFLAGS = -std=c++11 `pkg-config --libs lib/glfw3.pc` 


build/Collision.o: src/Collision.cpp 
	g++ -std=c++11 -O2 -c -o build/Collision.o src/Collision.cpp

build/circle.o: src/circle.cpp src/circle.h
	g++ -std=c++11 -O2 -c -o build/circle.o src/circle.cpp

build/Disks.o: src/Disks.cpp src/animation.h src/stats.h src/Collision.h
	g++ -std=c++11 -O2 -c -o build/Disks.o src/Disks.cpp

build/animation.o: src/animation.cpp src/animation.h src/circle.h
	g++ -std=c++11 -O2 -c -o build/animation.o src/animation.cpp

build/RotationSim.o: src/RotationSim.cpp src/animation.h src/Disks.h src/Collision.h
	g++ -std=c++11 -O2 -c -o build/RotationSim.o src/RotationSim.cpp

build/stats.o: src/stats.cpp  src/stats.h
	g++ -std=c++11 -O2 -c -o build/stats.o src/stats.cpp



compile: build/Collision.o build/circle.o build/Disks.o build/animation.o build/RotationSim.o build/stats.o
	g++ -O2 $(LFLAGS) $(AFLAGS) build/stats.o build/Collision.o build/Disks.o build/RotationSim.o build/animation.o build/circle.o build/lib/glew.o -o RotationSim

test:
	./RotationSim t
animate:
	./RotationSim a
run:
	./RotationSim r
