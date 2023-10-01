#include "simpleGraphics.hpp"

#include <iostream>

int main(){

  sg::setup();
  sg::setVsync(false);

  sg::Window w(1920/2, 1080/2, "main window");

  while (w.isOpen()){

    w.clear(0.2f, 0.3f, 0.3f);

    if (w.input.release[sg::Key::ESCAPE]) w.close();

    if (w.input.press[sg::Key::F]) w.setFullscreen(!w.isFullscreen);

    w.display();
  }

  sg::glError();

	return 0;
}
