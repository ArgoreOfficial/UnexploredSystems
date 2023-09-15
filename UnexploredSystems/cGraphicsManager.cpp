#include "cGraphicsManager.h"

cGraphicsManager::cGraphicsManager() 
{

}

cGraphicsManager::~cGraphicsManager()
{
	
}

void cGraphicsManager::update(float _dt, float _t)
{
	for ( int i = 0; i < m_meshes.size(); i++ )
	{
		m_meshes[ i ].rotate( glm::vec3( 0, 0, 0 ) * _dt );
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


void cGraphicsManager::draw( cCamera _camera )
{
	// glClearColor( 0.392f, 0.584f, 0.929f, 1.0f ); // cornflower blue
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f ); // black
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	for ( int i = 0; i < m_meshes.size(); i++ )
	{
		// glDisable( GL_CULL_FACE );
		// drawMesh( m_meshes[ i ], m_shaderPrograms[ "white" ], _camera, GL_LINE);
		// glEnable( GL_CULL_FACE );
		drawMesh( m_meshes[ i ], m_shaderPrograms[ "default" ], _camera );
	}

}

void cGraphicsManager::drawMesh( cMesh& _mesh, unsigned int& _shaderProgram, cCamera _camera, GLenum _mode )
{
	// transform
	glm::vec3 mesh_rot = _mesh.getRotation();
	glm::vec3 mesh_pos = _mesh.getPosition();
	glm::vec3 mesh_scale = _mesh.getScale();

	glm::mat4 projection = _camera.getProjectionMatrix();

	glm::vec3 view_rot = _camera.getRotation();
	glm::mat4 view = glm::mat4( 1.0f );
	view = glm::rotate( view, glm::radians( view_rot.x ), glm::vec3( 1.0, 0.0, 0.0 ) );
	view = glm::rotate( view, glm::radians( view_rot.y ), glm::vec3( 0.0, 1.0, 0.0 ) );
	view = glm::rotate( view, glm::radians( view_rot.z ), glm::vec3( 0.0, 0.0, 1.0 ) );
	view = glm::translate( view, -_camera.getPosition() );

	glm::mat4 model = glm::mat4( 1.0f );
	model = glm::rotate( model, glm::radians( mesh_rot.x ), glm::vec3( 1.0, 0.0, 0.0 ) );
	model = glm::rotate( model, glm::radians( mesh_rot.y ), glm::vec3( 0.0, 1.0, 0.0 ) );
	model = glm::rotate( model, glm::radians( mesh_rot.z ), glm::vec3( 0.0, 0.0, 1.0 ) );
	model = glm::scale( model, glm::vec3( mesh_scale.x, mesh_scale.y, mesh_scale.z ) );
	model = glm::translate( model, glm::vec3( mesh_pos.x, mesh_pos.z, mesh_pos.y ) );

	// pass matrices to attribute
	glUniformMatrix4fv( glGetUniformLocation( _shaderProgram, "projection" ), 1, GL_FALSE, glm::value_ptr( projection ) );
	glUniformMatrix4fv( glGetUniformLocation( _shaderProgram, "view" ), 1, GL_FALSE, glm::value_ptr( view ) );
	glUniformMatrix4fv( glGetUniformLocation( _shaderProgram, "model" ), 1, GL_FALSE, glm::value_ptr( model ) );

	// bind and render
	glBindVertexArray( _mesh.getVertexArrayObject() );
	glUseProgram( _shaderProgram );
	glPolygonMode( GL_FRONT_AND_BACK, _mode );
	glDrawElements( GL_TRIANGLES, _mesh.getFaceIndicesBufferSize(), GL_UNSIGNED_INT, 0 );
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
	glDepthRange( 0.0f, 1.0f );
	

	initShaders();
}

unsigned int cGraphicsManager::loadMesh( const std::string& _path )
{
	cMesh mesh;
	mesh.loadFromFile( _path );
	m_meshes.push_back( mesh );
	return m_meshes.size();
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

void cGraphicsManager::setMeshPosition( const unsigned int& _id, const glm::vec3& _newPosition )
{
	m_meshes[ _id ].setPosition( _newPosition );
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
