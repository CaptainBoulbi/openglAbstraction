#include "engine.hpp"

#include <iostream>

void info(){
	std::cout << "\033[2J\033[7A";
	std::cout << "Life Time :";
	std::cout << currentTime << std::endl;
	std::cout << "FPS :";
	std::cout << 1 / deltaTime << std::endl;
	std::cout << "average FPS :";
	std::cout << nbFrame / currentTime << std::endl;
	std::cout << "MS :";
	std::cout << deltaTime << std::endl;
}

int main(){
	engineStartUp("hamood");
	engineResizeScreen(50, 50);

	while (!engineShouldClose()){
		info();
		engineSwapBuffers();
	}

	engineTearDown();
	return 1;
}
