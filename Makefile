CPPFLAGS = -std=c++11 -O2 -MMD
AFLAGS =  -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
LDFLAGS = -std=c++11 `pkg-config --libs lib/glfw3.pc` 
N=55

SRCS = src/cross.cpp src/Collision.cpp src/circle.cpp src/Disks.cpp src/animation.cpp src/RotationSim.cpp src/stats.cpp src/next-event.cpp src/process-event.cpp
OBJS = build/cross.o build/Collision.o build/circle.o build/Disks.o build/animation.o build/RotationSim.o build/stats.o build/lib/glew.o build/next-event.o build/process-event.o

all: RotationSim


build/lib/glew.o: glew.c
	gcc -c $< -o $@ $(LDFLAGS)

build/%.o: src/%.cpp 
	g++ $(CPPFLAGS) -c -o $@ $<


RotationSim: ${OBJS}
	g++ $(CPPFLAGS) $^ -o $@ $(LDFLAGS) $(AFLAGS)

.PHONY: clean

clean:
	rm build/*.o
test:
	./RotationSim t
animate:
	./RotationSim a ${N}
run:
	./RotationSim r ${N}


-include $(OBJS:.o=.d)