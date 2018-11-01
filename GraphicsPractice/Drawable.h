#pragma once
#include <vector>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderManager.h"
#include "Constants.h"

class Drawable
{
protected:
	GLuint buffer_id;
	GLuint normal_buffer;
	GLuint model_uniform_id;
	GLuint tex_coords_buffer;

	GLuint texture_id;

	Shader shader_program = NULL;

	float *verts = nullptr;
	float *normals = nullptr;
	float *texture_coords = nullptr;
	
	
	int num_verts;

	glm::mat4 model_matrix;
	glm::mat4 view_matrix;

	glm::vec3 center_position = glm::vec4(0);

	void load_into_memory();
public:
	Drawable() {};
	~Drawable();
	
	bool tex_enabled;
	void init(Shader shader_program, float* vertices, int num_verts, float* normals = nullptr, float* texcoords = nullptr);
	
	void draw();
	void set_model_matrix(glm::mat4 model_matrix);
	void set_view_matrix(glm::mat4 view_matrix);

	glm::mat4 get_model_matrix() { return model_matrix; }
	glm::vec3 get_center_position() { return center_position; }

	void translate(glm::vec3 direction);
	void rotate(float radians, glm::vec3 axis);
	void scale(glm::vec3 direction);
};

