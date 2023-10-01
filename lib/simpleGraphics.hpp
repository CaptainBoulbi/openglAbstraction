#ifndef SIMPLE_GRAPHICS_HPP
#define SIMPLE_GRAPHICS_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

#include <iostream>
#include <cassert>

// TODO
// fix sg::setVsync()
// sprite.hpp
// shader.hpp
// gui.hpp
// camera.hpp
// sound.hpp
// vec2 fn

namespace sg{


  // GENERAL


  // setup glfw, glad et opengl config
  void setup();
  // enable / disable vsync
  // driver config will override it
  void setVsync(bool etat);
  // console log all opengl error
  void glError();

  void screenSizeCallback(GLFWwindow* window, int width, int height);


  // INPUT


  enum Key{
    MOUSE_LEFT,MOUSE_RIGHT,		// important : laisser les boutton de la souris au debut
    W,A,S,D,F,
    SPACE,LEFT_SHIFT,LEFT_CTRL,ESCAPE,
    LAST_KEY
  };
  
  inline int inputRef[sg::LAST_KEY];

  struct Input{
    bool press[LAST_KEY];
    bool hold[LAST_KEY];
    bool release[LAST_KEY];
    double mXpos;
    double mYpos;
    
    Input();
    void process(GLFWwindow* gwind);

    private:
    void processKey(Key k, bool glfw);
  };


  // IMAGE


  struct Image{
    unsigned char* data;

    bool flipped;

    int width;
    int height;
    int nrChannels;

    Image(const char* path, bool flip = false);
    ~Image();

    bool failedLoad();
  };


  // TEXTURE


  struct Texture{
    unsigned int ID;

    const char* path;
    sg::Image* image;

    bool flipped;

    int width;
    int height;
    int nrChannels;

    Texture(const char* path, bool flip = false);
    Texture(sg::Image* img);
    ~Texture();

    void setRepeat(bool etat);
    void refresh();
    bool failedLoad();
  };


  // SPRITE

  
  struct Sprite{
    float x;
    float y;
    float originX;
    float originY;
    float scaleX;
    float scaleY;
    float angle;
    unsigned int textID;

    Sprite(Texture* text);
    ~Sprite();
    void setPos(float x, float y);
    void move(float x, float y);
    void setRotation(float deg);
    void rotate(float deg);
    void setScale(float facx, float facy);
    void scale(float facx, float facy);
    void setOrigin(float x, float y);
  };


  // WINDOW


  struct Window{
    GLFWwindow* gwind; 
    bool isFullscreen;

    float deltaTime = 0.0f;
    float timeLastFrame = 0.0f;
    float currentTime = 0.0f;
    unsigned int nbFrame = 0;

    Input input;

    Window(unsigned int width, unsigned int height, const char* title);
    ~Window();
    // end life of window
    void destroy();
    // send a close signal to the window
    void close();
    // clear everything drawn
    void clear(float r, float g, float b);
    // target the window to draw for opengl
    void setActive(bool etat);
    // draw everithing to the window
    void display();
    // return if the window is open or if a close signal is sent
    bool isOpen();
    // change the position of the window in the screen
    void setPos(unsigned int x, unsigned int y);
    void getPos(int* x, int* y);
    //void setPos(vec2 pos);
    void setSize(unsigned int width, unsigned int height);
    void getSize(int* width, int* height);
    //void setSize(vec2 size);
    void setTitle(const char* title);
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
    void draw(Sprite* sprite);

    private:
    void processTime();
  };

}

#endif
