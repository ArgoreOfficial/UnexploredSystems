#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class cVertex3f {
private:
	sf::Vector3f m_position;
	sf::Color m_color;

public:
	cVertex3f();
	cVertex3f( sf::Vector3f _position );
	cVertex3f( float x, float y, float z );
	~cVertex3f();

	void rotateX( float _angle );
	void rotateY( float _angle );
	void rotateZ( float _angle );
	void rotate( sf::Vector3f _rotation );
	void scale( sf::Vector3f _scale );
	void move( sf::Vector3f _direction ) { m_position += _direction; }

	void setPosition( sf::Vector3f _position ) { m_position = _position; }

	void transform( sf::Vector3f _rotation, sf::Vector3f _scale, sf::Vector3f _position );

	const sf::Vector3f& getPosition() { return m_position; }
};