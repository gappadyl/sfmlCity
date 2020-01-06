#include "Population.h"

Population::Population(const int* level, sf::RenderTarget* window)
{
	this->level = level; 
	this->target = window; 

	try {
		setUpPlayer();
	}
	catch (const char* msg)
	{
		std::cerr << msg << std::endl;
	}
}

Population::Population()
{
	std::cout << "default constructor" << std::endl; 
}



Population::~Population()
{

}

void Population::setUpPlayer()
{
	if (!texture.loadFromFile("Textures/Player/DinoSprites - vita.png") ) 
	{
		throw("Can't find texture");
	}
	else
	{
		Robert = Person(50.f, 50.f, &texture); 
	}


}

void Population::updatePopulation(float& dt)
{
	this->Robert.update(dt); 
}

void Population::renderPopulation()
{
	try { 
		this->Robert.render(this->target);
		}
		catch (const char* msg)
		{
		std::cerr << msg << std::endl;
		}
}

float Population::getHappy()
{
	//return this->getHappy; 
	return 0.f; 
}

