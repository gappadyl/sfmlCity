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
	map = nullptr; 
	target = NULL; 
}

Population::~Population()
{
	//std::cout << Robert << std::endl; 
	for (Entity* entity : population)
	{
		delete entity; 
	}
	
	 
}

//initializer Functions
void Population::setUpPlayer(std::map<std::string, sf::Texture>& textures)
{
	std::cout << "player set up" << std::endl; 
		this->Robert = new Person(50.f, 50.f, textures["PLAYER_IDLE"] ); 

		std::cout << Robert << std::endl; 
}

void Population::handleEntityCollision(sf::Vector2f lastPos, Entity* entity)
{//the entity is colliding
		
			
	std::vector<sf::Vector2i> collidedCords = map->getCollidedCordinates(entity);
	std::vector<sf::Vector2i> checkParallel = map->getCollidedCordinates(entity);


	sf::Vector2i lastTopLeft = sf::Vector2i(lastPos.x / 32, lastPos.y / 32);
	sf::Vector2i lastBotRight = sf::Vector2i((lastPos.x + entity->getHitBoxDimensions().x) / 32, (lastPos.y + entity->getHitBoxDimensions().y) / 32);

	for (sf::Vector2i cord : collidedCords)
	{

		if ((lastTopLeft.y - cord.y != 0) && (lastBotRight.y - cord.y != 0))
		{//if collided tile has diff y

			int x_dif = 0;
			int y_dif = 0;

			if (checkParallel.size() > 1)
			{//if not corner

				for (int a = 0; a < checkParallel.size(); a++)
				{//calculate delta x and delta y of cords to determine if parallel
					sf::Vector2i currentCord = checkParallel[a];
					x_dif += pow(-1, a) * currentCord.x;
					y_dif += pow(-1, a) * currentCord.y;
				}
				if (x_dif != 0 || (y_dif == 0 && x_dif == 0))
				{//if not parallel or if both collision cords are same space

					entity->setPosition(sf::Vector2f(entity->getPosition().x, lastPos.y));
					entity->stopVelocityY();
					//stop y
				}
			}
			else
			{//if corner: stop y
				entity->setPosition(sf::Vector2f(entity->getPosition().x, lastPos.y));
				entity->stopVelocityY();
			}
		}

		if ((lastTopLeft.x - cord.x != 0) && (lastBotRight.x - cord.x != 0))
		{//if collided tile has diff x


			if (checkParallel.size() > 1)
			{
				int y_dif = 0;
				int x_dif = 0;

				for (int a = 0; a < checkParallel.size(); a++)
				{//calculate delta x and delta y of cords to determine if parallel
					sf::Vector2i currentCord = checkParallel[a];
					y_dif += pow(-1, a) * currentCord.y;

					x_dif += pow(-1, a) * currentCord.x;
				}
				if (y_dif != 0 || (x_dif == 0 && y_dif == 0))
				{//if not parallel or if both collision cords are same space
					entity->setPosition(sf::Vector2f(lastPos.x, entity->getPosition().y));
					entity->stopVelocityX();
					//stop x
				}
			}
			else
			{//if corner : stop x
				entity->setPosition(sf::Vector2f(lastPos.x, entity->getPosition().y));
				entity->stopVelocityX();
			}

		}
	}
}

void Population::flood_fill(int x, int y, std::vector<std::vector<int>>& fill, int steps)
{
	std::vector<sf::Vector2i> stack; 
	stack.push_back(sf::Vector2i(x, y));

	while (stack.size() != 0)
	{
		std::vector<sf::Vector2i> new_stack; 
		std::vector<sf::Vector2i> visited; 

		for (sf::Vector2i cordinate : stack)
		{//for each cordinates in current stack
			

			for (sf::Vector2i newCordinate : fillPoint(cordinate.x, cordinate.y, fill, steps))
			{//fill the points and get all the neighbors
				
				std::cout << "adding cord x" << newCordinate.x << " cord y: " << newCordinate.y << std::endl;
				new_stack.push_back(newCordinate); 
			}

		}

		steps += 1;
		stack = new_stack;//set stack to neighbors

		new_stack.clear(); //clear neighbors

	} 


}

