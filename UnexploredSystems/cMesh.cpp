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
			std::vector<int> face;

			// loop through vert indecies 
			for ( int i = 1; i < keys.size(); i++ ) {
				std::string::size_type pos = keys[i].find('/');
				std::string value = keys[ i ].substr( 0, pos );
				face.push_back(stoi(value));
			}

			m_faces.push_back( face );
		}
	}

	file_in.close();
	std::cout << "Finished loading!\n";
}

void cMesh::draw( sf::RenderWindow& _window )
{
	sf::VertexArray vertarr( sf::PrimitiveType::LineStrip );
	
	sf::ConvexShape shape;
	shape.setFillColor( sf::Color( 0, 128, 255, 128 ) );

	for ( int f = 0; f < m_faces.size(); f++ ) {
		shape.setPointCount( m_faces[f].size() );

		for ( int v = 0; v < m_faces[f].size(); v++ )
		{
			cVertex3f vert = m_vertices[ m_faces[ f ][ v ] - 1 ];
			vert.transform( m_rotation, m_scale, m_position );
			sf::Vector3f pos = vert.getPosition();
			
			vertarr.append( sf::Vertex( sf::Vector2f( pos.x, pos.y ), sf::Color::Cyan ) );
			shape.setPoint( v, sf::Vector2f( pos.x, pos.y ) );
		}
		vertarr.append( sf::Vertex( shape.getPoint(0), sf::Color::Cyan ));
		_window.draw( shape );
		_window.draw( vertarr );
		vertarr.clear();
	}
	
	// vertarr.clear();
}
