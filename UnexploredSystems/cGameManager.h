#pragma once
#include "cGraphicsManager.h"

class cGameManager {
private:
	sf::Window* m_window;
	cGraphicsManager m_graphicsManager;

	bool m_running = true;

	void update();
	void draw();

public:
	cGameManager();
	~cGameManager();

	// void registerMesh( cMesh _mesh, std::string _name ) { m_meshes[ _name ] = _mesh; }
	void createWindow();
	void run();
};