#include "cCamera.h"

cCamera::cCamera()
{
}

cCamera::cCamera( sf::Window& _window )
{
	m_aspect = ( float )_window.getSize().x / ( float )_window.getSize().x;
	m_position = glm::vec3( 0.0f, 0.0f, 2.0f );
	m_rotation = glm::vec3( 0.0f, 0.0f, 0.0f );
}
