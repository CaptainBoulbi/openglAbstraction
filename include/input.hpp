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
	bool escp;
}input;

void clearInput(){
	input = {0, 0, 0, 0, 0, 0, 0, 0};
}

void processInput(){
	clearInput();

	if(glfwGetKey(engineWindow, GLFW_KEY_W) == GLFW_PRESS)
		input.w = true;
	if(glfwGetKey(engineWindow, GLFW_KEY_A) == GLFW_PRESS)
		input.a = true;
	if(glfwGetKey(engineWindow, GLFW_KEY_S) == GLFW_PRESS)
		input.s = true;
	if(glfwGetKey(engineWindow, GLFW_KEY_D) == GLFW_PRESS)
		input.d = true;
	if(glfwGetKey(engineWindow, GLFW_KEY_SPACE) == GLFW_PRESS)
		input.space = true;
	if(glfwGetKey(engineWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS
			|| glfwGetKey(engineWindow, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
		input.shift = true;
	if(glfwGetKey(engineWindow, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS
			|| glfwGetKey(engineWindow, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
		input.ctrl = true;
	if(glfwGetKey(engineWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		input.escp = true;
}

#endif
