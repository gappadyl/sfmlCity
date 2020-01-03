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
	
	camera = Camera(this->window, widthMap, heightMap, tileLength); //initialize camera object
	
	
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


void City::drawTileMap()
{
	this->window->draw(this->map);
}

void City::initPopulation()
{

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

		camera.SFMLCameraEvents(this->sfEvent, this->bHasFocus); 
		
	}
}

void City::update()
{
	
	this->camera.cameraUpdate(dt, bHasFocus); //camera update
	this->updateSFMLEvents(); //SFML Event
	this->camera.boundsControl((camera.getCamera() ), camera.getOldCamera());//bounds check post movement

}

void City::render()
{
	//clears the window
	this->window->clear();

	//draws
	this->drawTileMap(); 
	//sets window view to camera
	this->camera.cameraRender();
	//displays the window
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


