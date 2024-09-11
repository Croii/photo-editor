#pragma once

#include "GUIElement.h"
#include <unordered_map>

class GUIManager
{
public:
	GUIManager() = default;
	~GUIManager() = default;

	void addElement(std::unique_ptr<GUIElement> element);
	void renderAll(sf::RenderWindow& window);
	void updateAll(sf::Event& event);



private:

	int priority = 0;
	using GUIElement_ptr = std::unique_ptr<GUIElement>;
	std::unordered_map <int, GUIElement_ptr > guiElements;

};

