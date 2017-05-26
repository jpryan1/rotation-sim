#include "circle.h"

GLuint Circle::modelLoc;

Circle::Circle(double radius){
	
	
	for(int i=0; i<3; i++) vertices.push_back(0);
	
	for(int i=0; i<30; i++){
		vertices.push_back( cos((PI*i) / 15.0));
		vertices.push_back( sin((PI*i) / 15.0));
		vertices.push_back( 0);
	}
	
	for(int i=1; i<29; i++){
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i+1);
	}
	
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLushort), &indices[0], GL_STATIC_DRAW);

}


void Circle::draw(GLfloat a, GLfloat b){
	glm::mat4 transform;
	transform = glm::translate(transform, glm::vec3(a,b,0));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (GLvoid*) 0);
}
