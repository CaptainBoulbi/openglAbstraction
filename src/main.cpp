#include "engine.hpp"

#include <iostream>

void info(){
	std::cout << "\033[2J\033[7A";
	std::cout << "Life Time :\t";
	std::cout << currentTime << std::endl;
	std::cout << "FPS :\t\t";
	std::cout << 1 / deltaTime << std::endl;
	std::cout << "average FPS :\t";
	std::cout << nbFrame / currentTime << std::endl;
	std::cout << "MS :\t\t";
	std::cout << deltaTime * 1000 << std::endl;
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
