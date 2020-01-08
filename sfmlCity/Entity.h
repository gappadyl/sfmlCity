#pragma once
#include "MovementComponent.h"

class Entity
{//Base class for any Entitys
private:
	
protected:
	//Variables
	sf::Sprite sprite; 
	MovementComponent* movementComponent; 


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
	


};

