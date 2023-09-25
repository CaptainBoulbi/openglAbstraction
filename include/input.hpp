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

bool GLFWMouseLeftPress = false;
bool GLFWMouseRightPress = false;

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

	input.mLeftPress = !input.mLeftPress && !input.mLeftHold && GLFWMouseLeftPress;
	input.mRightPress = !input.mRightPress && !input.mRightHold && GLFWMouseRightPress;

	input.mLeftRelease = !input.mLeftRelease && input.mLeftHold && !GLFWMouseLeftPress;
	input.mRightRelease = !input.mRightRelease && input.mRightHold && !GLFWMouseRightPress;

	input.mLeftHold = GLFWMouseLeftPress;
	input.mRightHold = GLFWMouseRightPress;
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
