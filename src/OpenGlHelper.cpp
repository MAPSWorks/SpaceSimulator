#include "../include/OpenGlHelper.hpp"

#include <iostream>

GLFWwindow* OpenGlHelper::init(void){
	std::cout << "OpenGlHelper.cpp\tInitialize" << std::endl;
	
	// Initialise GLFW
	if(!glfwInit()){
		std::cerr << "Failed to initialize GLFW\n";
		return NULL;
	}else{
		std::cout << "OpenGlHelper.cpp\tInitialized GLFW\n";
	}
	
	// OpenGL hints
	glfwWindowHint(GLFW_SAMPLES, 4); 								// 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 					// We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 	//We don't want the old OpenGL
	
	GLFWwindow *window = glfwCreateWindow(1, 1, "Init", NULL, NULL);
	glfwMakeContextCurrent(window);
	
	// Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err){
        std::cout << "OpenGlHelper.cpp\tError: " << glewGetErrorString(err) << "\n";
        return NULL;
    }else{    
	    std::cout << "OpenGlHelper.cpp\tStatus: Using GLEW " << glewGetString(GLEW_VERSION) << "\n";
    }
	std::cout << "OpenGlHelper.cpp\tGLEW Init (Error = " << glewGetErrorString(glGetError()) << ")\n";
	
	return window;
}
