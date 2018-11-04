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
	this->y_rot_speed = (rand() %5 + 5);//generate a random speed "up and down"
	this->cur_y_angle = 0;
}

Planet::~Planet()
{
	delete sphere;
}

void Planet::draw(glm::mat4 view_matrix, float delta_time, int sphere_drawmode)
{
	sphere->set_view_matrix(view_matrix);

	//calculate the current angle for cos/sin calculations and rotation around itself
	float speed = (rotation_speed*delta_time);
	cur_angle = (cur_angle >= 360) ? 0 : cur_angle + speed;
	cur_y_angle = (cur_y_angle >= 360) ? 0 : cur_y_angle + speed/2;

	//calculate the new planet positions on each of the axis
	float px = glm::cos(glm::radians(cur_angle))*dist_from_parent;
	float pz = glm::sin(glm::radians(cur_angle))*dist_from_parent;
	float py = (glm::sin(glm::radians(cur_angle))*dist_from_parent) / y_rot_speed;//divided by y_rot_speed as it shouldn't be moving along the Y axis as much as along the other ones

	if (parent != nullptr)
	{//make sure that the center of orbit is at the parent planet's center
		glm::vec3 origin = parent->get_center_position();
		float parent_scale = parent->get_scale();

		//add the coordinates of parent (accounting for both parent's and own scale)
		px += origin.x * parent_scale / scale;
		pz += origin.z * parent_scale / scale;
		py += origin.y * parent_scale / scale;
	}

	//manipulate the sphere
	sphere->scale(glm::vec3(scale, scale, scale));
	sphere->translate(glm::vec3(px, py, pz));
	sphere->rotate(glm::radians(cur_y_angle), glm::vec3(0, 1, 0));
	sphere->rotate(glm::radians(90.f), glm::vec3(1, 0, 0));//initially all spheres are tilted at 90 degree angle (poles are along horizontal plane), so need to tilt them to have poles along Y axis

	sphere->drawSphere(sphere_drawmode);
}

float Planet::get_scale()
{
	float res = scale;
	return res;
}
