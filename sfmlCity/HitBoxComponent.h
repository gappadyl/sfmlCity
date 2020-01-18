#pragma once

#include <iostream>
#include"SFML/window.hpp"
#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"

class HitBoxComponent
{

public:
	//Constructor/Destructor
	HitBoxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	~HitBoxComponent(); 
	//Functions
	void update();
	void render(sf::RenderTarget& target);
	bool checkInterset(sf::FloatRect frect); 

	//Accesor
	sf::RectangleShape getRect()const; 

	private:
		sf::Sprite& sprite; 
		 float offSetX; 
		 float offSetY; 
		sf::RectangleShape hitBox; 
		
};

