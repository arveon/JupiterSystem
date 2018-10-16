#pragma once
#define GLEW_STATIC

#pragma comment(lib, "glfw3D.lib")
#pragma comment(lib, "glew32sd.lib")
#pragma comment(lib, "opengl32.lib")

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stack>

#include "EventManager.h"
#include "ShaderManager.h"

#include "Triangle.h"
#include "Square.h"
#include "Cube.h"

class GLManager
{
private:
	GLFWwindow * win;

	EventManager events;
	ShaderManager shader;

	Drawable triangle;
	Drawable square;
	Drawable cube;
public:
	GLManager();
	~GLManager();

	void init();
	void loop();
	void render();
	void terminate();

	static void resize_callback(GLFWwindow* window, int width, int height);
	static void error_callback(int error, const char* desc);
	static void key_callback(GLFWwindow* window, int key_code, int scancode, int action, int mods);

	void init_objects();
};

