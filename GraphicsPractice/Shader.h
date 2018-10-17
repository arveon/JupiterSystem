#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
private:
	GLuint program;

	GLuint model_uniform_id;
	GLuint view_uniform_id;
	GLuint projection_uniform_id;

	GLuint color_mode_id;
public:

	GLuint get_program_id() { return program; };

	void init_shader(GLfloat aspect_ratio);
	void set_view_matrix(glm::mat4);
	void set_model_matrix(glm::mat4);
	void set_color_mode(GLuint);


	Shader(GLuint program_id);
	~Shader();
};

