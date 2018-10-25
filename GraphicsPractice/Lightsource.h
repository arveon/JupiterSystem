#pragma once

#include "Shader.h"
#include "Sphere.h"

#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Lightsource
{
private:
	Sphere sphere = NULL;

	glm::vec4 light_position;
public:
	void draw();

	void set_view_matrix(glm::mat4);
	void set_model_matrix(glm::mat4);

	void move_to(glm::vec4);
	void shift(glm::vec3);

	glm::vec4 get_position() { return light_position; }

	Lightsource(Shader light_shader);
	Lightsource() {}
	~Lightsource();
};

