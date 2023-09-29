#ifndef SIMPLE_GRAPHICS_HPP
#define SIMPLE_GRAPHICS_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <cassert>

//#include "shader.hpp"
//#include "input.hpp"

namespace sg{

  // GENERAL

  void setup();
  void setVsync(bool etat);
  void glError();

  // WINDOW

  struct Window{
    GLFWwindow* gwind; 
    unsigned int width;
    unsigned int height;
    unsigned int x;
    unsigned int y;
    bool isFullscreen;

    float deltaTime = 0.0f;
    float timeLastFrame = 0.0f;
    float currentTime = 0.0f;
    unsigned int nbFrame = 0;

    Window(unsigned int width, unsigned int height, const char* title);
    ~Window();
    void destroy();
    void close();
    void display();
    bool isOpen();
    void setPos(unsigned int x, unsigned int y);
    void getPos(unsigned int* x, unsigned int* y);
    //void setPos(vec2 pos);
    void setSize(unsigned int width, unsigned int height);
    void getSize(unsigned int* width, unsigned int* height);
    //void setSize(vec2 size);
    void setTitle(const char* title);
    //void setIcon(unsigned int width, unsigned int height, const Uint8 *pixels)
    void setVisible(bool etat);
    void setCursorLock(bool etat);
    void requestFocus();
    void forceFocus();
    bool hasFocus();
    void setFullscreen(bool etat);

    private:
    //void screenSizeCallback(GLFWwindow* window, int width, int height);
    void processTime();
  };

  // INPUT


  


  //  }
  //  glfwMakeContextCurrent(engineWindow);
  //  glfwSwapInterval(0);


  //  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  //  glEnable(GL_DEPTH_TEST);

  //  glfwSetInputMode(engineWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
  //  //glfwSetInputMode(engineWindow, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

  //  setupInputRef();
  //}


  //bool engineShouldClose(){
  //  return glfwWindowShouldClose(engineWindow);
  //}

  //void engineBeginFrame(){
  //  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  //  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //  processTime();
  //  processInput();
  //}

  //void engineEndFrame(){
  //  //input.release[LEFT_MOUSE] = false;
  //  //input.release[LEFT_MOUSE] = false;

  //  glfwSwapBuffers(engineWindow);
  //  glfwPollEvents();
  //}

  //void engineResizeScreen(int width, int height){
  //  glfwSetWindowSize(engineWindow, width, height);
  //  engineScreenSizeCallback(NULL, width, height);
  //}

  //void engineScreenSizeCallback(GLFWwindow* window, int width, int height){
  //  SCR_WIDTH = width;
  //  SCR_HEIGHT = height;
  //  glViewport(0, 0, width, height);
  //}

}

#endif
