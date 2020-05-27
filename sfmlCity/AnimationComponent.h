#pragma once
#include <iostream>
#include <map>
#include <string>
#include"SFML/window.hpp"
#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
#include <math.h>
class AnimationComponent//Handles animations
{
public:
	//Constructor/Destructor
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet); 
	virtual ~AnimationComponent(); 

	//Functions
	void update(const float& dt);//updates all animations
	void play(const float& dt, const std::string key); 
	void addAnimation(const std::string key,
		float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height);

	/*void pauseAnimation(const std::string animation);
	void startAnimation(const std::string animation);
	void addAnimation(const std::string key); */

private:
	
	class Animation/*Creates animation class, this class will control each animation*/
	{
	
	public:

		//Variables
		sf::Sprite& sprite; //sprite
		sf::Texture& textureSheet; //animation texture sheet

		float animationTimer; 
		float timer; 
		int textureWidth; //width of texture
		int textureHeight; //height of texture

		sf::IntRect startRect; /* the start, current, and end Rectangle the sprite will look at in the texture sheet*/
		sf::IntRect endRect; 
		sf::IntRect currentRect; 

		//Constructor
		Animation(sf::Sprite& sprite, sf::Texture& textureSheet,
			float animation_timer, 
			int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
			:sprite(sprite), textureSheet(textureSheet), animationTimer(animation_timer), textureHeight(height), textureWidth(width), timer(0.f)
		{
			//initializes all three Rects
			this->startRect = sf::IntRect(start_frame_x*abs(width), start_frame_y*height, width, height); //rectangle of first frame of animation
			this->endRect = sf::IntRect(frames_x* abs(width), frames_y * height, width, height);  //rectangle of last frame of animation
			this->currentRect = this->startRect; 
			
			//Sets sprites texture and Rect spot in texture
			this->sprite.setTexture(this->textureSheet, true); 
			this->sprite.setTextureRect(this->startRect); 
			
		}
		
		void play(const float& dt)
		{//updates texture of sprite
			
			//Update timer
			timer += 10.f * dt; 

			if (this->timer >= this->animationTimer)
			{
				//reset timer
				this->timer = 0.f;

				if (this->currentRect.left != this->endRect.left)//checks if end of animation
				{
					this->currentRect.left += abs(this->textureWidth); //moves animation to left
				}
				else
				{
					//std::cout << "end of animation" << std::endl; 
					this->currentRect.left = this->startRect.left; //resets current Rect
					
				}
				this->sprite.setTextureRect(this->currentRect); 
			}
		}

		void reset()
		{
			this->timer = 0.f; 
			this->currentRect = this->startRect; 
			
		}
	};
 
	//Variables
	sf::Sprite& sprite; 
	sf::Texture& textureSheet;
	

	std::map<std::string, Animation*> animations; //map of animations
};

