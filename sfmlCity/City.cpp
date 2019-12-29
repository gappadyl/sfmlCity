#include "City.h"
using namespace std;

//inilization func
void City::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "test Window", sf::Style::Close | sf::Style::Resize);
	
}

void City::initView()
{
	this->widthMap = 16;
	this->heightMap = 16;
	this->tileLength = 32;

	this->camera.setCenter((float) (this->heightMap * this->widthMap) , (float) (this->heightMap * this->widthMap)); //sets the camera at the center of the tilemap
	this->camera.setSize(this->window->getSize().x/2, this->window->getSize().y/2);
	this->camera = correctRatioView(camera, this->window->getSize().x, this->window->getSize().y); 
}

bool City::initTileMap()
{
	


	if (!(this->map.load("tileset.png", sf::Vector2u(tileLength, tileLength), level, widthMap, heightMap)))
		throw("failed to find tileset file");
	else
		return 1; 
}




//constructor/destructor
City::City()
{

	this->initWindow(); //initializes the window
	this->initView(); // initializes camera

	try { //loads the tile map textures and positions
		this->initTileMap();
	}
	catch (const char* msg)
	{
		cerr << msg << endl;


	}
}

City::~City()
{
	delete this->window; 
}

//Functions
sf::View City::correctRatioView(sf::View view, int windowWidth, int windowHeight)
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

void City::drawTileMap()
{
	this->window->draw(this->map);
}


bool City::isCameraLegal(sf::Vector2f center, sf::Vector2f size)
{
	if (center.x - size.x / 2 < 0)
	{
		return false;
		
	}

	if (center.x + size.x / 2 > (this->widthMap * this->tileLength))
		return false; 

	if (center.y - size.y / 2 < 0)
		return false;

	if (center.y + size.y / 2 > (this->heightMap * this->tileLength) )
		return false;
	
	return true;
}

void City::boundsControl(sf::View* currentCamera, sf::View oldCamera)
{

	if (!isCameraLegal(currentCamera->getCenter(), currentCamera->getSize()))
	{
		
		*currentCamera = oldCamera;
		
	}

}


void City::pollKeyEvents()
{
	
  bool cameraMove = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp) && camera.getSize().x >= 10)
		camera.zoom(1.f - this->dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown) && camera.getSize().x <= 1000)
		camera.zoom(1.f + this->dt);
  
	if (cameraMove == true)
	{
		
		

		//camera controls
    
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

		

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			const sf::Vector2i mousepos = sf::Mouse::getPosition(); //clicked position

			if (this->mousepos != mousepos)
			{
				sf::Vector2f relativePos1 = this->window->mapPixelToCoords(mousepos);
				sf::Vector2f relativePos2 = this->window->mapPixelToCoords(this->mousepos);

				camera.move(relativePos2.x - relativePos1.x, relativePos2.y - relativePos1.y);
			}
			
			 
		}
		this->mousepos = sf::Mouse::getPosition(); //dragged position

	}
}

void City::updateDT()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void City::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}

		if (this->sfEvent.type == sf::Event::GainedFocus)
		{
			this->bHasFocus = true;
		}

		if (this->sfEvent.type == sf::Event::LostFocus)
		{
				this->bHasFocus = false;
		}

		if (this->sfEvent.type == sf::Event::MouseWheelMoved && this->bHasFocus)
		{
			 
			if(camera.getSize().x >= 10)
				camera.zoom(1.f - this->sfEvent.mouseWheel.delta * 0.1f);
			 
			if (camera.getSize().x < 10)
				camera.setSize(10, 10);
		}
		
		if (this->sfEvent.type == sf::Event::Resized)
		{
			camera = correctRatioView(camera, sfEvent.size.width, sfEvent.size.height); //gives ratio method the new width and height of resized window
			
		}
	}
}

void City::update()
{
	sf::View oldCam = this->camera;
	
	if (this->bHasFocus)
	{
		this->pollKeyEvents();
	}

	this->updateSFMLEvents();

	boundsControl(&(this->camera), oldCam); 

	
}

void City::render()
{
	//clears the window
	this->window->clear();

	//draws
	this->drawTileMap(); 
	
	//displays the window
	this->window->setView(camera);
	this->window->display(); 
}

void City::run()
{
	while (this->window->isOpen())
	{
		this->updateDT();
		this->update(); 
    
		this->render(); 
	}
}


