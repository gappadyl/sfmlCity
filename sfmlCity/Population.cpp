#include "Population.h"


//Constructors/Destructors
Population::Population( sf::RenderTarget* window, std::map<std::string, sf::Texture> textures, TileMapLevel* level)
{
	this->map = level; 

	this->target = window; 
	this->textures = textures; 
	
	setUpPlayer(this->textures);
	population.push_back(Robert); 
}

Population::Population()
{
	std::cout << "setting Robert to null" << std::endl; 
	Robert = NULL; 
	
	target = NULL; 
}

Population::~Population()
{
	//std::cout << Robert << std::endl; 
	delete this->Robert; 
	
	 
}

//initializer Functions
void Population::setUpPlayer(std::map<std::string, sf::Texture>& textures)
{
	std::cout << "player set up" << std::endl; 
		this->Robert = new Person(50.f, 50.f, textures["PLAYER_IDLE"] ); 

		std::cout << Robert << std::endl; 
}

//Functions
void Population::updatePopulation(float& dt)
{
	for (Entity* entity : population)
	{
		sf::Vector2f lastPosition = entity->getPosition(); 

		entity->update(dt); 

		if (map->printEntityBoardPosition(entity))
		{//the entity is colliding
		
			
			std::vector<sf::Vector2i> collidedCords = map->getCollidedCordinates(entity);
			std::vector<sf::Vector2i> checkParallel = map->getCollidedCordinates(entity); 

		
			sf::Vector2i lastTopLeft = sf::Vector2i(lastPosition.x / 32, lastPosition.y / 32) ; 
			sf::Vector2i lastBotRight = sf::Vector2i( (lastPosition.x + entity->getHitBoxDimensions().x) / 32, (lastPosition.y + entity->getHitBoxDimensions().y )/ 32); 
			for (sf::Vector2i cord : collidedCords)
			{

				if (( lastTopLeft.y - cord.y != 0) && lastBotRight.y-cord.y !=0)
				{//if coliding with block with different y, set to last y
					int x_dif = 0; 
					int y_dif = 0; 

					if (checkParallel.size() > 1)
					{
						for (int a = 0; a < checkParallel.size(); a++)
						{//check if parallel
							sf::Vector2i currentCord = checkParallel[a];
							x_dif += pow(-1, a) * currentCord.x;
							y_dif += pow(-1, a) * currentCord.y;
						}
						if (x_dif != 0 || (y_dif ==0 && x_dif==0))
						{
							entity->setPosition(sf::Vector2f(entity->getPosition().x, lastPosition.y));
							entity->stopVelocityY();
						}
					}
					else
					{
						entity->setPosition(sf::Vector2f(entity->getPosition().x, lastPosition.y));
						entity->stopVelocityY();
					}
				}

				if ((lastTopLeft.x - cord.x != 0) && (lastBotRight.x - cord.x != 0))
				{//if coliding with block with different x, 


					if (checkParallel.size() > 1)
					{
						int y_dif = 0;
						int x_dif = 0;
						bool checkPara;

						for (int a = 0; a < checkParallel.size(); a++)
						{//check if parallel
							sf::Vector2i currentCord = checkParallel[a];
							y_dif += pow(-1, a) * currentCord.y;

							x_dif += pow(-1, a) * currentCord.x;
						}
						if (y_dif != 0 || (x_dif == 0 && y_dif == 0))
						{
							entity->setPosition(sf::Vector2f(lastPosition.x, entity->getPosition().y));
							entity->stopVelocityX();
						}


					}
					else
					{
						std::cout << checkParallel.size() << std::endl;
						entity->setPosition(sf::Vector2f(lastPosition.x, entity->getPosition().y));
						entity->stopVelocityX();
					}

				}
			} 
		}

	}
	

}

void Population::renderPopulation(sf::RenderTarget* window)
{
	try { 
		this->Robert->render(window);
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