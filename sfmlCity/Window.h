#pragma once
#include "SFML/window.hpp"
#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
#include <iostream>
class Window
{
public:
	//Constructor/Destructor
	Window(); 
	~Window(); 
	//Methods
	virtual bool isOn(sf::Vector2f mousePosition); 

	virtual void use(float& dt);
	virtual void show(sf::RenderTarget* target); 

private:

protected: 

};

