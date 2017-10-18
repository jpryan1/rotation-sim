#include "Disks.h"


Collision Disks::nextDiskCollision(Disk& a, Disk& b){
	double time;
	
	double dv0 = a.vel[0]-b.vel[0];
	double dv1 = a.vel[1]-b.vel[1];
	double dp0 = a.pos[0]-b.pos[0];
	double dp1 = a.pos[1]-b.pos[1];
	
	
	double A = pow(dv0,2) + pow(dv1,2);
	double B = 2 * ( dp0* dv0 + dp1 *dv1);
	double C = pow(dp0,2) + pow(dp1,2) -4;
	//ball radius is 1, dist between two centers is 2, 2^2=4
	
	double det = B*B-4*A*C;
	if(det<0){
		time = -1;
	}
	else{
		double t = (0.0 - B - sqrt(det))/(2*A);
		if(t>1e-13){
			time = t;
			
		}else{
			time = -1;
		}
	}
	return Collision( time, a, b);
	
	
}

Collision Disks::nextWallCollision(Disk& a){
	double time;
	
	
	double dv0 = a.vel[0]-boundvel[0];
	double dv1 = a.vel[1]-boundvel[1];
	double dp0 = a.pos[0]-boundpos[0];
	double dp1 = a.pos[1]-boundpos[1];

	
	double A = pow(dv0,2) + pow(dv1,2);
	double B = 2 * ( dp0* dv0 + dp1 *dv1);
	double C = pow(dp0,2) + pow(dp1,2) - pow(boundrad-1, 2);
	double det = B*B-4*A*C;
	
	if(det<0){
		time = -1;
	}else{
		double t = (0.0 - B + sqrt(det))/(2*A);
		if(t>1e-13){
			time = t;
		}
		else{
			time = -1;
		}
	}
	
	return Collision( time, a);
	
}


/*The following four functions look for the next collision to occur by comparing the times
 of all collisions that will happen in the future
 */
void Disks::nextCollisions(std::vector<Collision>& currentCollisions){
	currentCollisions.clear();
	checkDiskCollisions( currentCollisions );
	checkWallCollisions( currentCollisions );
	if(boundvel[0] || boundvel[1] )  checkSwirlCollision( currentCollisions );
	
}

void Disks::checkDiskCollisions( std::vector<Collision>& currentCollisions ){
	Collision collision;
	
	for(int i=0; i<num_of_disks-1; i++){
		for(int j=i+1; j<num_of_disks; j++){
			collision = nextDiskCollision(disks[i], disks[j]);
			if(collision.getTime() == -1) continue;
			addCollision(currentCollisions, collision);
		}
	}
}

void Disks::checkWallCollisions( std::vector<Collision>& currentCollisions ){
	
	Collision collision;
	for(int i=0; i<num_of_disks; i++){
		collision = nextWallCollision(disks[i]);
		if(collision.getTime() ==-1) continue;
		addCollision(currentCollisions, collision);
	}
}

void Disks::checkSwirlCollision( std::vector<Collision>& currentCollisions ){
	
	Collision collision(swirl_interval - swirl_time);
	if(swirl_interval - swirl_time - currentCollisions[0].getTime() < 1e-13){
		//this will evaluate to true only if the swirl will be added
		swirl_time = 0;
	}else{
		swirl_time += currentCollisions[0].getTime();
	}
	addCollision( currentCollisions, collision);
	
	
}



/*
 This function deals with checking whether an event is the next to occur.
 It checks the event's time against the times of other events that are to take place shortly, 
 and adds the event if it is at least as soon as the soonest next event.
 Recall that we are using a vector of events because some events may happen at exactly the same time.
 */
void Disks::addCollision(std::vector<Collision>& currentCollisions, Collision& collision){
	
	
	//if currentcollisions is empty, just add
	//Time of vector is found by first collision. If we're within 1e13, we add.
	//If we're 1e13 faster than first one, we delete all that aren't as fast
	
	
	if(currentCollisions.size()==0){
		currentCollisions.push_back(collision);
		return;
	}
	
	double diff = currentCollisions[0].getTime() - collision.getTime();
	
	if( diff > 1e-13){
		currentCollisions.clear();
		currentCollisions.push_back(collision);
	}
	else if(fabs(diff) < 1e-13){
		currentCollisions.push_back(collision);
	}
}

