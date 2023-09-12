#include "cMesh.h"

cMesh::cMesh():
	m_position( 0, 0, 0 ),
	m_rotation( 0, 0, 0),
	m_scale( 1, 1, 1 )
{ }

cMesh::cMesh( sf::Vector3f _position, sf::Vector3f _rotation ):
	m_position(_position),
	m_rotation(_rotation),
	m_scale(1,1,1) 
{ }

cMesh::~cMesh()
{ }

void cMesh::loadFromFile( std::string _path )
{
	std::cout << "Loading " << _path << "\n";

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
			addVert( cVertex3f( 
				stof( keys[ 1 ] ),
				stof( keys[ 2 ] ),
				stof( keys[ 3 ] )
			) );
		}
		else if ( keys[ 0 ] == "f" ) { // face
			continue;
		}
	}

	file_in.close();
	std::cout << "Finished loading!\n";
}

struct blueprint {
	std::string id;
	std::string data;
	std::string metadata;
};

void cMesh::draw( sf::RenderWindow& window )
{
	sf::ConvexShape shape;
	shape.setPointCount( 3 );
	shape.setFillColor( sf::Color( 0, 128, 255, 128 ) );

	for ( int i = 0; i < m_vertices.size()-3; i += 3 ) {
		cVertex3f v1 = m_vertices[ i ];
		cVertex3f v2 = m_vertices[ i + 1];
		cVertex3f v3 = m_vertices[ i + 2];

		v1.transform( m_rotation, m_scale, m_position );
		v2.transform( m_rotation, m_scale, m_position );
		v3.transform( m_rotation, m_scale, m_position );

		sf::Vector3f p1 = v1.getPosition();
		sf::Vector3f p2 = v2.getPosition();
		sf::Vector3f p3 = v3.getPosition();

		shape.setPoint( 0, sf::Vector2f( p1.x, p1.y ) );
		shape.setPoint( 1, sf::Vector2f( p2.x, p2.y ) );
		shape.setPoint( 2, sf::Vector2f( p3.x, p3.y ) );
        
		window.draw( shape );
	}

}
