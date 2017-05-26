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
#include "animation.h"


class Collision;



class Disks{
	
	public:
	
		static double swirl_interval;
		static double boundrad;
		static double swirl_angle;
		static double mu;
		static double wmu;
		static Animation* animation;
		Disks(){}
		~Disks(){
			if(disks){
				delete [] disks;
			}
		}
		
		void initialize(int N);
		void updatePositions(double collisionTime);
		void draw();
		void nextCollisions(std::vector<Collision>& currentCollisions);
	
		Collision nextDiskCollision(Disk& a, Disk& b);
		Collision nextWallCollision(Disk& disk);
	
		void checkDiskCollisions( std::vector<Collision>& currentCollisions );
		void checkWallCollisions( std::vector<Collision>& currentCollisions );
		void checkSwirlCollision( std::vector<Collision>& currentCollisions );

		void addCollision(std::vector<Collision>& currentCollisions, Collision& collision);

	
		void processCollision(Collision& collision);
		void processNormalCollision(Collision& collision);
		void processWallCollision(Collision& collision);
		void swirl();
	
	
	double getAngVel();
	vec centerOfMass();
	double squareSum();
	
	
	
		Disk* disks;
	private:
		int num_of_disks;
		
		double boundpos[2];
		double boundvel[2];
		double swirl_time;
};


#endif
