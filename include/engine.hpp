#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <cassert>

unsigned int SCR_WIDTH = 1920 / 2;
unsigned int SCR_HEIGHT = 1080 / 2;

float deltaTime = 0.0f;
float timeLastFrame = 0.0f;
float currentTime = 0.0f;
unsigned int nbFrame = 0;

GLFWwindow* engineWindow;

void engineStartUp(const char* titre);
bool engineShouldClose();
void engineBeginFrame();
void engineEndFrame();
void engineResizeScreen(int width, int height);
void engineClose();
void engineTearDown();
void engineFullscreen();
void engineQuitFullscreen();

void engineScreenSizeCallback(GLFWwindow* engineWindow, int width, int height);

void processTime();

#include "input.hpp"

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
	glfwSetCursorPosCallback(engineWindow, mousePosCallback);
	glfwSetMouseButtonCallback(engineWindow, mouseButtonCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "Failed to initialize GLAD" << std::endl;
		assert("Failed to initialize GLAD");
	}    

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(engineWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
	//glfwSetInputMode(engineWindow, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
	
	setupInputRef();
}


bool engineShouldClose(){
	return glfwWindowShouldClose(engineWindow);
}

void engineBeginFrame(){
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	processTime();
	processInput();
}

void engineEndFrame(){
	//input.release[LEFT_MOUSE] = false;
	//input.release[LEFT_MOUSE] = false;

	glfwSwapBuffers(engineWindow);
	glfwPollEvents();
}

void engineResizeScreen(int width, int height){
	glfwSetWindowSize(engineWindow, width, height);
	engineScreenSizeCallback(NULL, width, height);
}

void engineClose(){
	glfwSetWindowShouldClose(engineWindow, true);
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

void engineFullscreen(){
	glfwSetWindowMonitor(engineWindow, glfwGetPrimaryMonitor(), 0, 0, 1920, 1080, GLFW_DONT_CARE);
}

void engineQuitFullscreen(){
	glfwSetWindowMonitor(engineWindow, NULL, 0, 0, 1920 / 2, 1080 / 2, GLFW_DONT_CARE);
}

#include "shader.hpp"

#endif
