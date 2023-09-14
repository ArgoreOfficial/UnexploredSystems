#pragma once
#include <SFML/Graphics.hpp>
#include <gtc/matrix_transform.hpp>

class cCamera {
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	float m_aspect;
	float m_fov;

public:
	cCamera();
	cCamera( sf::Window& _window, float _fov = 60.0f );

	glm::mat4 getProjectionMatrix() {
		return glm::perspective( glm::radians( m_fov ), m_aspect, 0.1f, 100.0f );
	}
	glm::vec3 getPosition() { return m_position; }
	glm::vec3 getRotation() { return m_rotation; }

	void move( glm::vec3 _direction );
	void rotate( glm::vec3 _angle ) 
	{ 
		m_rotation += _angle; 
	}
};