#ifndef  _COLLISION_H_    /* only process this file once */
#define  _COLLISION_H_


#include <stdlib.h>
#include <iostream>     
#include <fstream>
#include <cmath>
#include "type.h"
#include "disk.h"

class Collision{
	
	public:
		Collision(){}
		Collision(double t) : time(t), type(SWIRL) {}
		Collision(double t, Disk& a, Disk& b){
			time = t;
			type = NORMAL;
			disks[0] = &a;
			disks[1] = &b;
		}
		Collision(double t, Disk& a){
			time = t;
			type = WALL;
			disks[0] = &a;
			disks[1] = NULL;
		}
		Collision(const Collision &other);
		double getTime();
		Type getType();
	
		Disk* disks[2];
	
	private:
		Type type;
		double time;
		
	
};


#endif
