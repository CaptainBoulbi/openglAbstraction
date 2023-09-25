#include "engine.hpp"

#include <iostream>

int main(){
	engineStartUp("hamood");
	engineResizeScreen(50, 50);

	std::cout << SCR_WIDTH << ':' << SCR_HEIGHT << std::endl;

	while (!engineShouldClose()){
		//std::cout << currentTime << ':' << deltaTime << std::endl;
		engineSwapBuffers();
	}

	engineTearDown();
	return 1;
}
