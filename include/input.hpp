#ifndef SG_INPUT_HPP
#define SG_INPUT_HPP

#include "GLFW/glfw3.h"

namespace sg{

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

}

#endif // !SG_INPUT_HPP
