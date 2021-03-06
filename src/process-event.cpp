#include "Disks.h"

void Disks::updatePositions(double time){
	
	
	if(animation){
		animation->setDisks(disks, boundpos, boundvel);
		animation->moveDisks(time);
		
	}
	
	boundpos[0] += time*boundvel[0];
	boundpos[1] += time*boundvel[1];
	//if(swirl_time==0) printf("Boundary at %f %f\n", boundpos[0], boundpos[1]);
	for(int i=0; i<num_of_disks; i++){
		for(int j=0; j<2; j++){
			disks[i].pos[j] += time*disks[i].vel[j];
			
		}
		disks[i].ang += time*disks[i].ang_vel;
		
	}
	

	stats.update(disks, boundpos,boundvel, time);

}

void Disks::processCollision(Collision& collision){
	//Obligation here is just to change the trajectories of the affected disks




	double angvel_before, angvel_after;
	int which;
	




	//This is for measuring to what extent the wall collisions and disk collisions
	//are affecting the overall angular momentum
	angvel_before = getAngVel();


//This is a check to make sure that we are conserving momentum in our equations

	// double p_x_i, p_y_i, p_x_f, p_y_f;
	// double a_i, a_f;
//	double L_1_i, L_2_i, L_1_f, L_2_f, L_i,L_f;
//	 if(collision.getType()==NORMAL){
//
//	 	Disk* a = collision.disks[0];
//	 	Disk* b = collision.disks[1];
//	 	L_1_i = a->vel[1]*a->pos[0] - a->vel[0]*a->pos[1] + a->ang_vel;
//		L_2_i = b->vel[1]*b->pos[0] - b->vel[0]*b->pos[1] + b->ang_vel;
//		L_i = L_1_i+L_2_i;
//		 
//	 }

	
	switch(collision.getType()){
		case NORMAL:
			
			which = 0;
			processNormalCollision(collision);
	
			break;
			
		case WALL:
			which = 1;
			processWallCollision(collision);
			
			break;
			
		case SWIRL:
			which = 2;
			swirl();
			
			break;
	}



//
//	 if(collision.getType()==NORMAL){
//
//	 	Disk* a = collision.disks[0];
//	 	Disk* b = collision.disks[1];
//	 	
//		 L_1_f = a->vel[1]*a->pos[0] - a->vel[0]*a->pos[1] + a->ang_vel;
//	 	L_2_f = b->vel[1]*b->pos[0] - b->vel[0]*b->pos[1] + b->ang_vel;
//		 
//		 L_f = L_1_f+L_2_f;
//		 printf("Before %f + %f = %f after %f + %f = %f\n",L_1_i,L_2_i, L_i,
//				L_1_f, L_2_f,L_f);
//	 }


	angvel_after = getAngVel();
	
	//stats.updateContributions(angvel_after-angvel_before, which);
	
	
}


