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

  // setup glfw, glad et opengl config
  void setup();
  // enable / disable vsync
  // driver config will override it
  void setVsync(bool etat);
  // console log all opengl error
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
    // end life of window
    void destroy();
    // send a close signal to the window
    void close();
    // draw everithing to the window
    void display();
    // return if the window is open or if a close signal is sent
    bool isOpen();
    // change the position of the window in the screen
    void setPos(unsigned int x, unsigned int y);
    void getPos(unsigned int* x, unsigned int* y);
    //void setPos(vec2 pos);
    void setSize(unsigned int width, unsigned int height);
    void getSize(unsigned int* width, unsigned int* height);
    //void setSize(vec2 size);
    void setTitle(const char* title);
    //void setIcon(unsigned int width, unsigned int height, const Uint8 *pixels)
    // show / hide the window
    void setVisible(bool etat);
    // lock the cursor in the window area and make it invisible
    void setCursorLock(bool etat);
    // send a signal to the os that the window need focus
    // on ubuntu it send a notification
    void requestFocus();
    // put the window in the first plan
    void forceFocus();
    // return if the window has the focus (if the user is on the window)
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
