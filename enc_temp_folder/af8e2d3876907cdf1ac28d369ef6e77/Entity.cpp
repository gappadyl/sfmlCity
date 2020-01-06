#include "Entity.h"

//initialization
void Entity::initVariables()
{
	this->texture = NULL;
	this->sprite = NULL;
	this->moveSpeed = 100.f;
}

//Constructor/Destructor
Entity::Entity()
{
	initVariables(); 
}

Entity::~Entity()
{
	std::cout << sprite << std::endl; 
	
	delete this->sprite;
	
	std::cout << "called destructor" << std::endl;
}

//Functions
void Entity::move(const float& dt, const float x, const float y)
{
	this->sprite->move(x * dt * moveSpeed, y * dt * moveSpeed);
}

void Entity::update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
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
		this->move(dt, 1.f, 0);
	}
}

void Entity::render(sf::RenderTarget* target)
{
	if (target == nullptr)
	{
		throw("error RenderTarget not found");
	}
	else if (sprite == NULL)
	{
		throw("error Sprite is NULL"); 
	}
	else
		target->draw(*this->sprite);
}

void Entity::createSprite(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite = new sf::Sprite(*this->texture);

	if (texture == NULL)
	{
		throw("error texture is missing");
	}
}

void Entity::setPosition(const float x, const float y)
{
	if (sprite == NULL)
	{
		throw ("sprite is NULL"); 
	}
	else
	sprite->setPosition(sf::Vector2f(x, y)); 
}

