#pragma once
#include "Entity.h"
class Person: public Entity
{
public:
	//Constructors/destructor
	Person(); 
	~Person(); 
	
	//Functions
	std::string getName();
	sf::Vector2f getLocation(); 
	void setName(std::string name);
	void setLocation(sf::Vector2f location); 

	//inherited from entity
	virtual void move(const float& dt, const float x, const float y); 
	virtual void update(const float& dt); 
	virtual void render(sf::RenderTarget* target); 
	virtual void createSprite(sf::Texture* texture); 

private: 
	std::string name; 
	sf::Vector2f location; 
	float movementSpeed = 100.f; 
	//init functions
	void initVariables(); 
	
};

