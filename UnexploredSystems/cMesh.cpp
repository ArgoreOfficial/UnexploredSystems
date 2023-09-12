#include "cMesh.h"

cMesh::cMesh()
{
	
}

cMesh::~cMesh()
{
	
}

void cMesh::addVert( cVertex3f _vert )
{
	m_vertexArray.push_back( _vert );
}

void cMesh::draw( sf::RenderWindow& window )
{
    sf::ConvexShape shape;
    shape.setPointCount( 3 );
    shape.setFillColor( sf::Color( 0, 128, 255, 128 ) );

    for ( int i = 0; i < m_vertexArray.size(); i += 3 ) {
        sf::Vector3f v1 = m_vertexArray[ i ].getPosition();
        sf::Vector3f v2 = m_vertexArray[ i + 1].getPosition();
        sf::Vector3f v3 = m_vertexArray[ i + 2 ].getPosition();

        shape.setPoint( 0, sf::Vector2f( v1.x, v1.y ) );
        shape.setPoint( 1, sf::Vector2f( v2.x, v2.y ) );
        shape.setPoint( 2, sf::Vector2f( v3.x, v3.y ) );
        
        window.draw( shape );
    }

}
