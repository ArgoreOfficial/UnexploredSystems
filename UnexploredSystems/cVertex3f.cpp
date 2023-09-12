#include "cVertex3f.h"

cVertex3f::cVertex3f()
{
	m_position = sf::Vector3f( 0.0f, 0.0f, 0.0f );
}

cVertex3f::cVertex3f( sf::Vector3f _position )
{
	m_position = _position;
}

cVertex3f::~cVertex3f()
{

}

void cVertex3f::rotateX( float _angle )
{
	m_position.x = m_position.x * cos( _angle ) - m_position.y * sin( _angle );
	m_position.y = m_position.x * sin( _angle ) + m_position.y * cos( _angle );
 // m_position.z = m_position.z
}

void cVertex3f::rotateY( float _angle )
{
	m_position.x = m_position.x * sin( _angle ) + m_position.z * sin( _angle );
 // m_position.y = m_position.y
	m_position.z = -m_position.x * sin( _angle ) + m_position.z * cos( _angle );
}

void cVertex3f::rotateZ( float _angle )
{
 // m_position.x = m_position.x
	m_position.y = m_position.y * cos( _angle ) - m_position.z * sin( _angle );
	m_position.z = m_position.y * sin( _angle ) + m_position.z * cos( _angle );
}

void cVertex3f::move( sf::Vector3f _vector )
{
	m_position += _vector;
}
