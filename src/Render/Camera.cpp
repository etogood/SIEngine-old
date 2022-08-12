//
// Created by etogood on 14.04.2022.
//

#include "Camera.h"
#include "glm/ext/matrix_transform.hpp"

namespace Render {
	Camera::Camera(float yaw, float pitch, glm::vec3 position, glm::vec3 up) : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
																			   MovementSpeed(SPEED),
																			   MouseSensitivity(SENSITIVITY),
																			   Zoom(ZOOM) {
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
        update_camera_vectors();
	}

	Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(
			glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
		Pitch = pitch;
        update_camera_vectors();
	}

	Camera::Camera(float posX, float posY, float posZ, glm::vec3 up, float yaw, float pitch) : Front(
			glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
        update_camera_vectors();
	}

	Camera::Camera(glm::vec3 position, float upX, float upY, float upZ, float yaw, float pitch) : Front(
			glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
        Position = position;
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
		Pitch = pitch;
        update_camera_vectors();
	}

    glm::mat4 Camera::get_view_matrix() const {
        return glm::lookAt(Position, Position + Front, Up);
    }

	void Camera::process_keyboard(CameraMovement direction, float deltaTime) {
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position += Front * velocity;
		if (direction == BACKWARD)
			Position -= Front * velocity;
		if (direction == LEFT)
			Position -= Right * velocity;
		if (direction == RIGHT)
			Position += Right * velocity;
	}

    void Camera::process_mouse_movement(float xoffset, float yoffset, bool constrainPitch) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        if (constrainPitch) {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
				Pitch = -89.0f;
		}
        update_camera_vectors();
	}

	void Camera::process_mouse_scroll(float yoffset) {
		Zoom -= (float) yoffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}

	void Camera::update_camera_vectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}


}
