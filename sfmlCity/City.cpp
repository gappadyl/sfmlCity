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
	camera.ratioUpdate(window->getSize().x, window->getSize().y); 
	
}
void City::initPopulation()
{
	//initializing texture
	sf::Texture temp;
	temp.loadFromFile("Textures/Player/DinoSprites - vita.png");
	this->textures["PLAYER_IDLE"] = temp;

	this->population = new Population( (this->level), this->window, textures); 

	 
}

bool City::initTileMap()
{

	if (!(this->map.load("Textures/background/tileset.png", sf::Vector2u(tileLength, tileLength), level, widthMap, heightMap)))
		throw("failed to find tileset file");
	else
		return 1; 
}


//Constructors/Destructors
City::City()
{

	this->initWindow(); //initializes the window
	this->initView(); // initializes camera
	this->levelMap = new TileMapLevel("test_load.txt"); 
	this->levelMap->save_to_file("test_save.txt"); 
	try { //loads the tile map textures and positions
		this->initTileMap();
	}
	catch (const char* msg)
	{
		cerr << msg << endl;


	}

	initPopulation(); 
}

City::~City()
{
	delete this->population; 
	delete this->window; 

}

//Functions


void City::drawTileMap()
{
	this->window->draw(this->map);
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
	this->population->updatePopulation(dt); 
	if (levelMap)
	{
		this->levelMap->gridBoarderCollisionCheck(population->getPlayer());
	}
	this->camera.boundsControl((camera.getCamera() ), camera.getOldCamera());//bounds check post movement

}

void City::render()
{
	//clears the window
	this->window->clear();

	//draws
	//this->drawTileMap(); 
	levelMap->render(*window, true); 
	this->population->renderPopulation(); 
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


