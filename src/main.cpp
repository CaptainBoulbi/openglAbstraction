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
	std::cout << SCR_WIDTH << '/' << SCR_HEIGHT << std::endl;;
}

void showInput(){
	if (input.w) std::cout << 'w';
	if (input.a) std::cout << 'a';
	if (input.s) std::cout << 's';
	if (input.d) std::cout << 'd';
	if (input.f) std::cout << 'f';
	if (input.space) std::cout << "space";
	if (input.shift) std::cout << "shift";
	if (input.ctrl) std::cout << "ctrl";
	if (input.mLeftPress) std::cout << "\033[34mGPress";
	if (input.mRightPress) std::cout << "\033[1mDPress";
	if (input.mLeftHold) std::cout << "GHold";
	if (input.mRightHold) std::cout << "DHold";
	if (input.mLeftRelease) std::cout << "\033[37mGRelease";
	if (input.mRightRelease) std::cout << "\033[22mDRelease";
	std::cout << "X:" << input.mXpos;
	std::cout << "Y:" << input.mYpos;
	if (input.escape) std::cout << "escape";
	std::cout << std::endl;
}

int main(){
	engineStartUp("hamood");
	bool fullscreen = false;

	while (!engineShouldClose()){
		engineBeginFrame();

		info();
		showInput();

		if (input.escape) engineClose();
		if (input.space) engineResizeScreen(500, 500);
		if (input.f){
			if (fullscreen) engineQuitFullscreen();
			else engineFullscreen();
			fullscreen = !fullscreen;
		}

		engineEndFrame();
	}

	engineTearDown();
	return 0;
}
