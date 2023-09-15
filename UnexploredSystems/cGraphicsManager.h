#pragma once
#include "cMesh.h"
#include "cCamera.h"
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
	void update( float _dt, float _t );
	void draw( cCamera _camera );
	void drawMesh(cMesh& _mesh, unsigned int& _shaderProgram, cCamera _camera, GLenum _mode = GL_FILL);
	void initGL( sf::Window* _window );
	unsigned int loadMesh( const std::string& _path );
	unsigned int loadVertexShader( const std::string& _path );
	unsigned int loadFragmentShader( const std::string& _path );
	void loadShaderProgram( std::string _name, unsigned int _vert, unsigned int _frag );
	void setMeshPosition( const unsigned int& _id, const glm::vec3& _newPosition );
	std::ifstream loadFileToStream( const std::string& _path );
};