void Disks::processNormalCollision(Collision& collision){
	Disk s1 = *(collision.disks[0]);
	Disk s2 = *(collision.disks[1]);
	vec v1 = vec(collision.disks[0]->vel);
	vec v2 = vec(collision.disks[1]->vel);
	vec x1 = vec(collision.disks[0]->pos);
	vec x2 = vec(collision.disks[1]->pos);
	

	vec unit = x2.minus(x1).times(0.5);
	double angv1 = s1.ang_vel;
	double angv2 = s2.ang_vel;
	
	//Process as if elastic
	vec old_normal = unit.times(v1.dot(unit));
	double dot1 = v1.minus(v2).dot(x1.minus(x2));
	dot1 /= pow(x1.minus(x2).norm(), 2);
	vec s1vel = v1.minus(x1.minus(x2).times(dot1));
	double dot2 = v2.minus(v1).dot(x2.minus(x1));
	dot2 /= pow( x2.minus(x1).norm(), 2);
	vec s2vel = v2.minus(x2.minus(x1).times(dot2));
	
	
	//Part 3a - Break vectors into components
	vec newPerp1 = unit.times(s1vel.dot(unit));
	vec par1 = s1vel.minus(newPerp1);
	if(fabs(par1.norm())<1e-13){
		par1 = vec();
	}
	unit = unit.times(-1); //points towards x1
	vec newPerp2 = unit.times(s2vel.dot(unit));
	vec par2 = s2vel.minus(newPerp2);
	if(fabs(par2.norm())<1e-13){
		par2 = vec();
	}
	
	vec delv1perp = newPerp1.minus(old_normal);
	double DELTA = delv1perp.norm();
	//So named because it is the same for both disks
	
	
	
	
	//Part 3b - r0 is x2vel minus x1vel
	vec r0unit(unit.a[1], -unit.a[0]);
	
	vec r0 = par1.minus(par2).add(r0unit.times(angv1+angv2));
	int s0 = (r0.dot(r0unit) > 0 ? 1 : -1);
	
	//Part 3c - apply sticking rules
	double t = (r0.norm())/(mu*DELTA*2*((1.0/DISK_MASS)+(1.0/DISK_MOMENT)));
	if(mu==0){
		t=0;
	}
	t = fmin(t, 1);
	double impulse = mu*s0*DELTA*t;
	
	vec newPar1 = par1.minus(r0unit.times(impulse/DISK_MASS));
	vec newPar2 = par2.add(r0unit.times(impulse/DISK_MASS));
	
	memcpy(collision.disks[0]->vel, newPar1.add(newPerp1).a, 2*sizeof(double));
	memcpy(collision.disks[1]->vel, newPar2.add(newPerp2).a, 2*sizeof(double));
	angv1 -= impulse/DISK_MOMENT;
	angv2 -= impulse/DISK_MOMENT;
	collision.disks[0]->ang_vel = angv1;
	collision.disks[1]->ang_vel = angv2;
}

void Disks::processWallCollision(Collision& collision){

	Disk s = *(collision.disks[0]);
	double angv = s.ang_vel;
	vec bv(boundvel);
	vec rad(s.pos[0]-boundpos[0],s.pos[1]-boundpos[1]);
	double radNorm = rad.norm();
	rad = rad.times(1/radNorm); //rad is normal.
	

//	printf("Rad vector %f %f\n", rad.a[0], rad.a[1]);

	vec newVel(s.vel);
//	printf("Original disc velocity %f %f\n Original wall velocity %f %f\n",
//		newVel.a[0], newVel.a[1], bv.a[0], bv.a[1]);
//	printf("Ang vel was %f\n", angv);
	newVel = newVel.minus(bv);  //now we're in stationary boundary frame of reference
	vec perp = rad.times(newVel.dot(rad));

//printf("Stationary boundary frame now\n Normal vel %f %f\n", perp.a[0], perp.a[1]);

	vec par = newVel.minus(perp);
//printf("Tangent vel %f %f\n", par.a[0], par.a[1]);
	perp = perp.times(-1); //bonk
	double DELTA = 2*perp.norm();
	

	
	vec r0unit(-rad.a[1], rad.a[0]);
	vec r0 = par.add(r0unit.times(angv));
	int s0 = (r0.dot(r0unit) > 0 ? 1 : -1);
	double t = (r0.norm())/(wmu*DELTA*((1.0/DISK_MASS)+(1.0/DISK_MOMENT)));
	if(wmu==0){
		t=0;
	}
	t=fmin(t,1);
	double impulse = wmu*s0*DELTA*t;
	
	vec newPar = par.minus(r0unit.times(impulse/DISK_MASS));
	angv -= impulse/DISK_MOMENT;
//	printf("Angv is now %f\n", angv);
//	printf("New tangent vector %f %f\n", newPar.a[0], newPar.a[1]);
//	printf("New normal vector %f %f\n", perp.a[0], perp.a[1]);

	perp = perp.add(newPar);


	perp = perp.add(bv);
//	printf("Final velocity (lab frame) is %f %f\n\n\n\n", perp.a[0], perp.a[1]);
	for(int i=0; i<2; i++) collision.disks[0]->vel[i] = perp.a[i];
	collision.disks[0]->ang_vel = angv;
}


void Disks::swirl(){
	double v0 = boundvel[0];
	boundvel[0] = cos(swirl_angle) * boundvel[0] - sin(swirl_angle) * boundvel[1];
	boundvel[1] = sin(swirl_angle) * v0 + cos(swirl_angle) * boundvel[1];
}


