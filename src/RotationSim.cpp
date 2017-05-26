
#include "animation.h"
#include <thread>
#include <iostream>
#include <vector>
#include "Disks.h"
#include "Collision.h"
#include <ctime>


void simulation();


int main(int argc, char** argv){
	std::cout.precision(16);
//	Animation animation(50);
	//	animation.setup();
	//	Disks::animation = &animation;
	Disks::animation =NULL;
	//animation.notReady = true;
	
	std::thread drawer(simulation);
	//animation.draw();
	drawer.join();
	return 0;
}

void simulation(){
	std::vector<Collision> currentCollisions;
	Disks disks;
	disks.initialize(55);

	double total_ang_vel = 0;
	
	
	for(int iterations = 0; iterations<100000; iterations++){
		total_ang_vel += disks.getAngVel();
		disks.nextCollisions(currentCollisions);
		disks.updatePositions(currentCollisions[0].getTime());
		for(int i=0; i<currentCollisions.size(); i++){
			disks.processCollision(currentCollisions[i]);
		}
		
		
	}
	std::cout<<(total_ang_vel/100000.0)<<std::endl;
}


