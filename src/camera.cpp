#include "camera.h"
#include "key_code.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera() {
	UpdateVectors();
}

void Camera::ProcessKeyboard(KeyCode key, float delta) {
	float velocity = speed * delta;
	switch (key) {
	case KeyCode::W: position += front * velocity; break;
	case KeyCode::S: position -= front * velocity; break;
	case KeyCode::D: position += right * velocity; break;
	case KeyCode::A: position -= right * velocity; break;
	}
}


void Camera::ProcessMouseMovements(float xoffset, float yoffset, bool constraintPitch=true) {
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch+= yoffset;


	if (constraintPitch) {
		if (pitch > 89.0f)
			pitch = 89.0f;		
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	UpdateVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	fov -= yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 90.0f)
		fov = 90.0f;
}

void Camera::UpdateVectors() {
	//Get new Front vector to handling camera rotations
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(direction);

	//Get new Right, Up vectors from cross products
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(position, position+front, up);
}