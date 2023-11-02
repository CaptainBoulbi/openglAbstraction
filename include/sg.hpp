#ifndef SG_SG_HPP
#define SG_SG_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "input.hpp"
#include "wind.hpp"

//void sg::setup(){
//  glfwInit();
//  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//  Window sgSetupWindow(1920/2, 1080/2, "sg setoup window");
//
//  glfwMakeContextCurrent(sgSetupWindow.gwind);
//
//  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
//    std::cout << "Failed to initialize GLAD" << std::endl;
//    assert("Failed to initialize GLAD");
//  }    
//
//  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//  glEnable(GL_DEPTH_TEST);
//
//  glGenVertexArrays(1, &rectangleVAO);
//  glGenBuffers(1, &rectangleVBO);
//  glGenBuffers(1, &rectangleEBO);
//
//  glBindVertexArray(rectangleVAO);
//
//  glBindBuffer(GL_ARRAY_BUFFER, rectangleVBO);
//  glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);
//
//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangleEBO);
//  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rectangleIndices), rectangleIndices, GL_STATIC_DRAW);
//
//  // position attribute
//  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//  glEnableVertexAttribArray(0);
//  // color attribute
//  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//  glEnableVertexAttribArray(1);
//  // texture coord attribute
//  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//  glEnableVertexAttribArray(2);
//}
//
//void sg::setVsync(bool etat){
//  glfwSwapInterval(etat);
//}
//
//void sg::glError(){
//  GLenum errorCode;
//  while ((errorCode = glGetError()) != GL_NO_ERROR){
//    std::cout << errorCode << std::endl;
//  }
//}

#endif // !SG_SG_HPP

