
#ifndef  _ANIMATION_H_    /* only process this file once */
#define  _ANIMATION_H_

#define GLEW_STATIC
#include <iostream>
#include "circle.h"
#include <mutex>
#include "disk.h"

class Animation{
	public:
	
		Animation(){  }
		Animation(int n){
			num_of_disks = n;
			disks = new Disk[n];
		}
		void initialize();
		void setup();
		void compileShaders();
		void generateBuffers();
		void generateShapes();
		void setProjectionMatrices();
		void draw();
		void drawShapes();
	
		void setDisks(Disk* d);
	private:
		GLuint s_VBO, s_VAO, s_EBO, shaderProgram, modelLoc, colorLoc, viewLoc;
		int width, height;
		GLFWwindow* window;
		Circle circle;
		Disk* disks;
		int num_of_disks;
	
};
#endif
