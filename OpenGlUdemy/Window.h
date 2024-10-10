#pragma once

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidht, GLint windowHeight);

	int Initialize();

	GLfloat getBufferWidth() { return bufferWidht; }
	GLfloat GetBuferrHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	bool* getKesy() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }


	~Window();
private:

	GLFWwindow* mainWindow;
	GLint width, height;
	GLint bufferWidht, bufferHeight;


	bool keys[1024];
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange = 0;
	GLfloat yChange = 0;
	bool mouseFirtMoved;

	
	void createCallbacks();

	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window,double xPos, double yPos);
};

