#include "simpleGraphics.hpp"
#include "GLFW/glfw3.h"

// GENERAL

void sg::setup(){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  Window sgSetupWindow(1920/2, 1080/2, "sg setup window");

  glfwMakeContextCurrent(sgSetupWindow.gwind);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "Failed to initialize GLAD" << std::endl;
    assert("Failed to initialize GLAD");
  }    

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);
}

void sg::setVsync(bool etat){
  glfwSwapInterval(etat);
}

void sg::glError(){
  GLenum errorCode;
  while ((errorCode = glGetError()) != GL_NO_ERROR){
    std::cout << errorCode << std::endl;
  }
}

// INPUT

// WINDOW

sg::Window::Window(unsigned int width, unsigned int height, const char* title){
  this->width = width;
  this->height = height;

  gwind = glfwCreateWindow(width, height, title, NULL, NULL);

  if (gwind == NULL){
    std::cout << "failed to create glfw window" << title << std::endl;
    glfwTerminate();
    assert("failed to create glfw window");
  }

  //glfwSetFramebufferSizeCallback(gwind, screenSizeCallback);
}

sg::Window::~Window(){
  destroy();
}

void sg::Window::destroy(){
  glfwDestroyWindow(gwind);
}

void sg::Window::close(){
  glfwSetWindowShouldClose(gwind, true);
}

void sg::Window::display(){
  glfwSwapBuffers(gwind);
  glfwPollEvents();
  processTime();
}

bool sg::Window::isOpen(){
  return !glfwWindowShouldClose(gwind);
}

void sg::Window::setPos(unsigned int x, unsigned int y){
  this->x = x;
  this->y = y;
  glfwSetWindowPos(gwind, x, y);
}

//void setPos(vec2 pos);

void sg::Window::setSize(unsigned int width, unsigned int height){
  this->width = width;
  this->height = height;
  glfwSetWindowSize(gwind, width, height);
  glViewport(0, 0, width, height);
}

//void setSize(vec2 size);

void sg::Window::setTitle(const char* title){
  glfwSetWindowTitle(gwind, title);
}

//void setIcon(unsigned int width, unsigned int height, const Uint8 *pixels)

void sg::Window::setVisible(bool etat){
  if (etat) glfwShowWindow(gwind);
  else glfwHideWindow(gwind);
}

void sg::Window::setCursorLock(bool etat){
  if (etat) glfwSetInputMode(gwind, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  else glfwSetInputMode(gwind, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void sg::Window::requestFocus(){
  glfwRequestWindowAttention(gwind);
}

void sg::Window::forceFocus(){
  glfwFocusWindow(gwind);
}

bool sg::Window::hasFocus(){
  return glfwGetWindowAttrib(gwind, GLFW_FOCUSED);
}

void sg::Window::processTime(){
  timeLastFrame = currentTime;
  currentTime= glfwGetTime();
  deltaTime = currentTime - timeLastFrame;
  nbFrame++;
}

void sg::Window::setFullscreen(bool etat){
  isFullscreen = etat;
  if (etat){
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowMonitor(gwind, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE); 
  }
  else glfwSetWindowMonitor(gwind, NULL, 0, 0, width, height, GLFW_DONT_CARE);
}



//void sg::Window::screenSizeCallback(GLFWwindow* window, int wid, int hei){
//  width  = wid;
//  height = hei;
//  glViewport(0, 0, wid, hei);
//}

