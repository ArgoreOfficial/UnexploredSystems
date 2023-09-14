#pragma once
#include "cMesh.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class cGraphicsManager {
private:
	std::vector<cMesh> m_meshes;
	std::map<std::string, unsigned int> m_shaderPrograms;

	void initShaders();

public:
	cGraphicsManager();
	~cGraphicsManager();
	void update( float _dt );
	void draw();
	void initGL( sf::Window* _window );
	void loadMesh( const std::string& _path );
	unsigned int loadVertexShader( const std::string& _path );
	unsigned int loadFragmentShader( const std::string& _path );
	void loadShaderProgram( std::string _name, unsigned int _vert, unsigned int _frag );
	
	std::ifstream loadFileToStream( const std::string& _path );
};