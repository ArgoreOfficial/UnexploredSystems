#include "cGraphicsManager.h"

cGraphicsManager::cGraphicsManager() 
{

}

cGraphicsManager::~cGraphicsManager()
{
	
}

void cGraphicsManager::update(float _dt)
{

	for ( int i = 0; i < m_meshes.size(); i++ )
	{
		m_meshes[ i ].rotate( sf::Vector3f( 0, 45.0f * _dt, 0 ) );
	}
}


void cGraphicsManager::initShaders()
{
	unsigned int v_default = loadVertexShader( "assets/shaders/default.vert" );
	unsigned int f_default = loadFragmentShader( "assets/shaders/default.frag" );
	loadShaderProgram( "default", v_default, f_default);

	unsigned int f_translucent = loadFragmentShader( "assets/shaders/translucent.frag" );
	loadShaderProgram( "translucent", v_default, f_translucent );

	unsigned int f_white = loadFragmentShader( "assets/shaders/white.frag" );
	loadShaderProgram( "white", v_default, f_white );


	// delete shaders, we don't need them anymore
	glDeleteShader( v_default );
	glDeleteShader( f_default );
	glDeleteShader( f_translucent );
	glDeleteShader( f_white );
}


void cGraphicsManager::draw()
{
	glClearColor( 0.392f, 0.584f, 0.929f, 1.0f ); // cornflower blue
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


	for ( int i = 0; i < m_meshes.size(); i++ )
	{
		
		// set transforms
		glm::mat4 trans = glm::mat4( 1.0f );
		sf::Vector3f mesh_rot = m_meshes[ i ].getRotation();
		trans = glm::rotate( trans, glm::radians( mesh_rot.x ), glm::vec3(1.0, 0.0, 0.0));
		trans = glm::rotate( trans, glm::radians( mesh_rot.y ), glm::vec3( 0.0, 1.0, 0.0 ) );
		trans = glm::rotate( trans, glm::radians( mesh_rot.z ), glm::vec3( 0.0, 0.0, 1.0 ) );

		trans = glm::scale( trans, glm::vec3( 1.0, 1.0, 1.0 ) );
		
		glUniformMatrix4fv( glGetUniformLocation( m_shaderPrograms[ "default" ], "transform" ), 1, GL_FALSE, glm::value_ptr( trans ) );
		glUniformMatrix4fv( glGetUniformLocation( m_shaderPrograms[ "white" ], "transform" ), 1, GL_FALSE, glm::value_ptr( trans ) );

		glBindVertexArray( m_meshes[ i ].getVertexArrayObject() );
		
		glUseProgram( m_shaderPrograms[ "white" ] );
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		glDrawElements( GL_TRIANGLES, m_meshes[ i ].getFaceIndicesBufferSize(), GL_UNSIGNED_INT, 0 );

		glUseProgram( m_shaderPrograms["default"]);
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		glDrawElements( GL_TRIANGLES, m_meshes[ i ].getFaceIndicesBufferSize(), GL_UNSIGNED_INT, 0 );
		
		
	}
}

void cGraphicsManager::initGL( sf::Window* _window )
{
	glViewport( 0, 0, _window->getSize().x, _window->getSize().y );
	glewExperimental = GL_TRUE;
	glewInit();
	
	glEnable( GL_TEXTURE_2D );
	
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
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

unsigned int cGraphicsManager::loadVertexShader( const std::string& _path )
{
	std::ifstream file_in = loadFileToStream( _path );
	std::string filestring;

	std::string line;
	while ( std::getline( file_in, line ) ) { filestring += line + "\n"; }
	line += "\0";

	const char* vertexShaderSource = filestring.c_str();

	unsigned int vertexShader;
	vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
	glCompileShader( vertexShader );

	return vertexShader;
}

unsigned int cGraphicsManager::loadFragmentShader( const std::string& _path )
{
	std::ifstream file_in = loadFileToStream( _path );
	std::string filestring;

	std::string line;
	while ( std::getline( file_in, line ) ) { filestring += line + "\n"; }
	line += "\0";

	const char* fragShaderSource = filestring.c_str();
	
	unsigned int fragmentShader;
	fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragShaderSource, NULL );
	glCompileShader( fragmentShader );

	return fragmentShader;
}

void cGraphicsManager::loadShaderProgram( std::string _name, unsigned int _vert, unsigned int _frag )
{
	// create and link shader program, basically combine the vert
	// and frag shader into a single shader program that can then be used by the gpu
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader( shaderProgram, _vert );
	glAttachShader( shaderProgram, _frag );
	glLinkProgram( shaderProgram );

	m_shaderPrograms[ _name ] = shaderProgram;
}


std::ifstream cGraphicsManager::loadFileToStream( const std::string& _path )
{
	// get current working directory
	char buffer[ MAX_PATH ];
	GetModuleFileNameA( NULL, buffer, MAX_PATH );
	std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" );
	std::string current_dir = std::string( buffer ).substr( 0, pos );

	// load file into vector of strings
	std::vector<std::string> string_vec;
	std::ifstream file_in( current_dir + "/" + _path );
	
	return file_in;
}
