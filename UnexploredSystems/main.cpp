#include <SFML/Graphics.hpp>
#include <iostream>

#include "cMesh.h"
int main()
{
    sf::RenderWindow window( sf::VideoMode( 1024, 1024 ), "3D Testing!" );


	cMesh mesh( sf::Vector3f( 512, 512, 512 ), sf::Vector3f( -0.2f, 0, 0 ) );
	mesh.setScale( sf::Vector3f( 0.4f, -0.4f, 0.4f ) );
	mesh.loadFromFile( "ImperialStarDestroyer.obj" );
	
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

		
		mesh.rotate(sf::Vector3f( 0, dt / 2.0f, 0 ));
		mesh.draw( window );
        
		window.display();

	}


    return 0;
}