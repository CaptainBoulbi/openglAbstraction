#include "simpleGraphics.hpp"

#include <iostream>

int main(){

  sg::setup();
  sg::setVsync(false);

  sg::Window w(1920/2, 1080/2, "main window");

  while (w.isOpen()){

    if (w.input.release[sg::Key::ESCAPE]) w.close();

    if (w.input.press[sg::Key::F]) w.setFullscreen(!w.isFullscreen);

    std::cout << "X:" << w.input.mXpos << " Y:" << w.input.mYpos << std::endl;

    w.display();
  }

  sg::glError();

	return 0;
}
