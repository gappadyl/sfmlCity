
#include "Entity.h"
//initialization
void Entity::initVariables()
{

	this->movementComponent = NULL; 
	this->animationComponent = NULL; 
	this->hitBoxComponent = NULL; 
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

void Entity::CreateAnimationComponent( sf::Texture& texture_sheet) {

	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet); 

}

void Entity::CreateHitBoxComponent(sf::Sprite& sprite, float offsetX, float offsetY)
{
	std::cout << this->sprite.getGlobalBounds().width << std::endl; 
	this->hitBoxComponent = new HitBoxComponent(sprite,offsetX,offsetY,sprite.getGlobalBounds().width,sprite.getGlobalBounds().height); //sprite, offsetX, offsetY, width, height [MAYBE SOME WAY to ACCES
}


void Entity::physicsAnimationCheck(const float& dt)
{
	sf::Vector2f velocity; 
	sf::Vector2f direction;

	if (movementComponent )
	{
		velocity = movementComponent->getVelocity(); 
		direction = movementComponent->getDirection(); 

		if (velocity == sf::Vector2f(0, 0)) //if not moving
		{
			if (direction.x < 0)
			{
				this->animationComponent->play(dt, "PLAYER_IDLE_LEFT"); 
			}
			else
			{
				this->animationComponent->play(dt, "PLAYER_IDLE_RIGHT");
			}
		}
		else //if moving
		{
			if (direction.x > 0)
			{
				this->animationComponent->play(dt, "PLAYER_RUN_RIGHT");
			}
			else if(direction.x < 0)
			{
				this->animationComponent->play(dt, "PLAYER_RUN_LEFT"); 
			}
		}
	}
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
	delete this->hitBoxComponent; 
	
}

//Functions
void Entity::move(const float& dt, const float x, const float y)
{

	if ( this->movementComponent)
	{
		this->movementComponent->move(x, y, dt); 
		
	}
}

void Entity::checkDirection()//testing direction
{
	if (movementComponent)
	{
		sf::Vector2f direction = this->movementComponent->getDirection();

		if (direction.x > 0)
		{
			std::cout << "Facing Right" << std::endl; 

		}
		else if (direction.x < 0)
		{
			std::cout << "Facing Left" << std::endl; 
		}

		if (direction.y > 0)
		{
			std::cout << "Facing down" << std::endl; 
		}
		else if (direction.y < 0)
		{
			std::cout << "Facing up" << std::endl; 
		}
		
		
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
		hitBoxComponent->update();
	
		//checkDirection();
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
	if(hitBoxComponent)
	hitBoxComponent->render(*target); 
}

//Accesors
sf::RectangleShape Entity::getHitBox()const
{
	if (hitBoxComponent)
	{
		return this->hitBoxComponent->getRect();
	}
	else
	{
		return sf::RectangleShape();
	}
}

sf::Vector2f Entity::getHitBoxDimensions()const
{
	return sf::Vector2f(this->hitBoxComponent->getRect().getGlobalBounds().width, this->hitBoxComponent->getRect().getGlobalBounds().height); 
}

//Mutators

void Entity::setPosition(sf::Vector2f position)
{
	this->sprite.setPosition(position.x, position.y); 
	
}

void Entity::stopVelocityX()
{
	movementComponent->setVelocity(0.f, movementComponent->getVelocity().y); 
}

void Entity::stopVelocityY()
{
	movementComponent->setVelocity( movementComponent->getVelocity().x, 0.f);
}
