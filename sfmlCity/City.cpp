#include "City.h"
using namespace std;

//inilization func
void City::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(500, 500), "test Window", sf::Style::Close | sf::Style::Resize);
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

void City::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close(); 
	    }
		
	}
}

void City::update()
{
	this->updateSFMLEvents(); 
}

void City::render()
{
	//clears the window
	this->window->clear();
	//draws
	this->drawTileMap(); 
	
	
	//displays the window
	this->window->display(); 
}

void City::run()
{
	while (this->window->isOpen())
	{
		this->update(); 
		 
		this->render(); 
		
	}
}


