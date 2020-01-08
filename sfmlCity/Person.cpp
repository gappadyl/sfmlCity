#include "Person.h"
//Initializer func
void Person::initVariables()
{
	
	 
}


//Constructors/Destructors
Person::Person(float x, float y, sf::Texture& texture_sheet)
{

	initVariables(); 

	try {
		this->setTexture(texture_sheet);
		this->setPosition(x, y);
	}
	catch (const char* msg)
	{
		std::cerr << msg << std::endl; 
	}

	this->CreateMovementComponent(100.f, 20.f, 0.5f);
	this->CreateAnimationComponent(this->sprite, texture_sheet);
	this->animationComponent->addAnimation("PLAYER_IDLE", 100.f, 1, 1, 4, 1, 24, 24); 
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




