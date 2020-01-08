
#include "Entity.h"
//initialization
void Entity::initVariables()
{
	this->movementComponent = NULL; 
}

void Entity::setTexture(sf::Texture& texture)
{
	
	this->sprite.setTexture(texture); 

}

void Entity::setPosition(const float x, const float y)
{
		sprite.setPosition(sf::Vector2f(x, y));
}

void Entity::CreateMovementComponent(const float maxSpeed, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(maxSpeed, sprite, acceleration, deceleration); 
}
void Entity::CreateAnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet) {

	this->animationComponent = new AnimationComponent(sprite, texture_sheet); 

}


//Constructor/Destructor
Entity::Entity()
{
	initVariables(); 
}

Entity::~Entity()
{
	 
	delete this->movementComponent; 
	delete this->animationComponent; 
	
}

//Functions
void Entity::move(const float& dt, const float x, const float y)
{

	if ( this->movementComponent)
	{
		this->movementComponent->move(x, y, dt); 
		
	}
}

void Entity::update(const float& dt)
{
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) )
	{
		move(dt, 0.f, -1.f);
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		move(dt,-1.f, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		move(dt, 0.f, 1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		move(dt, 1.f, 0.f);
	}

	if (movementComponent)
	{
		movementComponent->update(dt);
	}
}

void Entity::render(sf::RenderTarget* target)
{
	if (target == nullptr)
	{
		throw("error RenderTarget not found");
	}
	else
		target->draw(this->sprite);
}





