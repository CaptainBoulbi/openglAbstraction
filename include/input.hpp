#ifndef INPUT_HPP
#define INPUT_HPP

struct KeyBoard{
	bool w;
	bool a;
	bool s;
	bool d;
	bool space;
	bool shift;
	bool ctrl;
	bool escape;
	bool mLeftPress;
	bool mRightPress;
	bool mLeftHold;
	bool mRightHold;
	bool mLeftRelease;
	bool mRightRelease;
	double mXpos;
	double mYpos;
}input;

void processInput(){
		input.w = glfwGetKey(engineWindow, GLFW_KEY_W) == GLFW_PRESS;
		input.a = glfwGetKey(engineWindow, GLFW_KEY_A) == GLFW_PRESS;
		input.s = glfwGetKey(engineWindow, GLFW_KEY_S) == GLFW_PRESS;
		input.d = glfwGetKey(engineWindow, GLFW_KEY_D) == GLFW_PRESS;
		input.space = glfwGetKey(engineWindow, GLFW_KEY_SPACE) == GLFW_PRESS;
		input.escape = glfwGetKey(engineWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS;
		input.shift = glfwGetKey(engineWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS 
			|| glfwGetKey(engineWindow, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
		input.ctrl = glfwGetKey(engineWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS
			|| glfwGetKey(engineWindow, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS;
}

void mousePosCallback(GLFWwindow* engineWindow, double xpos, double ypos){
	input.mXpos = xpos;
	input.mYpos = ypos;
}

void mouseLeftButton(int action){
	input.mLeftPress = !input.mLeftHold && action == GLFW_PRESS;

	input.mLeftHold = action == GLFW_PRESS;
	input.mLeftRelease = action == GLFW_RELEASE;
}
void mouseRightButton(int action){
	input.mRightPress = !input.mRightHold;

	input.mRightHold = action == GLFW_PRESS;
	input.mRightRelease = action == GLFW_RELEASE;
}

void mouseButtonCallback(GLFWwindow* engineWindow, int button, int action, int mods){
	if (button == GLFW_MOUSE_BUTTON_LEFT) mouseLeftButton(action);
	if (button == GLFW_MOUSE_BUTTON_RIGHT) mouseRightButton(action);
}

#endif
