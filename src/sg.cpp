#include "sg.hpp"

#include "GLFW/glfw3.h"
#include "stb_image.h"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <iostream>


// GENERAL


void sg::setup(){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  Window sgSetupWindow(1920/2, 1080/2, "sg setoup window");

  glfwMakeContextCurrent(sgSetupWindow.gwind);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "Failed to initialize GLAD" << std::endl;
    assert("Failed to initialize GLAD");
  }    

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);

  glGenVertexArrays(1, &rectangleVAO);
  glGenBuffers(1, &rectangleVBO);
  glGenBuffers(1, &rectangleEBO);

  glBindVertexArray(rectangleVAO);

  glBindBuffer(GL_ARRAY_BUFFER, rectangleVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangleEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
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

void sg::screenSizeCallback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}


// INPUT


sg::Input::Input(){
  sg::inputRef[sg::Key::W] = GLFW_KEY_W;
  sg::inputRef[sg::Key::A] = GLFW_KEY_A;
  sg::inputRef[sg::Key::S] = GLFW_KEY_S;
  sg::inputRef[sg::Key::D] = GLFW_KEY_D;
  sg::inputRef[sg::Key::F] = GLFW_KEY_F;
  sg::inputRef[sg::Key::SPACE] = GLFW_KEY_SPACE;
  sg::inputRef[sg::Key::LEFT_SHIFT] = GLFW_KEY_LEFT_SHIFT;
  sg::inputRef[sg::Key::LEFT_CTRL] = GLFW_KEY_LEFT_CONTROL;
  sg::inputRef[sg::Key::ESCAPE] = GLFW_KEY_ESCAPE;
}

sg::Input input;

void sg::Input::processKey(Key k, bool glfw){
  press[k] = !press[k] && !hold[k] && glfw;
  release[k] = !release[k] && hold[k] && !glfw;
  hold[k] = glfw;
}

void sg::Input::process(GLFWwindow* gwind){
  for (int i=2; i<LAST_KEY; i++){
    processKey((Key)i, glfwGetKey(gwind, inputRef[i]) == GLFW_PRESS);
  }

  processKey(MOUSE_LEFT, glfwGetMouseButton(gwind, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);
  processKey(MOUSE_RIGHT, glfwGetMouseButton(gwind, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);

  glfwGetCursorPos(gwind, &mXpos, &mYpos);
}


// SHADER


sg::ShaderCode::ShaderCode(const char* path, ShaderType stype){
  type = stype;
  success = true;

  std::ifstream file;
  file.open(path);

  if (!file.is_open()){
    success = false;
    log = "Unable to open file";
    return;
  }

  std::string line;
  std::string code;

  bool found = false;
  while (std::getline(file, line)){
    if (!found && ((type == VERTEX && line == "#vertex shader") || (type == FRAGMENT && line == "#fragment shader"))){
      found = true;
      continue;;
    }else if (found && ((type == FRAGMENT && line == "#vertex shader") || (type == VERTEX && line == "#fragment shader"))){
      found = false;
      continue;
    }

    if (found){
      code += line + '\n';
    }
  }

  file.close();

  if (code == ""){
    success = false;
    log = "No shader type found";
    return;
  }

  const char* glCode = code.c_str();

  if (type == VERTEX) ID = glCreateShader(GL_VERTEX_SHADER);
  if (type == FRAGMENT) ID = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(ID, 1, &glCode, NULL);
  glCompileShader(ID);

  glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

  if (!success){
    if (type == VERTEX)
      log = (char*)"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
    else if (type == FRAGMENT)
      log = (char*)"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";

    char infoLog[512];
    glGetShaderInfoLog(ID, 512, NULL, infoLog);

    log += infoLog;
    return;
  }
}

sg::ShaderCode::~ShaderCode(){
  glDeleteShader(ID);
}


sg::Shader::Shader(const char* vpath, const char* fpath){
  ShaderCode vert(vpath, VERTEX);
  ShaderCode frag(fpath, FRAGMENT);

  if (!vert.success)
    log += vert.log;
  if (!frag.success)
    log += frag.log;

  compile(vert.ID, frag.ID);
}

sg::Shader::Shader(const char* path){
  ShaderCode vert(path, VERTEX);
  ShaderCode frag(path, FRAGMENT);

  if (!vert.success)
    log += vert.log;
  if (!frag.success)
    log += frag.log;

  compile(vert.ID, frag.ID);
}

sg::Shader::Shader(ShaderCode vcode, ShaderCode fcode){
  compile(vcode.ID, fcode.ID);
}

sg::Shader::~Shader(){
  glDeleteProgram(ID);
}

void sg::Shader::use(){
  glUseProgram(ID);
}

void sg::Shader::compile(unsigned int idv, unsigned int idf){
  ID = glCreateProgram();
  glAttachShader(ID, idv);
  glAttachShader(ID, idf);
  glLinkProgram(ID);

  char infoLog[512];
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ID, 512, NULL, infoLog);
    log += "ERROR::SHADER::PROGRAM::LINKING_FAILED\n";
    log += infoLog;
  }
}

void sg::Shader::setInt(const char* name, int value){
  use();
  glUniform1i(glGetUniformLocation(ID, name), value); 
}


// TEXTURE


sg::Texture::Texture(const char* path, bool flip){
  glGenTextures(1, &ID);
  glBindTexture(GL_TEXTURE_2D, ID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  if (flip) stbi_set_flip_vertically_on_load(true);

  unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
  if (data) {
    success = true;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    success = false;
    log = "Failed to load texture";
  }
  stbi_image_free(data);
}

sg::Texture::~Texture(){
  glDeleteTextures(1, &ID);
}


// SPRITE


void sg::Sprite::bind(sg::Texture text){
  textID = text.ID;
}

void sg::Sprite::bind(sg::Shader* shad){
  shader = shad;
}

void sg::Sprite::draw(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textID);

    shader->use();

    glBindVertexArray(rectangleVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


// WINDOW


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
