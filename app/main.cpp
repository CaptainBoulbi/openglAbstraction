#include <iostream>

#include "sg.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

int main () {

  sg::Window wind(1280, 720, "hamood");

  while (!wind.input.release[sg::Key::ESCAPE]);
  
  wind.destroy();
  return 0;
}
