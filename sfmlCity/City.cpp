#include "City.h"
using namespace std;

//inilization func
void City::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "test Window", sf::Style::Close | sf::Style::Resize);
	this->window->setView(camera);
}

void City::initView()
{
	this->camera.setCenter(256.f, 256.f);
	this->camera.setSize(256.f, 256.f);
}

bool City::initTileMap()
{
	if (!(this->map.load("tileset.png", sf::Vector2u(32, 32), level, 16, 16)))
		throw("failed to find tileset file");
	else
		return 1; 
}



//constructor/destructor
City::City()
{ 
	this->initView();
	this->initWindow(); //initializes the window
	
	try { //loads the tile map textures and positions
		this->initTileMap();
	}
	catch (const char* msg)
	{
		cerr << msg << endl; //can't find the png file
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

//the number 512 is determined by 16x32, 16 is the number of horizontal/vertical tiles and 32 is the horizontal/vertical size of the tiles
bool City::isCameraLegal(sf::Vector2f center, sf::Vector2f size)
{
	if (center.x - size.x / 2 < 0)
		return false;

	if (center.x + size.x / 2  > 512)
		return false;

	if (center.y - size.y / 2 < 0)
		return false;

	if (center.y + size.y / 2 > 512)
		return false;

	return true;
}

void City::pollKeyEvents()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp) && camera.getSize().x >= 10)
		camera.zoom(1.f - this->dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown) && camera.getSize().x <= 1000)
		camera.zoom(1.f + this->dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			camera.move(-0.5f + this->dt, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			camera.move(0.5f + this->dt, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			camera.move(0, -0.5f + this->dt);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			camera.move(0, 0.5f + this->dt);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			const sf::Vector2i mousepos = sf::Mouse::getPosition();

			if (this->mousepos != mousepos)
			{
				sf::Vector2f relativePos1 = this->window->mapPixelToCoords(mousepos);
				sf::Vector2f relativePos2 = this->window->mapPixelToCoords(this->mousepos);
				camera.move(relativePos2.x - relativePos1.x, relativePos2.y - relativePos1.y);
			}
		}

	this->mousepos = sf::Mouse::getPosition();
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

	if (!isCameraLegal(this->camera.getCenter(), this->camera.getSize()))
	{
		this->camera = oldCam;
	}
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


