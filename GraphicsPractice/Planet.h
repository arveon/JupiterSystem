#pragma once
#include "Sphere.h"
class Planet
{
private:
	float rotation_speed = 1;
	float scale;
	float cur_angle;

	Sphere* sphere;
	Planet* parent = nullptr;
	float dist_from_parent;
public:
	Planet();
	Planet(float rotation_speed, float scale, float starting_angle, Sphere* sphere, Planet* parent = nullptr, float dist_from_parent = 1);
	~Planet();

	void draw(glm::mat4 view_matrix, float delta_time, int sphere_drawmode = 1);

	glm::vec3 get_center_position() { return sphere->get_center_position(); }
	float get_scale();

	Sphere* get_sphere() { return sphere; }
};

