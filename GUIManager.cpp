#include "GUIManager.h"

void GUIManager::addElement(std::unique_ptr<GUIElement>&& element)
{
	guiElements[priority++] = std::move(element);
}

void GUIManager::renderAll(sf::RenderWindow& window)
{
	for (auto& [_, element] : guiElements)
	{
		if (element->isVisible())
		{
			element->render(window);
		}
	}
}

void GUIManager::updateAll(sf::Event& ev)
{
	for (auto& [_, element] : guiElements)
	{
		element->update(ev);
	}
}
