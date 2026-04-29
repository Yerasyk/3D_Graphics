#pragma once

#include <glm/glm.hpp>

enum class KeyCode;

class Camera
{
public:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float yaw=-90.0f;
	float pitch=0.0f;

	float speed=2.5f;
	float mouseSensitivity=0.1f;
	float fov=45.0f;

	Camera();
	
	void ProcessMouseMovements(float xoffset, float yoffset, bool constraintPitch);
	void ProcessMouseScroll(float yoffset);
	void ProcessKeyboard(KeyCode key, float delta);
	void UpdateVectors();

	glm::mat4 GetViewMatrix();
};