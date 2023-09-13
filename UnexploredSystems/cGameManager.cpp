#include "cGameManager.h"

cGameManager::cGameManager()
{
	m_window = new sf::Window();
}

cGameManager::~cGameManager()
{
	delete m_window;
}


void cGameManager::update()
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
}

void cGameManager::draw()
{
	glClearColor( 0.392f, 0.584f, 0.929f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// mesh.rotate( sf::Vector3f( 0, dt / 2.0f, 0 ) );
	// mesh.draw( m_window );
	// m_window.display();



	

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
	m_window = new sf::Window( sf::VideoMode( 640, 480 ), "Unexplored Systems - OpenGL Setup", sf::Style::Default, settings );

	sf::ContextSettings set_settings = m_window->getSettings();

	std::cout << "depth bits: " << settings.depthBits << std::endl;
	std::cout << "stencil bits: " << settings.stencilBits << std::endl;
	std::cout << "antialiasing level: " << settings.antialiasingLevel << std::endl;
	std::cout << "version: " << settings.majorVersion << "." << settings.minorVersion << std::endl;

	m_window->setVerticalSyncEnabled( false );
	m_window->setActive( true );

	glEnable( GL_TEXTURE_2D );
	glViewport( 0, 0, m_window->getSize().x, m_window->getSize().y );



}

void cGameManager::run()
{
	cMesh mesh( sf::Vector3f( 512, 512, 512 ), sf::Vector3f( -0.2f, 0, 0 ) );
	mesh.setScale( sf::Vector3f( 0.4f, -0.4f, 0.4f ) );
	mesh.loadFromFile( "ImperialStarDestroyer.obj" );

	sf::Clock delta_clock;

	while ( m_window->isOpen() )
	{
		float dt = delta_clock.restart().asSeconds();
		
		update();
		draw();
	}
}



