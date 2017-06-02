
#include "animation.h"

std::mutex lock;



const GLuint WIDTH = 800, HEIGHT = 600;

// Shaders
const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"out vec3 fragPos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
	"fragPos = vec3(model * vec4(position, 1.0));\n"
	"gl_Position = projection*view*vec4(fragPos,1.0f);\n"
"}\0";

const GLchar* fragmentShaderSource = "#version 330 core\n"
"in vec3 fragPos;\n"
"out vec4 color;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"	color = ourColor;\n"
"}\n\0";

void Animation::initialize(){
	//Initialize GLFW
	if (!glfwInit())
	return;
	//Set GLFW settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Window", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();
	
	
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	
	glEnable(GL_DEPTH_TEST);
	
}

//The following function can be simplified with the introduction of a shader.cpp file
void Animation::compileShaders(){
	// Build and compile our shader program
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	//Use the newly linked shader program
	glUseProgram(shaderProgram);
}



void Animation::setup(){
	initialize();
	compileShaders();
	generateBuffers();
	generateShapes();
	setProjectionMatrices();
}

void Animation::generateBuffers(){
	//	We use three buffers.
	//	VBO (vertex buffer object) contains the vertex positions
	//	EBO (element buffer object) contains the indices of the vertices (aka the order to draw triangles)
	//	VAO (vertex attribute object) contains the alignment info of the data in the VBO
	glGenVertexArrays(1, &s_VAO);
	glGenBuffers(1, &s_VBO);
	glGenBuffers(1, &s_EBO);
	glGenVertexArrays(1, &b_VAO);
	glGenBuffers(1, &b_VBO);
	glGenBuffers(1, &b_EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(s_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_EBO);
	

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//Unbind VAO
	glBindVertexArray(0);
	
	glBindVertexArray(b_VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, b_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b_EBO);
	
	
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//Unbind VAO
	glBindVertexArray(0);
	
	

	
	
	
	
	

}

void Animation::generateShapes(){
	//Bind VAO so sphere data can be transferred to VBO buffers on construction
	glBindVertexArray(s_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
	
	circle = Circle(1);
	//bound = Circle(9.1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//Unbind
	glBindVertexArray(0);
	
	
	glBindVertexArray(b_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, b_VBO);
	
	bound = Circle(9.1);
	//bound = Circle(9.1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//Unbind
	glBindVertexArray(0);
	
}

void Animation::setProjectionMatrices(){
	//This function creates 4x4 transformation matrices which are then passed to uniforms.
	//The uniforms are accessed by the shaderProgram, which then applies the matrices to the vertex positions
	
	//Initialize to identity
	glm::mat4 view;
	glm::mat4 projection;
	
	//View is at z = +8
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -50.0f));
//	view = glm::rotate(view, (float) -(M_PI/8.0), glm::vec3(0.0f, 1.0f, 0.0f));
	//Projection has 45 degree FoV, aspect ratio given by the window's, and
	//records only those objects within 0.1f and 100.0f of the "camera"
	projection = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	
	// Get the locations of the shader's uniforms
	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
	colorLoc = glGetUniformLocation(shaderProgram, "ourColor");
	//Give the location of the model uniform to the Sphere class, so that translations can be applied
	//when Sphere::draw is called.
	Circle::modelLoc = modelLoc;
	// Set the uniforms of the other matrices now - they won't change.
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	
}

void Animation::draw(){
	//This loop runs until the window is closed. When this happens, this function reaches the last line, which results in the
	//entire program ending
	while(notReady);
	
	
	while (!glfwWindowShouldClose(window) )
	{
		/* Poll for and process events */
		glfwPollEvents();

		//Set background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Draw!
		drawShapes();
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);
	}
	
	//Cleanup
	glDeleteVertexArrays(1, &s_VAO);
	glDeleteBuffers(1, &s_VBO);
	glDeleteBuffers(1, &s_EBO);
	glfwTerminate();
	
}



void Animation::drawShapes(){
	
	
	
	glBindVertexArray(b_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, b_VBO);
	lock.lock();
	glUniform4f(colorLoc, 0.8f, 0.8f, 0.8f, 1.0f);
	bound.draw(boundpos[0], boundpos[1], 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	
	
	glBindVertexArray(s_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
	glUniform4f(colorLoc, 0.75f, 0.5f, 0.25f, 1.0f);
	for(int i=0; i<num_of_disks; i++){
		circle.draw(disks[i].pos[0], disks[i].pos[1], 0.01);
	}
	lock.unlock();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}



void Animation::setDisks(Disk* d, double* b){
	lock.lock();
	memcpy(disks, d, sizeof(Disk)*num_of_disks);
	boundpos[0] =b[0];
	boundpos[1] = b[1];
	lock.unlock();
	usleep(200);
}









