
#include "stats.h"
#define PI 3.1415926535897932

void Stats::initialize(int N){
	disks = new Disk[N];
	num_of_disks = N;
	
	//M is originally at bottom in lab frame,
	//which is 180 degrees from where it is in M-frame
	M_ang = PI;
	
	//Zero out the bins
	for(int i=0; i<DENSITY_BINS; i++){
		for(int j=0; j<DENSITY_BINS; j++){
			hist[i][j] = 0;
		}
	}
	for(int i=0; i<QUIVER_BINS; i++){
		for(int j=0; j<QUIVER_BINS; j++){
			quiver_counts[i][j] = 0;
			for(int k=0; k<2; k++){
				quiver_hist[i][j][k] = 0;
			}
		}
	}
	for(int i=0;i<HEATMAP_BINS; i++){
		ang_vels[i] = 0;
		ang_counts[i] = 0;
	}
	CoM[0] = 0;
	CoM[1] = 0;
}

void Stats::update(Disk* d, double* b, double* bv, double time){
	//Start by recording data into OWN PERSONAL DISKS
	
	memcpy(disks, d, num_of_disks*sizeof(Disk));
	memcpy(boundpos, b, 2*sizeof(double));
	memcpy(boundvel, bv, 2*sizeof(double));
	//This only happens when stats is initialized - we don't do processing on input data
	if(time<0) return;
	
	
	//Update M_ang
	M_ang -= time*(PI / 6);
	if(M_ang<0) M_ang += (2*PI);
	
	//Used for CoM calculation
	double totalx=0;
	double totaly=0;
	
	
	for(int i=0; i<num_of_disks; i++){
		//First, we put our personal disks in M-frame. Subtract bound center...
		disks[i].pos[0] -= boundpos[0];
		disks[i].pos[1] -= boundpos[1];
		
		//...then rotate so M is up top
		double temp = disks[i].pos[0];
		disks[i].pos[0] = cos(M_ang)*disks[i].pos[0] - sin(M_ang)*disks[i].pos[1];
		disks[i].pos[1] = sin(M_ang)*temp + cos(M_ang)*disks[i].pos[1];
		
		//Rotate velocity, subtract boundvel
		disks[i].vel[0] -= bv[0];
		disks[i].vel[1] -= bv[1];
		
		temp = disks[i].vel[0];
		disks[i].vel[0] = cos(M_ang)*disks[i].vel[0] - sin(M_ang)*disks[i].vel[1];
		disks[i].vel[1] = sin(M_ang)*temp + cos(M_ang)*disks[i].vel[1];
		
		//This is for CoM
		totalx+=disks[i].pos[0];
		totaly+=disks[i].pos[1];
		
		//This is for density histogram
		int m = floor(((disks[i].pos[0]+9.1)/18.2)*DENSITY_BINS);
		int n = floor(((disks[i].pos[1]+9.1)/18.2)*DENSITY_BINS);
		hist[n][m] += 1;
		
		
		m = floor(((disks[i].pos[0]+9.1)/18.2)*QUIVER_BINS);
		n = floor(((disks[i].pos[1]+9.1)/18.2)*QUIVER_BINS);
		
		//This is for quiver plot
		quiver_hist[n][m][0] += disks[i].vel[0];
		quiver_hist[n][m][1] += disks[i].vel[1];
		quiver_counts[n][m] += 1;
	}
	
	
	CoM[0] += totalx/num_of_disks;
	CoM[1] += totaly/num_of_disks;
	
	
	//This is all for heatmap plot
	for(int i=0; i<num_of_disks; i++){
		double r1 = disks[i].pos[0];
		double r2 = disks[i].pos[1];
		
		
		
		double rsquared = pow(r1,2) + pow(r2,2);
		double rcrossv = r1*(disks[i].vel[1]) - r2*(disks[i].vel[0]);
		
		//Find index based on angle
		double ang = PI + atan2(r2, r1);
		int ind = floor((ang/(2*PI))*HEATMAP_BINS);
		
		ang_vels[ind] += rcrossv/rsquared;
		ang_counts[ind] += 1;
		
	}
}

void Stats::printRad(){
	CoM[0] = CoM[0] / 1000000.0;
	CoM[1] = CoM[1] / 1000000.0;
	double n = sqrt(pow(CoM[0],2) + pow(CoM[1],2));
	std::cout<<9.1-n<<std::endl;
}
void Stats::printCoM(){
	CoM[0] = CoM[0] / 1000000.0;
	CoM[1] = CoM[1] / 1000000.0;
	std::cout<<CoM[0]<<" "<<CoM[1]<<std::endl;
	
}

void Stats::printHeatMap(){
	for(int i=0; i<HEATMAP_BINS; i++){
		std::cout<<(ang_vels[i]/ang_counts[i])<<std::endl;
	}
}

void Stats::printQuiver(){
	for(int i=0; i<QUIVER_BINS; i++){
		for(int j=0; j<QUIVER_BINS; j++){
			std::cout<<(quiver_hist[i][j][0]/quiver_counts[i][j])
			<<" "<<(quiver_hist[i][j][1]/quiver_counts[i][j])<<std::endl;
		}
	}
}

void Stats::printDensity(){
	
	for(int i=0; i<DENSITY_BINS; i++){
		for(int j=0; j<DENSITY_BINS; j++){
			std::cout<<hist[i][j]<<std::endl;
		}
	}
	
}



