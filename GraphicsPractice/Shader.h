#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Constants.h"

class Shader
{
private:
	GLuint program;

	GLuint model_view_uniform_id;
	//GLuint model_uniform_id;
	GLuint view_uniform_id;
	GLuint projection_uniform_id;

	GLuint color_mode_id;
	GLfloat shininess_uniform_id;
	GLuint light_position_uniform_id;
	GLfloat attenuation_enabled_uniform_id;
public:

	GLuint get_program_id() { return program; };

	void init_shader(GLfloat aspect_ratio, int type);
	void set_view_matrix(glm::mat4);
	/*void set_model_matrix(glm::mat4);*/
	void set_model_view_matrix(glm::mat4);
	void set_color_mode(GLuint);
	void set_light_position(glm::vec4);
	void set_shininess(GLfloat);
	void set_attenuation_enabled(GLboolean);

	Shader(GLuint program_id);
	~Shader();
};

