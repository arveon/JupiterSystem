/* by Aleksejs Loginovs - October 2018 */

#pragma once
#include "Sphere.h"

//Class that abstracts away the sphere representing the planet and control over it
class Planet
{
private:
	float rotation_speed = 1;
	float y_rot_speed;
	float scale;
	float cur_angle;
	float cur_y_angle;

	Sphere* sphere;
	Planet* parent = nullptr;
	float dist_from_parent;
public:
	Planet();
	Planet(float rotation_speed, float scale, float starting_angle, Sphere* sphere, Planet* parent = nullptr, float dist_from_parent = 1);
	~Planet();

	void draw(glm::mat4 view_matrix, float delta_time, int sphere_drawmode = 0);

	glm::vec3 get_center_position() { return sphere->get_center_position(); }
	float get_scale();

	Sphere* get_sphere() { return sphere; }
};

