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
		"layout (location = 0) in vec3 pos;\n"
		"out vec3 fpos;"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
		"	fpos = pos;\n"
		"}\0";

	unsigned int vertexShader;
	vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
	glCompileShader( vertexShader );

	const char* fragShaderSource =
		"#version 330 core\n"
		"in vec3 fpos;\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	float c = (fpos.z + 1.0f) / 2.0f;\n"
		"	FragColor = vec4( c, c, c, 1.0f );\n"
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

	
	for ( int i = 0; i < m_meshes.size(); i++ )
	{
		glBindVertexArray( m_meshes[ i ].getVertexArrayObject() );
		glEnableVertexAttribArray( 0 );
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), ( void* )0 );

		glDrawElements( GL_TRIANGLES, m_meshes[ i ].getFaceIndicesBufferSize(), GL_UNSIGNED_INT, 0 );
		// glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // draw as wireframe
		// glDrawElements( GL_TRIANGLES, m_meshes[ i ].getFaceIndicesBufferSize(), GL_UNSIGNED_INT, 0 );
	}
}

void cGraphicsManager::initGL( sf::Window* window )
{
	glEnable( GL_TEXTURE_2D );
	glViewport( 0, 0, window->getSize().x, window->getSize().y );
	glewExperimental = GL_TRUE;
	glewInit();

	glEnable( GL_CULL_FACE );
	glEnable( GL_DEPTH_TEST );
	glDepthMask( GL_TRUE );
	glDepthFunc( GL_LEQUAL );
	glDepthRange( 1.0f, 0.0f );

	initShaders();
}

void cGraphicsManager::loadMesh( const std::string& _path )
{
	cMesh mesh;
	mesh.loadFromFile( _path );
	m_meshes.push_back( mesh );
}