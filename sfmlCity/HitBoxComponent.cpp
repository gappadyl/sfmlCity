#include "HitBoxComponent.h"

//Constructor/Destructor
HitBoxComponent::HitBoxComponent(sf::Sprite& sprite,
	float offset_x, float offset_y,
	float width, float height) :sprite(sprite), offSetX(offset_x), offSetY(offset_y)
{
	this->hitBox = sf::RectangleShape(sf::Vector2f(width, height) ); //set size
	this->hitBox.setPosition(sprite.getPosition().x + offSetX, sprite.getPosition().y + offSetY); //set position

	//setColors
	this->hitBox.setFillColor(sf::Color::Transparent); 
	this->hitBox.setOutlineThickness(1.f); 
	this->hitBox.setOutlineColor(sf::Color::Red); 
}

HitBoxComponent::~HitBoxComponent()
{

}

//Functions
bool HitBoxComponent::checkInterset(sf::FloatRect frect)
{
	return this->hitBox.getGlobalBounds().intersects(frect); 
}
void HitBoxComponent::update()
{
	this->hitBox.setPosition(sprite.getPosition().x + offSetX, sprite.getPosition().y + offSetY); 
}

void HitBoxComponent::render(sf::RenderTarget& target)
{
	target.draw(hitBox); 
}

//Accesors 
sf::RectangleShape HitBoxComponent::getRect()const
{
	return this->hitBox; 
}