#include <SFML/Graphics.hpp>
#include "cMesh.h"
int main()
{
    sf::RenderWindow window( sf::VideoMode( 1024, 1024 ), "3D Testing!" );


    cMesh mesh;
    mesh.addVert( sf::Vector3f( 300, 300, 300 ) );
    mesh.addVert( sf::Vector3f( 500, 500, 300 ) );
    mesh.addVert( sf::Vector3f( 300, 500, 300 ) );


    while ( window.isOpen() )
    {
        sf::Event event;
        while ( window.pollEvent( event ) )
        {
            if ( event.type == sf::Event::Closed )
                window.close();
        }

        window.clear();

        mesh.draw( window );
        
        window.display();
    }


    return 0;
}