#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <cassert>

#include "shader.hpp"

unsigned int SCR_WIDTH = 1920;
unsigned int SCR_HEIGHT = 1080;

float deltaTime = 0.0f;
float timeLastFrame = 0.0f;
float currentTime = 0.0f;
unsigned int nbFrame = 0;

GLFWwindow* engineWindow;

void engineStartUp(const char* titre);
bool engineShouldClose();
void engineSwapBuffers();
void engineResizeScreen(int width, int height);
void engineTearDown();

void engineScreenSizeCallback(GLFWwindow* engineWindow, int width, int height);

void processTime();


void engineStartUp(const char* titre){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	engineWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, titre, NULL, NULL);
	if (engineWindow == NULL){
		std::cout << "Failed to create GLFW engineWindow" << std::endl;
		glfwTerminate();
		assert("Failed to create GLFW engineWindow");
	}
	glfwMakeContextCurrent(engineWindow);

	glfwSetFramebufferSizeCallback(engineWindow, engineScreenSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initialize GLAD" << std::endl;
		assert("Failed to initialize GLAD");
	}    

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(engineWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
}


bool engineShouldClose(){
	return glfwWindowShouldClose(engineWindow);
}

void engineSwapBuffers(){
	processTime();
	glfwSwapBuffers(engineWindow);
	glfwPollEvents();
}

void engineResizeScreen(int width, int height){
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
	glViewport(0, 0, width, height);
}

void engineTearDown(){
	glfwTerminate();
}

void engineScreenSizeCallback(GLFWwindow* window, int width, int height){
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
	glViewport(0, 0, width, height);
}

void processTime(){
	timeLastFrame = currentTime;
	currentTime= glfwGetTime();
	deltaTime = currentTime - timeLastFrame;
	nbFrame++;
}

#endif
