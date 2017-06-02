
#include "animation.h"
#include <thread>
#include <iostream>
#include <vector>
#include "Disks.h"
#include "Collision.h"
#include <ctime>

#define NUM_OF_ITERATIONS 100000.0

double simulation(int N);


int main(int argc, char** argv){
	int NUM_OF_DISKS = 55;
	
	
	std::cout.precision(16);
	if(argc<2){
		std::cout<<"Include arg - a for animate or r for run (without animation)"<<std::endl;
		return 0;
	}
	if(*(argv[1])=='r'){
		Disks::animation =NULL;
		std::cout<<simulation(NUM_OF_DISKS )<<std::endl;
		return 0;
	}else if(*(argv[1])=='a'){
		Animation animation(NUM_OF_DISKS);
		animation.setup();
		Disks::animation = &animation;

		std::thread drawer(simulation, NUM_OF_DISKS);
		animation.draw();
		drawer.join();
		return 0;
	}else if(*(argv[1])=='t'){
		for(NUM_OF_DISKS=10; NUM_OF_DISKS<= 56; NUM_OF_DISKS++){
			simulation(NUM_OF_DISKS );
		}
		
	
	
	}
	else{
		std::cout<<"Option must be a for animate or r for run (without animation)"<<std::endl;
		return 0;
	}

}

double simulation(int NUM_OF_DISKS){
	std::vector<Collision> currentCollisions;
	Disks disks;
	disks.initialize(NUM_OF_DISKS);

	double total_ang_vel = 0;
	
	
	for(int iterations = 0; iterations<NUM_OF_ITERATIONS; iterations++){
		total_ang_vel += disks.getAngVel();
		disks.nextCollisions(currentCollisions);
		disks.updatePositions(currentCollisions[0].getTime());
		for(int i=0; i<currentCollisions.size(); i++){
			disks.processCollision(currentCollisions[i]);
		}
	}
	disks.printStats();
	return total_ang_vel/NUM_OF_ITERATIONS;
}
