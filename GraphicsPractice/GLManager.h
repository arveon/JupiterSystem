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
#include "Sphere.h"
#include "Lightsource.h"
#include "Planet.h"

#include "Camera.h"

class GLManager
{
private:
	GLFWwindow * win;

	EventManager events;
	Shader basic_shader = NULL;
	Shader lightsource_shader = NULL;
	
	std::vector<Planet*> bodies;
	
	Lightsource sun;

	static glm::vec2 cursor_movement;
	static Camera camera;
	static GLfloat aspect_ratio;
	static glm::vec3 light_movement;
	static GLuint colour_mode;
	static GLuint sphere_drawmode;
	static GLshort delta_time;

	static bool reset;
	static bool show_cursor;
	static bool close;

	void reset_scene();
public:
	GLManager();
	~GLManager();

	void init();
	void loop();
	void render(float delta_time);
	void terminate();

	static void resize_callback(GLFWwindow* window, int width, int height);
	static void error_callback(int error, const char* desc);
	static void key_callback(GLFWwindow* window, int key_code, int scancode, int action, int mods);
	static void cursor_moved_callback(GLFWwindow* window, double xpos, double ypos);

	void init_objects();
};

