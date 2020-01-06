#include "Person.h"

void Person::initVariables()
{
	
	 
}
void Person::initComponents()
{
	
}

Person::Person(float x, float y, sf::Texture* texture)
{
	initVariables(); 
	initComponents(); 

	try {
		this->createSprite(texture);
		this->setPosition(x, y);
	}
	catch (const char* msg)
	{
		std::cerr << msg << std::endl; 
	}
}
Person::Person()
{

}
Person::~Person()
{
	 
}

std::string Person::getName()
{
	return this->name; 
}

sf::Vector2f Person::getLocation()
{
	return this->location;
}

void Person::setLocation(sf::Vector2f location)
{
	this->location = location; 
}
void Person::setName(std::string name)
{
	this->name = name; 
}




