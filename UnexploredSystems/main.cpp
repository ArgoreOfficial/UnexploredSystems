#include <SFML/Graphics.hpp>
#include <iostream>

#include "cMesh.h"
int main()
{
    sf::RenderWindow window( sf::VideoMode( 1024, 1024 ), "3D Testing!" );


	cMesh mesh( sf::Vector3f( 300, 300, 0 ), sf::Vector3f( 0, 0, 0 ) );
	mesh.setScale( sf::Vector3f( 100, 100, 100 ) );
	mesh.loadFromFile( "testship.obj" );
	
	sf::Clock delta_clock;

	while ( window.isOpen() )
	{
		float dt = delta_clock.restart().asSeconds();
		sf::Event event;
		while ( window.pollEvent( event ) )
		{
			if ( event.type == sf::Event::Closed )
				window.close();
		}
        
		window.clear();

		mesh.rotate(sf::Vector3f( 2.0f * dt, 2.0f * dt, dt));
		mesh.draw( window );
        
		window.display();

	}


    return 0;
}