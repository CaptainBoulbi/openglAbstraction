#include "engine.hpp"

#include <iostream>

void info(){
	std::cout << "\033[2J\033[0;0H";
	std::cout << "Life Time :\t";
	std::cout << currentTime << std::endl;
	std::cout << "FPS :\t\t";
	std::cout << 1 / deltaTime << std::endl;
	std::cout << "average FPS :\t";
	std::cout << nbFrame / currentTime << std::endl;
	std::cout << "MS :\t\t";
	std::cout << deltaTime * 1000 << std::endl;
	std::cout << SCR_WIDTH << '/' << SCR_HEIGHT << std::endl;;
}

void showInput(){
	if (input.hold[W]) std::cout << 'w';
	if (input.hold[A]) std::cout << 'a';
	if (input.hold[S]) std::cout << 's';
	if (input.hold[D]) std::cout << 'd';
	if (input.hold[F]) std::cout << 'f';
	if (input.hold[SPACE]) std::cout << "space";
	if (input.hold[LEFT_SHIFT]) std::cout << "shift";
	if (input.hold[LEFT_CTRL]) std::cout << "ctrl";
	if (input.press[MOUSE_LEFT]) std::cout << "\033[34mGPress";
	if (input.press[MOUSE_RIGHT]) std::cout << "\033[1mDPress";
	if (input.hold[MOUSE_LEFT]) std::cout << "GHold";
	if (input.hold[MOUSE_RIGHT]) std::cout << "DHold";
	if (input.release[MOUSE_LEFT]) std::cout << "\033[37mGRelease";
	if (input.release[MOUSE_RIGHT]) std::cout << "\033[22mDRelease";
	std::cout << "X:" << input.mXpos;
	std::cout << "Y:" << input.mYpos;
	if (input.hold[ESCAPE]) std::cout << "escape";
	std::cout << std::endl;
}

int main(){
	engineStartUp("hamood");
	bool fullscreen = false;

	while (!engineShouldClose()){
		engineBeginFrame();

		info();
		showInput();

		if (input.press[ESCAPE]) engineClose();
		if (input.press[SPACE]) engineResizeScreen(500, 500);
		if (input.press[F]){
			if (fullscreen) engineQuitFullscreen();
			else engineFullscreen();
			fullscreen = !fullscreen;
		}

		engineEndFrame();
	}

	engineTearDown();
	return 0;
}
