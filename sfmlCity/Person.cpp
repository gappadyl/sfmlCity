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
		this->setPosition(x, y);
	}
	catch (const char* msg)
	{
		std::cerr << msg << std::endl; 
	}

	this->CreateMovementComponent(100.f, 20.f, 0.5f);
	this->CreateAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("PLAYER_IDLE_RIGHT", 2.f, 0, 0, 3, 1, 24, 24); 
	this->animationComponent->addAnimation("PLAYER_IDLE_LEFT", 2.f, 1, 0, 4, 1, -24, 24); 
	this->animationComponent->addAnimation("PLAYER_RUN_RIGHT", 1.f, 4, 0, 9, 1, 24, 24); 
	this->animationComponent->addAnimation("PLAYER_RUN_LEFT", 1.f, 5, 0, 9, 1, -24, 24); 


}
Person::Person()
{

}
Person::~Person()
{
	 
}
//Functions
void Person::update(const float& dt)
{
	Entity::update(dt); 

	this->physicsAnimationCheck(dt); 
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




