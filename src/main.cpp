#include "simpleGraphics.hpp"

#include <iostream>

int main(){

  sg::setup();
  sg::setVsync(false);

  sg::Window w(1920/2, 1080/2, "main window");
  sg::Window w2(1920/2, 1080/2, "second window");

  while (w.isOpen()){
    std::string titre = std::to_string((int) (w.nbFrame / w.currentTime));
    w.setTitle(titre.c_str());

    if (w.currentTime > 5.0f) w.close();

    int width, height;
    w.getSize(&width, &height);
    std::cout << width << ':' << height << std::endl;

    w.display();
  }

  sg::glError();

	return 0;
}
