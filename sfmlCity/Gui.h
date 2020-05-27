#pragma once
#include "SFML/window.hpp"
#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
#include <iostream>
//need button class to click

class Gui
{
	enum Button_States{idle_state = 0, hover_state= 1, active_state = 2 };
public:


	class Button//Button class
	{

	private:
		//button details
		short unsigned buttonState;
		bool isClickable;
		short unsigned id;
		sf::RectangleShape button;

		//button colors
		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color text_idle_color;
		sf::Color text_hover_color;
		sf::Color text_active_color;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;
		//text details
		sf::Text text;
		sf::Font* font;


	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned int textSize,
			sf::Color IdleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color outline_hover_color, sf::Color outline_active_color, sf::Color outline_idle_color, short unsigned id = 0, bool clickable = true);
		~Button();

		//accesors
		std::string returnText()const;
		bool isActive()const;
		short unsigned getId()const;

		//mutator
		void setText(const std::string newText);
		void setId(const short unsigned Id);

		//functions
		void update(const sf::Vector2i& mousePosition);
		void render(sf::RenderTarget& target);
	};
	Gui(); 
	~Gui();
	
	virtual sf::Vector2f getLocation()const = 0; 
	virtual void update(sf::Vector2i& mousePos, float& dt)=0;
	virtual void render(sf::RenderTarget& target)=0; 

	

	class TextureSelection
	{
	private: 
		float gridSize; //how many pixels are each square
		bool isActive; //are we on the selecture
		bool hidden; // can we see the selecture
		float keyTime; // used to make sure when we are pushing buttons it's updating appropriately 
		const float maxKeyTime; 


		Gui::Button* hideButton; 
		sf::Vector2u mousPosGrid; //row column the mouse position is on the text selector
		sf::Sprite textureSheet;
		sf::RectangleShape selectorBody;//a Rectangle shape that will contain all the sprites
		sf::RectangleShape selector; //selector for each sprite
		
		sf::IntRect textureRect; //holds the specific texture selected
	public: 
		//Const/Destructor
		TextureSelection(float x, float y, float width, float height, float gridSize, const sf::Texture* sheet, 
			sf::Font& font, std::string text );
			~TextureSelection();

		//Accessors
			const bool& isHidden() const; 
			const bool& isSelectorActive() const; 
			const sf::IntRect& getTextureSelected(); 

	    //mutators
	    const bool getKeyTime();//handles delta time with key presses
	    void updateKeyTime(const float& dt);
		void update(sf::Vector2i& mousePosition, const float& dt); //updating to see if selecting new texture
		void render(sf::RenderTarget& target);//rendering the button and texture selector out to the window; 
		
		void select();
	};

	Gui::Button* RobertsButton;
	Gui::TextureSelection* RobertSelector; 
protected: 
	//need to figure out what GUI needs sf::Rectangle shape?? location?
private:
	sf::Font font;
	sf::Texture sheet; 
	
};

