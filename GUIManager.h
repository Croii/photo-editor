#pragma once

#include "GUIElement.h"

class GUIManager
{
public:
	GUIManager() = default;
	~GUIManager() = default;

	void addElement(std::unique_ptr<GUIElement> element);
	void renderAll(sf::RenderWindow& window);
	void updateAll();



private:
	std::vector < std::unique_ptr<GUIElement>> guiElements;

};

