#pragma once
#include"SFML/window.hpp"
#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
#include<iostream>

class Path
{
public: 
	//Constructor / Destructor
	Path(); 
	Path(sf::Vector2i data); 
	~Path(); 

	sf::Vector2i data; 
	Path* next; 
};

