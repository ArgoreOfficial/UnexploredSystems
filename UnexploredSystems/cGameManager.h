#pragma once
#include "cMesh.h"

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

class cGameManager {
private:
	sf::Window* m_window;
	std::map<std::string, cMesh> m_meshes;
	bool m_running;

	void update();
	void draw();

public:
	cGameManager();
	~cGameManager();

	void registerMesh( cMesh _mesh, std::string _name ) { m_meshes[ _name ] = _mesh; }
	void createWindow();
	void run();
};