#pragma once
#include "cGraphicsManager.h"
#include "cCamera.h"

class cGameManager {
private:
	sf::Window* m_window;
	
	cGraphicsManager m_graphicsManager;
	cCamera m_camera;

	bool m_running = true;
	glm::vec2 m_mouseDelta;
	sf::Vector2i m_lastMousePos;

	void update(float _dt, float _t );
	void draw();

public:
	cGameManager();
	~cGameManager();

	// void registerMesh( cMesh _mesh, std::string _name ) { m_meshes[ _name ] = _mesh; }
	void createWindow();
	void run();
};