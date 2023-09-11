#pragma once
#include <SFML/Graphics.hpp>

struct sVertex3f {
	sf::Vector3f m_position;
	sf::Color m_color;
};

class cMesh {

private:
	std::vector<sVertex3f> m_vertexArray;


public:
	cMesh();
	~cMesh();

	void AddVertex( sVertex3f _vert );
};