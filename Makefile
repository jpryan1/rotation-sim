AFLAGS =  -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
LFLAGS = -std=c++11 `pkg-config --libs lib/glfw3.pc` 


build/Collision.o: src/Collision.cpp 
	g++ -O2 -c -o build/Collision.o src/Collision.cpp

build/circle.o: src/circle.cpp 
	g++ -O2 -c -o build/circle.o src/circle.cpp

build/Disks.o: src/Disks.cpp 
	g++ -O2 -c -o build/Disks.o src/Disks.cpp

build/animation.o: src/animation.cpp
	g++ -O2 -c -o build/animation.o src/animation.cpp

build/RotationSim.o: src/RotationSim.cpp 
	g++ -std=c++11 -O2 -c -o build/RotationSim.o src/RotationSim.cpp



compile: build/Collision.o build/circle.o build/Disks.o build/animation.o build/RotationSim.o
	g++ -O2 $(LFLAGS) $(AFLAGS) build/Collision.o build/Disks.o build/RotationSim.o build/animation.o build/circle.o build/glew.o -o RotationSim

run:
	./RotationSim
