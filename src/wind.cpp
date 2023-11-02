#include "wind.hpp"

void sg::screenSizeCallback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}

sg::Window::Window(unsigned int width, unsigned int height, const char* title){
  gwind = glfwCreateWindow(width, height, title, NULL, NULL);

  if (gwind == NULL){
    std::cout << "failed to create glfw window" << title << std::endl;
    glfwTerminate();
    assert("failed to create glfw window");
  }

  glfwMakeContextCurrent(gwind);

  glfwSetFramebufferSizeCallback(gwind, screenSizeCallback);
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

void sg::Window::clear(float r, float g, float b){
  glClearColor(r, g, b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void sg::Window::setActive(bool etat){
  if (etat) glfwMakeContextCurrent(gwind);
  else glfwMakeContextCurrent(NULL);
}

void sg::Window::display(){
  glfwSwapBuffers(gwind);
  glfwPollEvents();
  processTime();
  input.process(gwind);
}

bool sg::Window::isOpen(){
  return !glfwWindowShouldClose(gwind);
}

void sg::Window::setPos(unsigned int x, unsigned int y){
  glfwSetWindowPos(gwind, x, y);
}

void sg::Window::getPos(int* x, int* y){
  glfwGetWindowPos(gwind, x, y);
}

//void setPos(vec2 pos);

void sg::Window::setSize(unsigned int width, unsigned int height){
  glfwSetWindowSize(gwind, width, height);
  glViewport(0, 0, width, height);
}

void sg::Window::getSize(int* width, int* height){
  glfwGetWindowSize(gwind, width, height);
}

//void setSize(vec2 size);

void sg::Window::setTitle(const char* title){
  glfwSetWindowTitle(gwind, title);
}

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
  }else{
    int width, height;
    getSize(&width, &height);
    glfwSetWindowMonitor(gwind, NULL, 0, 0, width/2, height/2, GLFW_DONT_CARE);
  }
}
