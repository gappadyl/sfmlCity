#pragma once
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitBoxComponent.h"

class Entity
{//Base class for any Entitys
private:
	void checkDirection(); 
protected:
	//Variables
	sf::Sprite sprite; 
	MovementComponent* movementComponent; 
	AnimationComponent* animationComponent; 
	HitBoxComponent* hitBoxComponent; 
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
	virtual void CreateHitBoxComponent(sf::Sprite& sprite, float offsetX, float offsetY);

	//Accessors
	sf::RectangleShape getHitBox()const; 
	sf::Vector2f getHitBoxDimensions()const;

	//Mutators
	void setPosition(sf::Vector2f position);
	void stopVelocityX();
	void stopVelocityY(); 
};

