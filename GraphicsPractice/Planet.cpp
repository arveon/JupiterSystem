#include "Planet.h"



Planet::Planet()
{
}


Planet::Planet(float rotation_speed, float scale, float starting_angle, Sphere* sphere, 
	Planet* parent, float dist_from_parent)
{
	this->rotation_speed = rotation_speed;
	this->scale = scale;
	this->cur_angle = starting_angle;
	this->sphere = sphere;
	this->parent = parent;
	this->dist_from_parent = dist_from_parent;
	//sphere.makeSphere(NUM_LATS_SPHERE, NUM_LONGS_SPHERE);
}

Planet::~Planet()
{
	delete sphere;
}

void Planet::draw(glm::mat4 view_matrix, float delta_time, int sphere_drawmode)
{
	sphere->set_view_matrix(view_matrix);

	float speed = (rotation_speed*delta_time);
	cur_angle = (cur_angle >= 360) ? 0 : cur_angle + speed;

	float px = glm::cos(glm::radians(cur_angle))*dist_from_parent;
	float py = glm::sin(glm::radians(cur_angle))*dist_from_parent;

	if (parent != nullptr)
	{
		glm::vec3 origin = parent->get_center_position();
		float parent_scale = parent->get_scale();

		px += origin.x * parent_scale / scale;
		py += origin.y * parent_scale / scale;
	}

	sphere->scale(glm::vec3(scale, scale, scale));
	sphere->translate(glm::vec3(px, py, 0));

	sphere->drawSphere(sphere_drawmode);
}

float Planet::get_scale()
{
	float res = scale;
	if (parent != nullptr && parent != this)
		res *= parent->get_scale();

	return res;
}
