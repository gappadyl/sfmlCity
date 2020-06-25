#pragma once
#include "Window.h"
//need button class to click

class Gui
{
	enum Button_States{idle_state = 0, hover_state= 1, active_state = 2 };
public:


	class Button//Button class
	{

	private:
		//button details
		short unsigned buttonState;//Buttons state
		bool isClickable;//can be clicked
		bool is_clicked; //has been clicked
		short unsigned id;//buttons assigned id

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
		std::string true_text; 
		std::string false_text; 

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned int textSize,
			sf::Color IdleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color outline_hover_color, sf::Color outline_active_color, sf::Color outline_idle_color, short unsigned id = 0, bool clickable = true);
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string true_text, std::string false_text, unsigned int textSize,
			sf::Color IdleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color outline_hover_color, sf::Color outline_active_color, sf::Color outline_idle_color, short unsigned id = 0, bool clickable = true);
		~Button();

		//accesors
		std::string returnText()const;
		bool isActive()const;
		bool isHover()const; 
		bool clickedStatus() const;//returns clicked on or off
		short unsigned getId()const;
		std::string getTrueText()const;
		std::string getFalseText() const; 
		

		//mutator
		void moveButton(float x_Dif, float y_Dif); 

		void setText(const std::string newText);
		void setId(const short unsigned Id);
		void clicked(); 

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
		bool move; 
		bool hidden; // can we see the selecture
		bool is_moving;
		bool selectorIsVisible; 

		float keyTime; // used to make sure when we are pushing buttons it's updating appropriately 
		const float maxKeyTime; 

		
		Gui::Button* hideButton; 
		Gui::Button* pinButton; 

		std::vector<Gui::Button*> buttonVector;
		//Mouse controls
		sf::Vector2u mousPosGrid; //row column the mouse position is on the text selector
		sf::Vector2i mousePos; //pixels 
		

		sf::Sprite textureSheet;
		sf::RectangleShape selectorBody;//a Rectangle shape that will contain all the sprites
		sf::RectangleShape selector; //selector for each sprite
		sf::RenderWindow* window; 
		sf::IntRect textureRect; //holds the specific texture selected
	public: 
		//Const/Destructor
		TextureSelection(float x, float y, float width, float height, float gridSize, const sf::Texture* sheet, 
			sf::Font& font, std::string text, sf::RenderWindow* window);
			~TextureSelection();

		//Accessors
			const bool& isHidden() const; 
			const bool& isMoveable() const; 
			const bool& isSelectorActive() const; 
			const bool& isMoving() const; 
			const bool& isButtonActive() const; 
			const sf::IntRect& getTextureSelected(); 

	    //mutators

	    const bool getKeyTime();//handles delta time with key presses
		void highlightSelector(const bool& move, sf::Color new_color);
	    void updateKeyTime(const float& dt);
		void updateButtons(sf::Vector2i& mousePosition);
		void update(sf::Vector2i& mousePosition, const float& dt); //updating to see if selecting new texture
		void render(sf::RenderTarget& target);//rendering the button and texture selector out to the window; 
		void selectorSetVisible(bool is_visible); 
		void moveSelector(float x_Dif, float y_Dif); 
		
		void select();
	};

	class Highlight {
	public:
		//Constructor/Destructor
		Highlight(sf::RenderWindow* window,  int tileSize, sf::Color color);
		~Highlight(); 


		//functions
		void render(sf::RenderTarget& target); 
		void update(sf::RenderWindow* target);
		void setVisibility(bool isVisible); 
		void outOfBoundsHighlight(const bool inBounds, sf::Color new_color); 

	private:
		sf::RectangleShape highlight; 
		sf::Vector2i mpos;
		int x;
		int y;
	    int tile_Size; 
		sf::Color outlineColor; 
		bool visible; 
	};
	
protected: 
	
private:
	sf::Font font;
	sf::Texture sheet; 
	
};

