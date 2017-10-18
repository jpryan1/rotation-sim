CPPFLAGS = -std=c++11 -O2
AFLAGS =  -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
LDFLAGS = -std=c++11 `pkg-config --libs lib/glfw3.pc` 
N=55

SRCS = src/cross.cpp src/Collision.cpp src/circle.cpp src/Disks.cpp src/animation.cpp src/RotationSim.cpp src/stats.cpp
OBJS = build/cross.o build/Collision.o build/circle.o build/Disks.o build/animation.o build/RotationSim.o build/stats.o build/lib/glew.o

all: RotationSim


build/lib/glew.o: glew.c
	gcc -c $< -o $@ $(LDFLAGS)

build/%.o: src/%.cpp 
	g++ $(CPPFLAGS) -c -o $@ $<


RotationSim: ${OBJS}
	g++ -O2 $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(AFLAGS)


clean:
	rm build/*.o
test:
	./RotationSim t
animate:
	./RotationSim a ${N}
run:
	./RotationSim r ${N}



depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	g++ $(CPPFLAGS) -MM $^ > ./.depend

include .depend