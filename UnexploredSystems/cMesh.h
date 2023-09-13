#pragma once

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include <Windows.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

class cMesh {

private:
	std::vector<float> m_vertices;
	std::vector<unsigned int> m_face_indices;

	unsigned int m_vertexArrayObject;
	unsigned int m_vertexBufferObject;
	unsigned int m_elementBufferObject;

	unsigned int m_vertexBufferSize;
	unsigned int m_faceIndicesBufferSize;

	sf::Vector3f m_position;
	sf::Vector3f m_rotation;
	sf::Vector3f m_scale;
public:
	cMesh();
	cMesh( sf::Vector3f _position, sf::Vector3f _rotation );
	~cMesh();
	void loadFromFile( std::string _path );
	void setupBuffers();

	float* getVertexBuffer() { return &m_vertices[ 0 ]; }
	unsigned int* getFaceIndicesBuffer() { return &m_face_indices[ 0 ]; }
	
	unsigned int getVertexArrayObject() { return m_vertexArrayObject; }
	unsigned int getVertexBufferObject() { return m_vertexBufferObject; }
	unsigned int getElementBufferObject() { return m_elementBufferObject; }
	unsigned int getFaceIndicesBufferSize() { return m_faceIndicesBufferSize; }

	void rotate( sf::Vector3f _angle ) { m_rotation += _angle; }
	void scale( sf::Vector3f _delta ) { m_scale += _delta; }
	void move( sf::Vector3f _direction ) { m_position += _direction; }

	void setRotation( sf::Vector3f _rotation ) { m_rotation = _rotation; }
	void setScale( sf::Vector3f _scale ) { m_scale = _scale; }
	void setPosition( sf::Vector3f _position ) { m_position = _position; }

	void draw( sf::RenderWindow& _window );
};