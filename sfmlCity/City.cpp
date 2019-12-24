#include "City.h"
using namespace std;

//inilization func
void City::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(250, 250), "test Window", sf::Style::Close | sf::Style::Resize);
	this->window->setView(camera);
}

void City::initView()
{
	this->camera.setCenter(125.f, 125.f);
	this->camera.setSize(125.f, 125.f);
}

bool City::initTileMap()
{
	if (!(this->map.load("tileset.png", sf::Vector2u(32, 32), level, 16, 8)))
		throw("failed to find tileset file");
	else
		return 1; 
}



//constructor/destructor
City::City()
{ 
	this->initView();
	this->initWindow(); //initializes the window
	
	try { //loads the tile map textures and positions
		this->initTileMap();
	}
	catch (const char* msg)
	{
		cerr << msg << endl; //can't find the png file
	}
	
	
}

City::~City()
{
	delete this->window; 
}





//Functions

void City::drawTileMap()
{
	this->window->draw(this->map);
}

void City::pollKeyEvents()
{
	const float deltaTime = this->clock.restart().asSeconds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp) && camera.getSize().x > 10)
		camera.zoom(1.f - deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown) && camera.getSize().x < 1000)
		camera.zoom(1.f + deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		camera.move(-0.5f + deltaTime, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		camera.move(0.5f + deltaTime, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		camera.move(0, -0.5f + deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		camera.move(0, 0.5f + deltaTime);
}

void City::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close(); 
	    }

		if (this->sfEvent.type == sf::Event::MouseWheelMoved)
		{
			camera.zoom(1.f - this->sfEvent.mouseWheel.delta * 0.1f);
		}
	}
}

void City::update()
{
	this->pollKeyEvents();
	this->updateSFMLEvents(); 
}

void City::render()
{
	//clears the window
	this->window->clear();
	//draws
	this->drawTileMap(); 
	
	
	//displays the window
	this->window->setView(camera);
	this->window->display(); 
}

void City::run()
{
	while (this->window->isOpen())
	{
		this->update(); 
		std::cout << "x: " << camera.getSize().x << "y: " << camera.getSize().y << std::endl;
		 
		this->render(); 
		
	}
}


