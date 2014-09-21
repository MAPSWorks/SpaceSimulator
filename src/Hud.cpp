#include "../include/Hud.hpp"

#include <iostream>

HUD::HUD(GLFWwindow *window){
	// Debug
	std::cout << "HUD.cpp\t\t\tInitializing" << std::endl;
	
	// Init
	glfwGetWindowSize(window, &width, &height);
	this->window = window;
	this->visible = true;
	this->stride = width*3;
	this->pixels = (unsigned char*)malloc(width*height*3*sizeof(unsigned char));
	this->drawService = new DrawService(width, height, pixels);
	this->pages = new std::vector<HudPage*>();
	this->activePage = 0;
	
	// Creating GUI elements
	left = new View(10, height/2, 50, 50);
	right = new View(width-60, height/2, 50, 50);
	
	// Texture
	float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	// Buffering texture	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	
	// Shader
	shader = new Shader("src/shaders/hudVertex.glsl", "src/shaders/hudFragment.glsl");
	
	// Generating vertex buffer
	float z = 0.f;
	float vertices[] = {-1.f, 1.f, z,		// Top left
						-1.f, -1.f, z,		// Bottom left
						1.f, 1.f, z,		// Top right
						1.f, -1.f, z,		// Bottom right
						1.f, 1.f, z,		// Top right
						-1.f, -1.f, z};		// Bottom left
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_DYNAMIC_DRAW);
						
	// Generating texture coordinate buffer						
	//float texCords[] = {0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 1.f, 0.f, 0.f, 1.f}; // Top Down
	float texCords[] = {0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f}; // Bottom up
	glGenBuffers(1, &texCordsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texCordsBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCords), &texCords, GL_DYNAMIC_DRAW);
}

HUD::~HUD(){
	std::cout << "HUD.cpp\t\t\tFinalizing" << std::endl;
	glDeleteTextures(1, &tex);
}

void HUD::update(void){
	left->draw(drawService);
	right->draw(drawService);
	
	glActiveTexture(GL_TEXTURE0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
}

void HUD::render(void){
	if(visible){		
		// Updating
		update();
		
		// Binding the Body shader
		shader->bind();
	
		// Activating texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
	
		// Get a handle for our "MVP" uniform.
		glm::mat4 mvp = glm::lookAt(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
		GLuint mvpMatrixId = glGetUniformLocation(shader->getID(), "MVP");
		glUniformMatrix4fv(mvpMatrixId, 1, GL_FALSE, &mvp[0][0]);

		// Binding vertex VBO
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, 0);

		// Binding color VBO
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, texCordsBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

		// Draw
		glDrawArrays(GL_TRIANGLES, 0, 6);
	
		// Disabling buffers
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void HUD::toogleVisibility(void){
	this->visible = !visible;
}

void HUD::hudClicked(int button, int action, int x, int y){
	if(right->isInside(x, y)){
		right->clicked(button, action);
	}else if(left->isInside(x, y)){
		left->clicked(button, action);
	}
	std::cout << "HUD click " << button << ", " << action << ", " << " (" << x << " x " << y << ")\n";
}
