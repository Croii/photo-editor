#include "GUIManager.h"

void GUIManager::addElement(std::unique_ptr<GUIElement> element)
{
	guiElements.push_back(std::move(element));
}

void GUIManager::renderAll(sf::RenderWindow& window)
{
	for (auto& element : guiElements)
	{
		if (element->isVisible())
		{
			element->render(window);
		}
	}
}

void GUIManager::updateAll()
{
	for (auto& element : guiElements)
	{
		element->update();
	}
}
