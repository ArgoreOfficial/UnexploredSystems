#include "cGameManager.h"

cGameManager::cGameManager()
{
	m_window = new sf::Window();
}

cGameManager::~cGameManager()
{
	delete m_window;
}


void cGameManager::setupShaders()
{
	// create vert and frag shaders

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	unsigned int vertexShader;
	vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
	glCompileShader( vertexShader );

	const char* fragShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4( 1.0f, 0.5f, 0.2f, 1.0f );\n"
		"}\0";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragShaderSource, NULL );
	glCompileShader( fragmentShader );


	// create and link shader program, basically combine the vert
	// and frag shader into a single shader program that can then be used by the gpu
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader( shaderProgram, vertexShader );
	glAttachShader( shaderProgram, fragmentShader );
	glLinkProgram( shaderProgram );

	// every draw call after this will use this shader program
	glUseProgram( shaderProgram );

	// delete shaders, we don't need them anymore
	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );
}

void cGameManager::setupVAO()
{

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
	// glClearColor( 0.392f, 0.584f, 0.929f, 1.0f ); // cornflower blue
	glClearColor( 0, 0, 0, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // draw as wireframe

	for ( int i = 0; i < m_meshes.size(); i++ )
	{
		glBindVertexArray( m_meshes[ i ].getVertexArrayObject() );
		glDrawElements( GL_TRIANGLES, m_meshes[ i ].getFaceIndicesBufferSize(), GL_UNSIGNED_INT, 0);
	}


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
	m_window = new sf::Window( sf::VideoMode( 640, 480 ), "Unexplored Systems - Triangle!", sf::Style::Default, settings );

	sf::ContextSettings set_settings = m_window->getSettings();

	std::cout << "depth bits: " << settings.depthBits << std::endl;
	std::cout << "stencil bits: " << settings.stencilBits << std::endl;
	std::cout << "antialiasing level: " << settings.antialiasingLevel << std::endl;
	std::cout << "version: " << settings.majorVersion << "." << settings.minorVersion << std::endl;
	std::cout << "\n";

	m_window->setVerticalSyncEnabled( false );
	m_window->setActive( true );

	glEnable( GL_TEXTURE_2D );
	glViewport( 0, 0, m_window->getSize().x, m_window->getSize().y );
	glewExperimental = GL_TRUE;
	glewInit();

	cMesh a;
	m_meshes.push_back( a );
	m_meshes[ 0 ].loadFromFile( "NormalISD.obj" );

	cMesh b;
	m_meshes.push_back( b );
	m_meshes[ 1 ].loadFromFile( "testship.obj" );

	setupShaders();
}

void cGameManager::run()
{
	// cMesh mesh( sf::Vector3f( 512, 512, 512 ), sf::Vector3f( -0.2f, 0, 0 ) );
	// mesh.setScale( sf::Vector3f( 0.4f, -0.4f, 0.4f ) );
	// mesh.loadFromFile( "ImperialStarDestroyer.obj" );

	sf::Clock delta_clock;

	while ( m_running )
	{
		float dt = delta_clock.restart().asSeconds();
		
		update();
		draw();
	}
}