std::vector<sf::Vector2i> Population::fillPoint(int x, int y, std::vector<std::vector<int>>& fill, int steps)
{
	std::vector<sf::Vector2i> empty;

	if (!map->isCordinateInsideMap(sf::Vector2i(x, y)))
	{//out of bounds
		 
		return empty; 
	}
	else
	{
		if (x >= 0 && x < fill.size() && y >= 0 && y < fill[0].size())
		{//checks to make sure point is in fill_vector

			if (!map->isTileCollidable(sf::Vector2i(x, y)) && fill[x][y] < 0)
			{//if tile is not collidable or doesn't contain value
				fill[x][y] = steps;
				std::cout << "filling " << x << " " << y << " with " << steps << std::endl;
			
				return(findNeighbors(x, y) ); 	
			}
			else {
				//hit collidable block or block has number in it
				return empty; 
			}
		}
		else {//the cordinate is not included in vector
			return empty;
		}
	}
}

std::vector<sf::Vector2i> Population::findNeighbors(int x, int y)
{
	std::vector<sf::Vector2i> neighbors; 

	neighbors.push_back(sf::Vector2i(x - 1, y)); //left
	neighbors.push_back(sf::Vector2i(x + 1, y)); //right
	neighbors.push_back(sf::Vector2i(x, y + 1));//down 
	neighbors.push_back(sf::Vector2i(x, y - 1)); //up

	return neighbors; 
}

LinkedPathList* Population::pathFinder(int x, int y, std::vector<std::vector<int>> flood_map, LinkedPathList* list)
{
	if (x >= 0 && x < flood_map[0].size() && y >= 0 && y < flood_map.size())
	{//checks if 

		if (flood_map[x][y] == 0)
		{//if we're at starting place
		list->reverse(); 

			return list; 
		}
		else
		{
			int lowestNum = 50; //arbitray large num 'infinity doesnt work for operations for some reason'

			sf::Vector2i nextCord; 
			std::vector<sf::Vector2i> neighbors = findNeighbors(x, y);

			for (sf::Vector2i cord : neighbors)
			{
				if (cord.x >= 0 && cord.x < flood_map[0].size() && cord.y >= 0 && cord.y < flood_map.size())
				{//if cord is inside vector

					if (flood_map[cord.x][cord.y] >= 0 && flood_map[cord.x][cord.y]< lowestNum)
					{//-1 numbers are walls
						lowestNum = flood_map[cord.x][cord.y]; 
						nextCord = sf::Vector2i(cord.x, cord.y); 
					}
				}
			}
			
			list->add(nextCord); 

			return pathFinder(nextCord.x, nextCord.y, flood_map, list); 
		}
	}
}

//Functions
void Population::updatePopulation(const float& dt)
{
	std::vector<std::vector<int>> fillMap(16, std::vector<int>(16, -1)); 
	std::vector <std::thread> threadList; 
	
	//for (Entity* entity : population)
	//{
		//std::thread pathFinding(&Population::handlePathFinding, std::ref(population.at(0)), std::ref(dt)); 

		//threadList.push_back(pathFinding); 
		/*std::thread pathFinderThread = std::thread(pathFinder, 7, 7, fillMap, newList);
		std::thread pathFinderThread(pathFinder, 7, 7, fillMap, newList);*/
		
		
		
	//}
	

}

 void Population::handlePathFinding(Entity* entity, const float& dt)
{

	std::vector<std::vector<int>> fillMap(16, std::vector<int>(16, -1));

	LinkedPathList* newList = new LinkedPathList();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		flood_fill(entity->getGridPosition().x, entity->getGridPosition().y, fillMap, 0);

		pathFinder(7, 7, fillMap, newList);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		entity->setPosition(1, 1);
	}

	sf::Vector2f lastPosition = entity->getPosition();

	entity->update(dt, newList->head);



	if (map->printEntityBoardPosition(entity))
	{
		handleEntityCollision(lastPosition, entity);
		std::cout << "handeling collision" << std::endl;
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