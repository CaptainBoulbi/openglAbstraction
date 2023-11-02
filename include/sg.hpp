#ifndef SG_SIMPLE_GRAPHICS_HPP
#define SG_SIMPLE_GRAPHICS_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

#include "input.hpp"
#include "window.hpp"
#include "shader.hpp"

#include <iostream>
#include <cassert>
#include <string>

// TODO
// fix sg::setVsync()
// sprite.hpp
// gui.hpp
// camera.hpp
// sound.hpp
// vec2 fn

namespace sg{


  // GENERAL


  // setup glfw, glad et opengl config
  void setup();
  // enable / disable vsync
  // call it when a window exist
  // driver config will override it
  void setVsync(bool etat);
  // console log all opengl error
  void glError();

  inline float rectangleVertices[] = {
    // positions          // colors           // texture coords
    1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
  };

  inline unsigned int rectangleIndices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
  };

  inline unsigned int rectangleVBO, rectangleVAO, rectangleEBO;


  // TEXTURE


  struct Texture{
    unsigned int ID;
    int width;
    int height;
    int nrChannels;

    bool success;
    const char* log;

    Texture(const char* path, bool flip = false);
    ~Texture();
  };


  // SPRITE


  struct Sprite{
    unsigned int textID;
    Shader* shader;
    
    void bind(Texture* text);
    void bind(Shader* shad);
    void draw();
  };

}

#endif
