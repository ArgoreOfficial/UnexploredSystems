#include "cMesh.h"

cMesh::cMesh():
	m_vertexArrayObject( 0 ),
	m_vertexBufferObject( 0 ),
	m_elementBufferObject( 0 ),
	m_vertexBufferSize( 0 ),
	m_faceIndicesBufferSize( 0 ),
	m_position( 0, 0, 0 ),
	m_rotation( 0, 0, 0),
	m_scale( 1, 1, 1 )
{ }

cMesh::cMesh( glm::vec3 _position, glm::vec3 _rotation ):
	m_vertexArrayObject( 0 ),
	m_vertexBufferObject( 0 ),
	m_elementBufferObject( 0 ),
	m_vertexBufferSize( 0 ),
	m_faceIndicesBufferSize( 0 ),
	m_position(_position),
	m_rotation(_rotation),
	m_scale(1,1,1) 
{ }

cMesh::~cMesh()
{ }

void cMesh::loadFromFile( const std::string& _path )
{
	std::cout << "Loading mesh " << _path << "\n";

	// get current working directory
	char buffer[ MAX_PATH ];
	GetModuleFileNameA( NULL, buffer, MAX_PATH );
	std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" );
	std::string current_dir = std::string( buffer ).substr( 0, pos );

	// load file into vector of strings
	std::vector<std::string> string_vec;

	std::ifstream file_in( current_dir + "/" + _path );
	if ( !file_in ) { return; } // error

	// load vertices from string vector
	std::string line;
	while ( std::getline( file_in, line ) )
	{
		// split by spaces
		std::vector<std::string> keys;
		std::istringstream f( line );
		std::string s;
		while ( getline( f, s, ' ' ) ) {
			keys.push_back( s );
		}

		if ( keys[ 0 ] == "v" ) { // vertex
			// vert positions
			m_vertices.push_back( stof( keys[ 1 ] ) );
			m_vertices.push_back( stof( keys[ 2 ] ) );
			m_vertices.push_back( stof( keys[ 3 ] ) );
			m_vertexBufferSize += 12; // float size * 3
			// vert colours
			// m_vertices.push_back(0.0f);// float( rand() % 11 ) / 10.0f );
			// m_vertices.push_back(0.5f);// float( rand() % 11 ) / 10.0f );
			// m_vertices.push_back(1.0f);// float( rand() % 11 ) / 10.0f );
			m_vertices.push_back( float( rand() % 11 ) / 10.0f );
			m_vertices.push_back( float( rand() % 11 ) / 10.0f );
			m_vertices.push_back( float( rand() % 11 ) / 10.0f );
			m_vertexBufferSize += 12; // float size * 3
		}

		else if ( keys[ 0 ] == "f" ) { // face
			// loop through vert indecies 
			for ( int i = 1; i < keys.size(); i++ ) {
				std::string::size_type pos = keys[i].find('/');
				std::string value = keys[ i ].substr( 0, pos );
				
				m_face_indices.push_back( stoi( value ) - 1 );

				m_faceIndicesBufferSize += 4; // unsigned int size
			}
		}
	}

	file_in.close();
	std::cout << "\n";
	std::cout << "m_vertexBufferSize " << m_vertexBufferSize << "\n";
	std::cout << "m_faceIndicesBufferSize " << m_faceIndicesBufferSize << "\n";
	std::cout << "\n";

	setupBuffers();
}

void cMesh::setupBuffers()
{
	float* vertices = getVertexBuffer();
	unsigned int* indices = getFaceIndicesBuffer();

	// vertex array object
	glGenVertexArrays( 1, &m_vertexArrayObject );
	glBindVertexArray( m_vertexArrayObject );

	// vertex buffer object
	glGenBuffers( 1, &m_vertexBufferObject );
	glBindBuffer( GL_ARRAY_BUFFER, m_vertexBufferObject );
	glBufferData( GL_ARRAY_BUFFER, m_vertexBufferSize, vertices, GL_STATIC_DRAW);

	// vert position attribute
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), ( void* )0 );
	glEnableVertexAttribArray( 0 );
	// vert color attribute
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), ( void* )( 3 * sizeof( float ) ) );
	glEnableVertexAttribArray( 1 );

	// element buffer object
	glGenBuffers( 1, &m_elementBufferObject );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_faceIndicesBufferSize, indices, GL_STATIC_DRAW);

	glBindVertexArray( 0 );	
}