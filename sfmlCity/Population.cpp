#include "Population.h"

Population::Population()
{
	level = 0; 
	target = nullptr; 
}

Population::Population(const int* level, sf::RenderTarget* window)
{
	this->level = level; 
	this->target = window; 
	
}

Population::~Population()
{

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

