#include "LinkedPathList.h"

class MovementComponent
{
public:
	//Constructor/destructor
	MovementComponent(const float maxVelocity, sf::Sprite& sprite, float acceleration, float deceleration);
	~MovementComponent();

	//Functions
	void update(const float& dt); 
	void move(const float x, const float y, const float& dt);
	
	 
	//Acessors
	sf::Vector2f getVelocity()const; 
	sf::Vector2f getDirection()const; 
	//Mutators
	void setVelocity(float x, float y); 
	//Variables

private:
	//Functions
	void manualControl();
	void setCurrentVelocity(const float x, const float y, const float& dt);
	void setCurrentDirection(const float x, const float y);

	//Variables
	sf::Sprite& sprite; 
	float maxVelocity; 
	float acceleration; 
	float deceleration; 
	sf::Vector2f velocity; 
	sf::Vector2f direction; 
};

