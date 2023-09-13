#include "cGraphicsManager.h"

cGraphicsManager::cGraphicsManager() 
{

}

cGraphicsManager::~cGraphicsManager()
{
	
}


void cGraphicsManager::initShaders()
{
	// create vert and frag shaders

	const char* vertexShaderSource = 
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	unsigned int vertexShader;
	vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
	glCompileShader( vertexShader );

	const char* fragShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4( 1.0f, 0.5f, 0.2f, 1.0f );\n"
		"}\0";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragShaderSource, NULL );
	glCompileShader( fragmentShader );


	// create and link shader program, basically combine the vert
	// and frag shader into a single shader program that can then be used by the gpu
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader( shaderProgram, vertexShader );
	glAttachShader( shaderProgram, fragmentShader );
	glLinkProgram( shaderProgram );

	// every draw call after this will use this shader program
	glUseProgram( shaderProgram );

	// delete shaders, we don't need them anymore
	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );
}


void cGraphicsManager::draw()
{
	glClearColor( 0.392f, 0.584f, 0.929f, 1.0f ); // cornflower blue
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // draw as wireframe

	for ( int i = 0; i < m_meshes.size(); i++ )
	{
		glBindVertexArray( m_meshes[ i ].getVertexArrayObject() );
		glDrawElements( GL_TRIANGLES, m_meshes[ i ].getFaceIndicesBufferSize(), GL_UNSIGNED_INT, 0 );
	}
}

void cGraphicsManager::initGL( sf::Window* window )
{
	glEnable( GL_TEXTURE_2D );
	glViewport( 0, 0, window->getSize().x, window->getSize().y );
	glewExperimental = GL_TRUE;
	glewInit();

	initShaders();
}

void cGraphicsManager::loadMesh( const std::string& _path )
{
	cMesh mesh;
	mesh.loadFromFile( _path );
	m_meshes.push_back( mesh );
}