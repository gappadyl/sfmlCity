#pragma once


#include<iostream>
#include<ctime>
#include<cstdlib>

#include"SFML/System.hpp"
#include"SFML/window.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"



class City
{
private:

	//initialization func
	void initWindow(); 

	//Variables
	sf::RenderWindow window; 
	sf::Event sfEvent; 
public:
	//constructor/destructor
	City();
	virtual ~City();

	//Functions
	void updateSFMLEvents();
	void update();
	void render(); 
	void run(); 

};




