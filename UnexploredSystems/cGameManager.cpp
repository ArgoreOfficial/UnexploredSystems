#include "cGameManager.h"

cGameManager::cGameManager()
{
	m_window = new sf::Window();
}

cGameManager::~cGameManager()
{
	delete m_window;
}


void cGameManager::update(float _dt, float _t)
{
	// handle events
	sf::Event event;
	while ( m_window->pollEvent( event ) )
	{
		if ( event.type == sf::Event::Closed )
		{
			// end the program
			m_running = false;
		}
		else if ( event.type == sf::Event::Resized )
		{
			// adjust the viewport when the window is resized
			glViewport( 0, 0, event.size.width, event.size.height );
		}
	}

	float speed = 5.0f * _dt;

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) ) {
		m_camera.move( glm::vec3( 0, 0, -speed ) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) {
		m_camera.move( glm::vec3( 0, 0, speed ) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) ) {
		m_camera.move( glm::vec3( -speed, 0, 0) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) {
		m_camera.move( glm::vec3( speed, 0, 0 ) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::LShift ) ) {
		m_camera.move( glm::vec3( 0, speed, 0 ) );
	}
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::LControl ) ) {
		m_camera.move( glm::vec3( 0, -speed, 0 ) );
	}

	m_graphicsManager.update(_dt, _t);
}

void cGameManager::draw()
{
	m_graphicsManager.draw(m_camera);

	m_window->display();
}

void cGameManager::createWindow()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;
	m_window = new sf::Window( sf::VideoMode( 640 * 2, 480 * 2), "Unexplored Systems - Models!", sf::Style::Default, settings );
	
	m_window->setVerticalSyncEnabled( false );
	m_window->setActive( true );

	m_camera = cCamera( *m_window );

	m_graphicsManager.initGL( m_window );
	
	// m_graphicsManager.loadMesh( "assets/meshes/testship.obj" );
	m_graphicsManager.loadMesh( "assets/meshes/NormalISD.obj" );
}

void cGameManager::run()
{
	sf::Clock delta_clock;
	sf::Clock total_clock;

	while ( m_running )
	{
		float dt = delta_clock.restart().asSeconds();
		
		update(dt, total_clock.getElapsedTime().asSeconds());
		draw();
	}
}



