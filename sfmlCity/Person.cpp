#include "Person.h"
//Initializer func
void Person::initVariables()
{
	
	 
}
void Person::initComponents()
{
	
}

//Constructors/Destructors
Person::Person(float x, float y, sf::Texture* texture)
{
	initVariables(); 
	initComponents(); 

	try {
		this->createSprite(*texture);
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
//Accesor Func
std::string Person::getName()
{
	return this->name; 
}

sf::Vector2f Person::getLocation()
{
	return this->location;
}
//Mutator func
void Person::setLocation(sf::Vector2f location)
{
	this->location = location; 
}
void Person::setName(std::string name)
{
	this->name = name; 
}




