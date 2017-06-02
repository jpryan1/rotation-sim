
#ifndef  _ANIMATION_H_    /* only process this file once */
#define  _ANIMATION_H_

#define GLEW_STATIC
#include <iostream>
#include "circle.h"
#include <mutex>
#include <atomic>
#include <unistd.h>
#include "disk.h"

class Animation{
	public:
	
		Animation(){  }
		Animation(int n){
			num_of_disks = n;
			disks = new Disk[n];
			notReady = true;
			boundpos[0] = 0;
			boundpos[1] = 0;
		}
		void initialize();
		void setup();
		void compileShaders();
		void generateBuffers();
		void generateShapes();
		void setProjectionMatrices();
		void draw();
		void drawShapes();
		void setDisks(Disk* d, double* b);

		std::atomic<bool> notReady;
	
	private:
		GLuint s_VBO, s_VAO, s_EBO, shaderProgram, modelLoc, colorLoc, viewLoc;
		GLuint b_VBO, b_VAO, b_EBO;
		int width, height;
		GLFWwindow* window;
		Circle circle;
		Circle bound;
		Disk* disks;
	double boundpos[2];
		int num_of_disks;
	
	
};
#endif
