#include "simpleGraphics.hpp"

#include <iostream>
#include <string>

int main(){

  sg::setup();
  sg::setVsync(false);

  sg::Window w(1920/2, 1080/2, "main window");

  while (w.isOpen()){
    std::string titre = std::to_string((int) (w.nbFrame / w.currentTime));

    w.setTitle(titre.c_str());

    w.display();
  }

  sg::glError();

	return 0;
}
