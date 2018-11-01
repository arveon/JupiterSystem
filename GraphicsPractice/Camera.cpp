#include "Camera.h"



void Camera::update(float dt, glm::vec2 cursor_deltas)
{
	rotation.y += cursor_deltas.x / 50;
	rotation.x += cursor_deltas.y / 50;
	if (rotation.x > 90)
		rotation.x = 90;
	else if (rotation.x < -90)
		rotation.x = 0;

	//calculate strafe and forward movement of the eye vector (new position)
	glm::vec3 forward(view_matrix[0][2], view_matrix[1][2], view_matrix[2][2]);
	glm::vec3 strafe(view_matrix[0][0], view_matrix[1][0], view_matrix[2][0]);
	movement += (direction.z * forward + direction.x * strafe) * CAMERA_MOVEMENT_SPEED * dt;

	if (direction.y > 0)
		movement.y += CAMERA_MOVEMENT_SPEED * dt;
	else if (direction.y < 0)
		movement.y -= CAMERA_MOVEMENT_SPEED * dt;
	
	glm::mat4 yaw = glm::mat4(1.f);//"horizontal"
	glm::mat4 pitch = glm::mat4(1.f);//""updown"
	glm::mat4 rotation_mat;

	yaw = glm::rotate(yaw, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	pitch = glm::rotate(pitch, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	rotation_mat = pitch * yaw;

	glm::mat4 translate = glm::mat4(1.0f);
	translate = glm::translate(translate, glm::vec3(movement.x, movement.y, movement.z));
	view_matrix = rotation_mat * translate;
}

void Camera::reset()
{
	movement = glm::vec3(0);
	rotation = glm::vec3(0);
	movement.z = -20;
	view_matrix = glm::lookAt(
		glm::vec3(0, 0, -20),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);

}

Camera::Camera()
{
	movement = glm::vec3(0);
	rotation = glm::vec3(0);
	movement.z = -20;
	view_matrix = glm::lookAt(
		glm::vec3(0, 0, -20),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0)
	);
}


Camera::~Camera()
{
}
