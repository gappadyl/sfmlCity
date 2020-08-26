#include "MovementComponent.h"

//Constructor/destructor
MovementComponent::MovementComponent(const float maxVelocity, sf::Sprite& sprite, float acceleration, float deceleration):sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	direction.x = 1; //set a initial direction for character
}

MovementComponent::~MovementComponent()
{

}

//Functions

void MovementComponent::move(const float x, const float y, const float& dt)
{
	//Acceleration
	setCurrentVelocity(x, y, dt); 
	if(velocity.x!=0.f) //dont want the direction to be nothing
	setCurrentDirection(velocity.x, velocity.y); 
}

void MovementComponent::setCurrentVelocity(const float dir_x, const float dir_y, const float& dt)
{//accelerates sprite
	
	this->velocity.x += acceleration * dir_x*dt *25.f ; 
	this->velocity.y += acceleration * dir_y*dt*25.f; 

}

void MovementComponent::setCurrentDirection(const float dir_x, const float dir_y)
{
	 

	this->direction.x = dir_x;
	this->direction.y = dir_y; 

}


sf::Vector2f MovementComponent::getVelocity()const
{
	return this->velocity; 
}
sf::Vector2f MovementComponent::getDirection() const
{
	return this->direction;
}
void MovementComponent::manualControl()
{
	
}

void MovementComponent::setVelocity(float x, float y)
{
	this->velocity.x = x;
	this->velocity.y = y; 
}

void MovementComponent::update(const float& dt)
{
	/*Decelerates velocity and checks maxSpeed */
	if (velocity.x > 0)
	{
		//Deceleration
		velocity.x -= deceleration*700.f*dt; 
		if (velocity.x < 0.f)
			velocity.x = 0.f; 
		//check maxVelocity
		if (this->velocity.x > maxVelocity)
		{
			this->velocity.x = maxVelocity;
		}
	}
	else if (velocity.x < 0)
	{
		//Deceleration
		velocity.x += deceleration*700.f*dt; 
		if (velocity.x > 0)
			velocity.x = 0; 
		//check maxVelocity
		if (velocity.x < -maxVelocity)
		{
			velocity.x = -maxVelocity;
		}
	}
	 
	if (velocity.y > 0)
	{
		//Deceleration
		velocity.y -= deceleration*700.f*dt; 
		if (velocity.y < 0)
			velocity.y = 0; 

		//check maxVelocity
		if (this->velocity.y > maxVelocity)
		{
			this->velocity.y = maxVelocity;
		}

	}
	else if (velocity.y < 0)
	{
		//Deceleration
		velocity.y += deceleration*700.f*dt; 
		if (velocity.y > 0)
			velocity.y = 0;

		//check maxVelocity
		if (velocity.y < -maxVelocity)
		{
			velocity.y = -maxVelocity;
		}
	}
	
	sprite.move(velocity * dt); 
}