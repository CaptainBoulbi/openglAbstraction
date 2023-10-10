#include "input.hpp"

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
