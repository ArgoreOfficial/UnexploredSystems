#pragma once
#include "cMesh.h"

class cGraphicsManager {
private:
	std::vector<cMesh> m_meshes;

	void initShaders();

public:
	cGraphicsManager();
	~cGraphicsManager();
	void draw();
	void initGL( sf::Window* window );
	void loadMesh(const std::string& _path);
};