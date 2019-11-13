#include "City.h"


//inilization func
void City::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(500, 500), "test Window", sf::Style::Default);
}


//constructor/destructor
City::City()
{
	this->initWindow(); 
}

City::~City()
{
	delete this->window; 
}





//Functions
void City::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
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
	this->window->clear;
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


