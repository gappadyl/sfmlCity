#include "AnimationComponent.h"


//Constructors/Destructors
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet) :sprite(sprite), textureSheet(texture_sheet)
{

}

AnimationComponent::~AnimationComponent()
{
	std::cout << "Animation destructor" << std::endl; 
	for (auto &i : this->animations)
	{
		delete i.second; 
	}
}
//Functions
void AnimationComponent::update(const float& dt)
{
	play(dt, "PLAYER_IDLE"); 
}

void AnimationComponent::play(const float& dt, const std::string key)
{
	if (animations.count(key) > 0)
	{
		this->animations[key]->play(dt);
	}
	else
	{
		std::cout << "ERROR Animation not found" << std::endl;
	}
}

void AnimationComponent::addAnimation(const std::string key,
	float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet, animation_timer, start_frame_x, start_frame_y, frames_x, frames_y, width, height); 
	 
}


