#pragma once
#include <SFML/Graphics.hpp>

class cVertex3f {
private:
	sf::Vector3f m_position;
	sf::Color m_color;

public:
	cVertex3f();
	cVertex3f( sf::Vector3f _position );
	~cVertex3f();

	void rotateX( float _angle );
	void rotateY( float _angle );
	void rotateZ( float _angle );
	void move( sf::Vector3f _vector );
	const sf::Vector3f& getPosition() { return m_position; }
};