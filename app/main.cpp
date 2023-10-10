#include "sg.hpp"

#include <iostream>

int main(){

  sg::setup();
  sg::setVsync(false);

  sg::Window w(1920/2, 1080/2, "man window");

  sg::Texture mac("data/macaque.jpg", true);
  if (!mac.success)
    std::cout << mac.log << std::endl;

  sg::Shader defaultShader("shader/texture.glsl");
  if (!defaultShader.success)
    std::cout << defaultShader.log << std::endl;

  defaultShader.setInt("texture1", 0);

  sg::Sprite player;
  player.bind(mac);
  player.bind(&defaultShader);

  std::cout << std::endl;

  while (w.isOpen()){

    w.clear(0.2f, 0.3f, 0.3f);

    if (w.input.release[sg::Key::ESCAPE])
      w.close();
    if (w.input.press[sg::Key::F])
      w.setFullscreen(!w.isFullscreen);

    std::cout << "\033[1A" << w.nbFrame / w.currentTime  << std::endl;

    player.draw();

    w.display();
  }

  sg::glError();

  return 0;
}
