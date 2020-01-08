#include "MovementComponent.h"

//Constructor/destructor
MovementComponent::MovementComponent(const float maxVelocity, sf::Sprite& sprite, float acceleration, float deceleration):sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	
}

MovementComponent::~MovementComponent()
{

}

//Functions

void MovementComponent::move(const float x, const float y, const float& dt)
{
	//Acceleration
	setCurrentVelocity(x, y, dt); 
	
}

void MovementComponent::setCurrentVelocity(const float dir_x, const float dir_y, const float& dt)
{//accelerating sprite
	if (velocity.x > 0.f) //check if moving right
	{
		if (this->velocity.x > maxVelocity)
		{
			this->velocity.x = maxVelocity;
		}
		
	}
	else if (velocity.x < 0.f)// check moving left
	{
		if (velocity.x < -maxVelocity)
		{
			velocity.x = -maxVelocity; 
		}

	}
	else
	{
		this->velocity.x += acceleration * dir_x;
	}

	if (velocity.y > 0.f) //check moving down
	{
		if (this->velocity.y > maxVelocity)
		{
			this->velocity.y = maxVelocity;
		}

	}
	else if (velocity.y < 0.f)// check moving up
	{
		if (velocity.y < -maxVelocity)
		{
			velocity.y = -maxVelocity;
		}

	}
	else
	{
		this->velocity.y += acceleration * dir_y ;
	}

}


sf::Vector2f MovementComponent::getVelocity()const
{
	return this->velocity; 
}
void MovementComponent::manualControl()
{
	
}

void MovementComponent::update(const float& dt)
{
	//Deceleration
	if (velocity.x > 0)
	{
		velocity.x -= deceleration*dt; 
		if (velocity.x < 0.f)
			velocity.x = 0.f; 
	}
	else if (velocity.x < 0)
	{
		velocity.x += deceleration*dt; 
		if (velocity.x > 0)
			velocity.x = 0; 
	}
	sprite.move(velocity * dt); 
}