#include "cCamera.h"

cCamera::cCamera()
{
}

cCamera::cCamera( sf::Window& _window, float _fov )
{
	m_aspect = ( float )_window.getSize().x / ( float )_window.getSize().x;
	m_position = glm::vec3( 0.0f, 0.0f, 2.0f );
	m_rotation = glm::vec3( 0.0f, 0.0f, 0.0f );

	m_fov = _fov;
}

void cCamera::move( glm::vec3 _direction )
{
	glm::mat4 mat = glm::mat4( 1.0f );
	mat = glm::rotate( mat, glm::radians( m_rotation.x ), glm::vec3( 1.0, 0.0, 0.0 ) );
	mat = glm::rotate( mat, glm::radians( m_rotation.y ), glm::vec3( 0.0, 1.0, 0.0 ) );
	mat = glm::rotate( mat, glm::radians( m_rotation.z ), glm::vec3( 0.0, 0.0, 1.0 ) );

	m_position += glm::vec3(glm::vec4(_direction, 0) * mat); 
}
