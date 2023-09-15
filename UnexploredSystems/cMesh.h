#pragma once

#include <glm.hpp>
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

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
public:
	cMesh();
	cMesh( glm::vec3 _position, glm::vec3 _rotation );
	~cMesh();
	void loadFromFile( const std::string& _path );
	void setupBuffers();

	float* getVertexBuffer() { return &m_vertices[ 0 ]; }
	unsigned int* getFaceIndicesBuffer() { return &m_face_indices[ 0 ]; }

	unsigned int getVertexArrayObject() { return m_vertexArrayObject; }
	unsigned int getVertexBufferObject() { return m_vertexBufferObject; }
	unsigned int getElementBufferObject() { return m_elementBufferObject; }
	unsigned int getFaceIndicesBufferSize() { return m_faceIndicesBufferSize; }

	void rotate( glm::vec3 _angle ) { m_rotation += _angle; }
	void scale( glm::vec3 _delta ) { m_scale += _delta; }
	void move( glm::vec3 _direction ) { m_position += _direction; }

	void setRotation( glm::vec3 _rotation ) { m_rotation = _rotation; }
	void setScale( glm::vec3 _scale ) { m_scale = _scale; }
	void setPosition( glm::vec3 _position ) { m_position = _position; }

	glm::vec3 getRotation() { return m_rotation; }
	glm::vec3 getPosition() { return m_position; }
	glm::vec3 getScale() { return m_scale; }
};