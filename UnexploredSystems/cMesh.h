#pragma once
#include <SFML/Graphics.hpp>
#include "cVertex3f.h"

class cMesh {

private:
	std::vector<cVertex3f> m_vertexArray;


public:
	cMesh();
	~cMesh();

	void addVert( cVertex3f _vert );
	void draw( sf::RenderWindow& window );
};