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

void inputfn(){
	if (input.w) std::cout << 'w';
	if (input.a) std::cout << 'a';
	if (input.s) std::cout << 's';
	if (input.d) std::cout << 'd';
	if (input.space) std::cout << "space";
	if (input.shift) std::cout << "shift";
	if (input.ctrl) std::cout << "ctrl";
	if (input.escp){
		std::cout << "escp";
		engineClose();
	}
	std::cout << std::endl;
}

int main(){
	engineStartUp("hamood");
	engineResizeScreen(50, 50);

	while (!engineShouldClose()){
		engineBeginFrame();

		info();
		inputfn();

		engineSwapBuffers();
	}

	engineTearDown();
	return 0;
}
