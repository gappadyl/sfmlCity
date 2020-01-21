#include "Population.h"


//Constructors/Destructors
Population::Population(const int* level, sf::RenderTarget* window, std::map<std::string, sf::Texture> textures)
{
	this->level = level; 
	this->target = window; 
	this->textures = textures; 
	
	setUpPlayer(this->textures);
}

Population::Population()
{
	Robert = NULL; 
	level = NULL; 
	target = NULL; 
}

Population::~Population()
{
	delete this->Robert; 
	
	 
}

//initializer Functions
void Population::setUpPlayer(std::map<std::string, sf::Texture>& textures)
{

		this->Robert = new Person(50.f, 50.f, textures["PLAYER_IDLE"] ); 

}

//Functions
void Population::updatePopulation(float& dt)
{
	this->Robert->update(dt); 

}

void Population::renderPopulation()
{
	try { 
		this->Robert->render(this->target);
		}
		catch (const char* msg)
		{
		std::cerr << msg << std::endl;
		}
}
//Accesors
float Population::getHappy()
{
	return 0.f; 
}

Person* Population::getPlayer()const
{
	if (Robert)
	{
		return Robert;
	}
}