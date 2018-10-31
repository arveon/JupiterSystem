#include "Camera.h"



void Camera::update(float dt, glm::vec2 cursor_deltas)
{
	if (direction.x > 0)
		movement.x += (dt*CAMERA_MOVEMENT_SPEED);
	else if (direction.x < 0)
		movement.x -= (dt*CAMERA_MOVEMENT_SPEED);

	if (direction.y > 0)
		movement.y += (dt*CAMERA_MOVEMENT_SPEED);
	else if (direction.y < 0)
		movement.y -= (dt*CAMERA_MOVEMENT_SPEED);

	if (direction.z > 0)
		movement.z += (dt*CAMERA_MOVEMENT_SPEED);
	else if (direction.z < 0)
		movement.z -= (dt*CAMERA_MOVEMENT_SPEED);

	rotation.y += cursor_deltas.x / 100;
	rotation.x += cursor_deltas.y / 100;
	std::cerr << rotation.y << std::endl;

	//move camera
	view_matrix = glm::lookAt(
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, -4),
		glm::vec3(0, 1, 0)
	);

	view_matrix = glm::rotate(view_matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	view_matrix = glm::rotate(view_matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	view_matrix = glm::rotate(view_matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	view_matrix = glm::translate(view_matrix, glm::vec3(movement.x, movement.y, movement.z - 20));
}

Camera::Camera()
{
}


Camera::~Camera()
{
}
