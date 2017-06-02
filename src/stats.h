
#ifndef  _STATS_H_    /* only process this file once */
#define  _STATS_H_
#include "disk.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <string.h>


class Stats{
	public:
		void initialize(int N);
		void update(Disk* d, double* b, double time);
	void print();
	void printRad();
	Disk* disks;
	long ang_counts[100];
	double ang_vels[100];
	
	~Stats(){
		if(disks) delete [] disks;
	}
	private:
		int num_of_disks;
		double boundpos[2];
		double CoM[2];
		double M_ang;
	
		int hist[100][100];
};



#endif
