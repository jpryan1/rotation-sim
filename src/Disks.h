#ifndef  _DISKS_H_    /* only process this file once */
#define  _DISKS_H_


#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "vec.h"
#include "type.h"
#include "disk.h"
#include "stats.h"
#include "animation.h"
#include "Collision.h"


class Collision;


class Disks{
	
	public:
	
	//Constants
		const double swirl_interval = 1;
		const double boundrad = 9.1;
		const double swirl_angle = 3.14159265359 / 6;
		const double mu = 10;
		const double wmu = 10;
	
		//Set by the main function in RotationSim.cpp depending on
		//whether we're animating
		static Animation* animation;
	
		Disks(){}
		~Disks(){
			if(disks){
				delete [] disks;
			}
		}
		void initialize(int N);
	
		//		Various stats functions.
		//
		void printStats();
		double getAngVel();
		vec centerOfMass();
		vec centerOfMassVel();

	
	
	
		//		FIND NEXT EVENT
		//
		void nextCollisions(std::vector<Collision>& currentCollisions);
		Collision nextDiskCollision(Disk& a, Disk& b);
		Collision nextWallCollision(Disk& disk);
		void checkDiskCollisions( std::vector<Collision>& currentCollisions );
		void checkWallCollisions( std::vector<Collision>& currentCollisions );
		void checkSwirlCollision( std::vector<Collision>& currentCollisions );
		void addCollision(std::vector<Collision>& currentCollisions, Collision& collision);

	
	
	
		//		PROCESS EVENT
		//
		void updatePositions(double collisionTime);
		
		void processCollision(Collision& collision);
			void processNormalCollision(Collision& collision);
			void processWallCollision(Collision& collision);
			void swirl();
		
	
	
	
		//The disks!
		Disk* disks;
	
	private:
	
		int num_of_disks;
		Stats stats;
		double boundpos[2];
		double boundvel[2];
		double swirl_time;
};


#endif
