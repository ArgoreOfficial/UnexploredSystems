#pragma once
#include "cVertex3f.h"
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

class cMesh {

private:
	std::vector<cVertex3f> m_vertices;
	std::vector<std::vector<int>> m_faces;
	sf::Vector3f m_position;
	sf::Vector3f m_rotation;
	sf::Vector3f m_scale;
public:
	cMesh();
	cMesh( sf::Vector3f _position, sf::Vector3f _rotation );
	~cMesh();
	void loadFromFile( std::string _path );

	void addVert( cVertex3f _vert ) { m_vertices.push_back( _vert ); }
	void rotate( sf::Vector3f _angle ) { m_rotation += _angle; }
	void scale( sf::Vector3f _delta ) { m_scale += _delta; }
	void move( sf::Vector3f _direction ) { m_position += _direction; }

	void setRotation( sf::Vector3f _rotation ) { m_rotation = _rotation; }
	void setScale( sf::Vector3f _scale ) { m_scale = _scale; }
	void setPosition( sf::Vector3f _position ) { m_position = _position; }

	void draw( sf::RenderWindow& _window );
};