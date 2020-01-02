#pragma once

#include "SFML/window.hpp"
#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
#include<iostream>

class Camera
{
public:
	//variables


	//functions
	void cameraUpdate(float dt, bool hasFocus);
	void SFMLCameraEvents(sf::Event cameraEvent, bool hasFocus);
	void cameraRender(); 
	void boundsControl(sf::View* Camera, sf::View oldCamera);
	sf::View* getCamera(); 
	sf::View getOldCamera(); 
	
	//constructor/destructor
	Camera(sf::RenderWindow *window, float width, float height, float pixelLength); 
	Camera(); 
	virtual ~Camera(); 

private:
	//variables
	sf::View camera;
	sf::View oldCamera; 
	sf::Vector2i mousePos; 
	sf::RenderWindow* window;
	float map_Width; 
	float map_Height; 
	float map_PixelLength; 
	float dt; 
	
	//functions
	bool isCameraLegal(sf::Vector2f center, sf::Vector2f size); 
	sf::View correctRatioView(sf::View view, float windowWidth, float windowheight); 
	void cameraKeyEvents(); 
	void initCamera(); 
	
	

};

