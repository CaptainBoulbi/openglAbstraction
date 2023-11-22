#include "sg.hpp"

#include <iostream>

//TODO
//renderer
//shader
//audio
//camera

int main(){

  sg::setup();

  sg::Window w(1920/2, 1080/2, "man window");
  sg::setVsync(false);

  std::cout << std::endl;

  while (w.isOpen()){

    w.clear(0.2f, 0.3f, 0.3f);

    if (w.input.release[sg::Key::ESCAPE])
      w.close();
    if (w.input.press[sg::Key::F])
      w.setFullscreen(!w.isFullscreen);

    std::cout << "\033[1A" << w.nbFrame / w.currentTime  << std::endl;

    w.display();
  }

  sg::glError();

  return 0;
}
