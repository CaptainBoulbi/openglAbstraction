#ifndef INPUT_HPP
#define INPUT_HPP

enum Key{
	W,A,S,D,F,
	SPACE,LEFT_SHIFT,LEFT_CTRL,ESCAPE,
	MOUSE_LEFT,MOUSE_RIGHT,		// important : laisser les boutton de la souris a la fin (avant LAST_KEY)
	LAST_KEY
};

int inputRef[LAST_KEY];

void setupInputRef(){
	inputRef[W] = GLFW_KEY_W;
	inputRef[A] = GLFW_KEY_A;
	inputRef[S] = GLFW_KEY_S;
	inputRef[D] = GLFW_KEY_D;
	inputRef[F] = GLFW_KEY_F;
	inputRef[SPACE] = GLFW_KEY_SPACE;
	inputRef[LEFT_SHIFT] = GLFW_KEY_LEFT_SHIFT;
	inputRef[LEFT_CTRL] = GLFW_KEY_LEFT_CONTROL;
	inputRef[ESCAPE] = GLFW_KEY_ESCAPE;
}

struct KeyBoard{
	bool press[LAST_KEY];
	bool hold[LAST_KEY];
	bool release[LAST_KEY];
	double mXpos;
	double mYpos;
}input;

void processKey(Key k, bool glfw){
	input.press[k] = !input.press[k] && !input.hold[k] && glfw;
	input.release[k] = !input.release[k] && input.hold[k] && !glfw;
	input.hold[k] = glfw;
}

bool GLFWMouseLeftPress = false;
bool GLFWMouseRightPress = false;

void processInput(){
	for (int i=0; i<LAST_KEY-2; i++){
		processKey((Key)i, glfwGetKey(engineWindow, inputRef[i]) == GLFW_PRESS);
	}

	processKey(MOUSE_LEFT, GLFWMouseLeftPress);
	processKey(MOUSE_RIGHT, GLFWMouseRightPress);
}

void mousePosCallback(GLFWwindow* engineWindow, double xpos, double ypos){
	input.mXpos = xpos;
	input.mYpos = ypos;
}

void mouseButtonCallback(GLFWwindow* engineWindow, int button, int action, int mods){
	if (button == GLFW_MOUSE_BUTTON_LEFT) GLFWMouseLeftPress = action == GLFW_PRESS;
	else if (button == GLFW_MOUSE_BUTTON_RIGHT) GLFWMouseRightPress = action == GLFW_PRESS;
}

#endif
