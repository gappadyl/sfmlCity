#pragma once
#include "MovementComponent.h"
#include "AnimationComponent.h"
class Entity
{//Base class for any Entitys
private:
	void checkDirection(); 
protected:
	//Variables
	sf::Sprite sprite; 
	MovementComponent* movementComponent; 
	AnimationComponent* animationComponent; 
	//Functions
	void physicsAnimationCheck(const float& dt); 

public:
	//Constructor/Destructor
	Entity(); 
	virtual ~Entity(); 

	//Functions
	virtual void move(const float& dt, const float x, const float y); 
	virtual void update(const float& dt); 
	virtual void render(sf::RenderTarget* target); 
	
	//Initializers
	virtual void setPosition(const float x, const float y);
	virtual void setTexture(sf::Texture& texture);
	virtual void initVariables();
	virtual void CreateMovementComponent(const float maxSpeedconst, const float acceleration, const float deceleration);
	virtual void CreateAnimationComponent( sf::Texture& textureSheet); 
	


};

