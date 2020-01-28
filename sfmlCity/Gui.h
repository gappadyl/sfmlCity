#pragma once
#include "SFML/window.hpp"
#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"

class Gui
{

public:
	Gui(); 
	~Gui();

	virtual sf::Vector2f getLocation() = 0; 
	virtual void update()=0; 
	virtual void render()=0; 

protected: 

private:

};

