#include "Shader.h"

void Shader::init_shader(GLfloat aspect_ratio)
{
	glUseProgram(program);

	//model
	model_uniform_id = glGetUniformLocation(program, "model");
	//set initial matrix value to identity matrix
	glm::mat4 model = glm::mat4(1.f);
	glUniformMatrix4fv(model_uniform_id, 1, GL_FALSE, &model[0][0]);

	//view
	view_uniform_id = glGetUniformLocation(program, "view");
	glm::mat4 view = glm::lookAt(
		glm::vec3(0, 0, 0.5f),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
	glUniformMatrix4fv(view_uniform_id, 1, GL_FALSE, &view[0][0]);

	//projection
	projection_uniform_id = glGetUniformLocation(program, "projection");
	//set initial matrix value to identity matrix
	glm::mat4 projection = glm::perspective(glm::radians(60.f), aspect_ratio, 0.1f, 100.f);
	glUniformMatrix4fv(projection_uniform_id, 1, GL_FALSE, &projection[0][0]);

	//allocate color_mode int and set it to 0
	color_mode_id = glGetUniformLocation(program, "colour_mode");
	GLuint mode = 1;
	glUniform1ui(color_mode_id, mode);

	glUseProgram(0);
}

void Shader::set_view_matrix(glm::mat4 view)
{
	glUseProgram(program);
	glUniformMatrix4fv(view_uniform_id, 1, GL_FALSE, &view[0][0]);
	glUseProgram(0);
}

void Shader::set_model_matrix(glm::mat4 model)
{
	glUseProgram(program);
	glUniformMatrix4fv(model_uniform_id, 1, GL_FALSE, &model[0][0]);
	glUseProgram(0);
}

void Shader::set_color_mode(GLuint mode)
{
	glUseProgram(program);
	glUniform1ui(color_mode_id, mode);
	glUseProgram(0);
}

Shader::Shader(GLuint program_id)
{
	this->program = program_id;
}

Shader::~Shader()
{
}
