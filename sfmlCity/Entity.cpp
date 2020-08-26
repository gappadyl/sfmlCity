
#include "Entity.h"
//initialization
void Entity::initVariables()
{

	this->movementComponent = NULL; 
	this->animationComponent = NULL; 
	this->hitBoxComponent = NULL; 
	currentPath = NULL; 
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
		//std::cout << movementComponent->getVelocity().x << std::endl; 

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
	delete this->currentPath; 
	
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

void Entity::update(const float& dt, Path* path)
{

	if (movementComponent)
	{
		movementComponent->update(dt);
		hitBoxComponent->update();

		//checkDirection();
	}
	
	updatePath(path); 

	if (currentPath != NULL )
	{
		int x_dif = currentPath->data.x - getGridPosition().x;
		int y_dif = currentPath->data.y - getGridPosition().y;

	

		if (x_dif == 0 && y_dif == 0)
		{
			currentPath = currentPath->next;
			
			if (currentPath != NULL)
			{//if we're not on the last position
				x_dif = currentPath->data.x - getGridPosition().x;
				y_dif = currentPath->data.y - getGridPosition().y;
			}
		}


		//stops acceleration after direction change
		if (x_dif == 0)
		{
			stopVelocityX();
		}

		if (y_dif == 0)
		{
			stopVelocityY(); 
		}

		move(dt, x_dif, y_dif);//is teleporting, why??
	}
	
	
}

void Entity::updatePath(Path* path)
{
	if (currentPath == NULL)
	{
		currentPath = path; 
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
sf::Vector2f Entity::getPosition()const
{
	return(sprite.getPosition()); 
}
sf::Vector2i Entity::getGridPosition()const
{//want to return what grid position the corners are on

	//depends on velocity
	sf::Vector2i topLeft_corner = sf::Vector2i(getPosition().x / 32, getPosition().y / 32); 
	sf::Vector2i botRight_corner = sf::Vector2i((getPosition().x + getHitBoxDimensions().x) / 32, (getPosition().y + getHitBoxDimensions().y) / 32); 

	sf::Vector2f direction = movementComponent->getDirection(); 

	if (direction.x > 0)
	{// if moving right
		if (direction.y > 0)
		{//if moving right and down
			return topLeft_corner;
		}
		else if (direction.y < 0)
		{//if moving right and up
			return sf::Vector2i(topLeft_corner.x, botRight_corner.y); 
		}
		else
		{//just moving Right
			return topLeft_corner; 
		}
	}
	else if (direction.x < 0)
	{// if moving left

		if (direction.y > 0)
		{//if moving left and down
			return sf::Vector2i(botRight_corner.x, topLeft_corner.y); 
		}
		else if (direction.y < 0)
		{//if moving left and up
			return botRight_corner; 
		}
		else
		{// if moving just left
			return botRight_corner;
		}
	}
	else if(direction.y > 0)
	{// if just moving down
		return topLeft_corner; 
	}
	else if (direction.y < 0)
	{// if just moving up
		return botRight_corner; 
	}
	
	 
}
//Mutators

void Entity::setTexture(sf::Texture& texture)
{

	this->sprite.setTexture(texture);

}

void Entity::setPosition(const float x, const float y)
{
	sprite.setPosition(sf::Vector2f(x, y));
}
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
