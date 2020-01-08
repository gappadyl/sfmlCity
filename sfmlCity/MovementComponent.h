#pragma once
#include"SFML/window.hpp"
#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
#include<iostream>

class MovementComponent
{
public:
	//Constructor/destructor
	MovementComponent(const float maxVelocity, sf::Sprite& sprite, float acceleration, float deceleration);
	~MovementComponent();

	//Functions
	void update(const float& dt); 
	void move(const float x, const float y, const float& dt);
	void setCurrentVelocity(const float x, const float y, const float& dt);

	//Acessors
	sf::Vector2f getVelocity()const; 

	//Variables

private:
	//Functions
	void manualControl();

	//Variables
	sf::Sprite& sprite; 
	float maxVelocity; 
	float acceleration; 
	float deceleration; 
	sf::Vector2f velocity; 
};

