#pragma once
#include <SFML/Graphics.hpp>
#include <gtc/matrix_transform.hpp>

class cCamera {
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	float m_aspect;

public:
	cCamera();
	cCamera( sf::Window& _window );

	glm::mat4 getProjectionMatrix() {
		return glm::perspective( glm::radians( 45.0f ), m_aspect, 0.1f, 100.0f );
	}
	glm::vec3 getPosition() { return m_position; }
	glm::vec3 getRotation() { return m_rotation; }

	void move( glm::vec3 _direction ) { m_position += _direction; }
	void rotate( glm::vec3 _angle ) { m_rotation += _angle; }
};