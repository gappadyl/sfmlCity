#include "Camera.h"



void Camera::initCamera()
{
	this->camera.setCenter((this->map_Width/2.f *this->map_PixelLength), this->map_Height*this->map_PixelLength / 2.f); 
	this->camera.setSize(this->window->getSize().x/2.f, this->window->getSize().y/2.f); 
	this->camera = correctRatioView(this->camera, map_Width, map_Height); 
}

Camera::Camera(sf::RenderWindow* window, float width, float height, float pixelLength)
{
	this->map_Width = width;
	this->map_Height = height;
	this->map_PixelLength = pixelLength; 
	this->window = window; 
	initCamera(); 


}

Camera::Camera()//default constructor
{
	
}

Camera::~Camera()
{


}

void Camera::SFMLCameraEvents(sf::Event cameraEvent, bool hasFocus)
{
	if (cameraEvent.type == sf::Event::MouseWheelMoved && hasFocus==true)
	{

		if (camera.getSize().x >= 10)
			camera.zoom(1.f - cameraEvent.mouseWheel.delta * 0.1f);

		if (camera.getSize().x < 10)
			camera.setSize(10, 10);
	}


	if (cameraEvent.type == sf::Event::Resized)
	{
		camera = correctRatioView(camera, cameraEvent.size.width, cameraEvent.size.height); //gives ratio method the new width and height of resized window

	}

	
}

void Camera::cameraRender()
{
	this->window->setView(this->camera); 
}

sf::View* Camera::getCamera()
{
	return &(this->camera); 
}

sf::View Camera::getOldCamera()
{
	return this->oldCamera; 
}

void Camera::boundsControl(sf::View* currentCamera, sf::View oldCamera)
{
	 
	if (!isCameraLegal(currentCamera->getCenter(), currentCamera->getSize()))
	{
		
		*currentCamera = oldCamera;

	}
}

bool Camera::isCameraLegal(sf::Vector2f center, sf::Vector2f size)
{
	if (center.x - size.x / 2 < 0)
	{
		return false;

	}

	if (center.x + size.x / 2 > (this->map_Width* this->map_PixelLength))
		return false;

	if (center.y - size.y / 2 < 0)
		return false;

	if (center.y + size.y / 2 > (this->map_Height * this->map_PixelLength))
		return false;

	return true;
}

sf::View Camera::correctRatioView(sf::View view, float windowWidth, float windowHeight)
{
	float windowRatio = windowWidth / (float)windowHeight;
	float viewRatio = view.getSize().x / (float)view.getSize().y;

	float posX = 0;
	float posY = 0;
	float sizeX = 1;
	float sizeY = 1;

	bool horizontalLines = true;

	if (windowRatio < viewRatio) //stretched too much vertically
	{
		horizontalLines = false;
	}


	if (horizontalLines)
	{
		sizeX = viewRatio / windowRatio; //amount of width window want to view

		posX = (1 - sizeX) / 2.f; //distance from left 
	}
	else
	{
		sizeY = (windowRatio / viewRatio); //amount of height window want to view

		posY = (1 - sizeY) / 2.f; //distance from top
	}

	view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));


	return view;
}

void Camera::cameraKeyEvents()
{
	//camera controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp) && camera.getSize().x >= 10)
		camera.zoom(1.f - this->dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown) && camera.getSize().x <= 1000)
		camera.zoom(1.f + this->dt);
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		camera.move(-0.5f + this->dt, 0);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		camera.move(0.5f + this->dt, 0);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		camera.move(0, -0.5f + this->dt);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		camera.move(0, 0.5f + this->dt);

	}


	//drag controls
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		const sf::Vector2i mousePos2 = sf::Mouse::getPosition(); //clicked position

		if (this->mousePos != mousePos2)
		{
			sf::Vector2f relativePos1 = this->window->mapPixelToCoords(mousePos2);
			sf::Vector2f relativePos2 = this->window->mapPixelToCoords(this->mousePos);

			camera.move(relativePos2.x - relativePos1.x, relativePos2.y - relativePos1.y);
		}


	}
	this->mousePos = sf::Mouse::getPosition(); //dragged position
}


void Camera::cameraUpdate(float dt, bool hasFocus)//update
{
	this->dt = dt; 
	this->oldCamera = this->camera;

	if (hasFocus)
	{
		cameraKeyEvents(); 
	}




}
