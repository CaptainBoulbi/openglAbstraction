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




// SHADER




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


void sg::Sprite::bind(sg::Texture* text){
  textID = text->ID;
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
