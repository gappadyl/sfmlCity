#include "Person.h"

void Person::initVariables()
{
	this->setLocation(sf::Vector2f(100.f, 100.f));
	this->shape.setSize(sf::Vector2f(32,32)); 
	this->shape.setFillColor(sf::Color::Blue); 
	this->shape.setPosition(this->location);

	this->setName("Robert Bowen");
	 
}

Person::Person()
{
	initVariables(); 
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

void Person::move(const float& dt, const float x, const float y)
{
	this->shape.move(x * dt * movementSpeed, y*dt* movementSpeed); 
}
void Person::update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
	{
		this->move(dt, -1.f, 0); 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->move(dt, 0, 1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->move(dt, 0, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->move(dt, 1.f, 0 );
	}
}
void Person::render(sf::RenderTarget* target)
{
	if (target == nullptr)
	{
		throw("error RenderTarget not found"); 
	}
	else
	target->draw(this->shape); 
}
void Person::createSprite(sf::Texture* texture)
{

}


