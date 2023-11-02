#ifndef SG_WIND_HPP
#define SG_WIND_HPP

#include "input.hpp"

#include <iostream>
#include <cassert>
#include <string>

namespace sg{
  //// setup glfw, glad et opengl config
  //void setup();
  //// console log all opengl error
  //void glError();

  void screenSizeCallback(GLFWwindow* window, int width, int height);


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

    bool setVsync(bool etat);

    private:
    void processTime();
  };

}

#endif
