#include "City.h"


//inilization func
void City::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(500, 500), "test Window", sf::Style::Close | sf::Style::Resize);
}

void City::initTriangle()
{
	this->triangle = new sf::VertexArray(sf::Triangles, 3);
	
}
//constructor/destructor
City::City()
{ 
	this->initWindow(); 
	this->initTriangle(); 

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


