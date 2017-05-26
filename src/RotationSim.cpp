
#include "animation.h"
#include <thread>
#include <iostream>
#include <vector>
#include "Disks.h"
#include "Collision.h"





int main(int argc, char** argv){
	
	
	
	std::vector<Collision> currentCollisions;
	Disks disks;
	Animation animation(50);
	animation.setup();
	Disks::animation = &animation;
	disks.initialize(50);
	
	std::thread drawer(&Animation::draw, animation);
	
	for(int iterations = 0; iterations<100; iterations++){
		disks.nextCollisions(currentCollisions);
		disks.updatePositions(currentCollisions[0].getTime());
		for(int i=0; i<currentCollisions.size(); i++){
			disks.processCollision(currentCollisions[i]);
		}
	}
	std::cout<<"Hello World"<<std::endl;
	drawer.join();
	return 0;
}
