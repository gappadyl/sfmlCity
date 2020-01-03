#pragma once

#include "SFML/window.hpp"
#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
#include<iostream>
class Entity
{//Base class for any Entitys
private:

protected:
	sf::RectangleShape shape; 

public:
	Entity(); 
	~Entity(); 

	virtual void move(const float& dt, const float x, const float y)=0; 
	virtual void update(const float& dt) = 0; 
	virtual void render(sf::RenderTarget* target) = 0; 



};

