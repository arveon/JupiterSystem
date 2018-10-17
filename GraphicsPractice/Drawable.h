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
	GLuint model_uniform_id;

	Shader shader_program = NULL;

	float *verts = NULL;
	int num_verts;

	void load_into_memory();
public:
	Drawable() {};
	~Drawable();
	
	void init(Shader shader_program, float* vertices, int num_verts);

	
	void draw();
	void set_model_matrix(glm::mat4 model_matrix);
	void set_view_matrix(glm::mat4 view_matrix);
};

