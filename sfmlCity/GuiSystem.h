#pragma once
#include "EditorGui.h"

class GuiSystem
{
public:
	//Constructor/Destructor
	GuiSystem(); 
	~GuiSystem();

	//Functions
	void update(float& dt); 
	void render(); 
	void createEditorGui(); 


private:
	EditorGui* Editor; 
};

