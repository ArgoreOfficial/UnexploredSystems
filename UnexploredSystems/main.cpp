#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window( sf::VideoMode( 1024, 1024 ), "3D Testing!" );
    
    while ( window.isOpen() )
    {
        sf::Event event;
        while ( window.pollEvent( event ) )
        {
            if ( event.type == sf::Event::Closed )
                window.close();
        }

        window.clear();
        
        
        
        sf::Vector3f p( 0.0f, 0.0f, 1.0f );
        sf::ConvexShape shape;
        shape.setPointCount( 3 );

        sf::Vector2f offset( 300, 300 );
        sf::Vector2f mousepos(sf::Mouse::getPosition( window ));
        mousepos -= offset;
        sf::Vector2f cross( mousepos.y, -mousepos.x );


        shape.setPoint( 0, sf::Vector2f( 0.0f, 0.0f ) + offset );
        shape.setPoint( 1, (mousepos / 2.0f) + cross / 2.0f + offset);
        shape.setPoint( 2, mousepos + offset );
        shape.setFillColor( sf::Color(0, 128, 255, 128) );
        window.draw( shape );
        
        shape.setPoint( 0, sf::Vector2f( 0.0f, 0.0f ) + offset / 2.0f );
        shape.setPoint( 1, ( mousepos / 2.0f ) + cross / 2.0f + offset / 2.0f );
        shape.setPoint( 2, mousepos + offset / 2.0f );
        shape.setFillColor( sf::Color( 0, 128, 255, 128 ) );
        window.draw( shape );


        window.display();
    }


    return 0;
}