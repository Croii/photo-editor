#include "GUIManager.h"

std::vector<std::string > GUIManager::S_ASSETNAME = { "saveFile", "selectFile", "rotateLeft", "rotateRight", "grayScale", "blur", "undo", "redo", "zoomIn", "zoomOut"};
std::unordered_map<std::string, std::shared_ptr<sf::Texture>> GUIManager::S_ASSETS;

void GUIManager::addElement(std::unique_ptr<GUIElement>&& element)
{
	m_guiElements[m_priority++] = std::move(element);
}



void GUIManager::drawAll(sf::RenderWindow& window)
{
	for (auto& [_, element] : m_guiElements)
	{
		if (element->isVisible())
		{
			element->draw(window, sf::RenderStates::Default);
		}
	}
}

void GUIManager::updateAll(sf::Event& ev)
{
	for (auto& [_, element] : m_guiElements)
	{
		element->update(ev);
	}
}


void GUIManager::initializeAssests()
{
	for (auto& name : S_ASSETNAME)
	{
		auto texture = std::make_shared<sf::Texture>();
		if (texture->loadFromFile("Assets\\" + name + ".png")) {
			//here is the good texture
			S_ASSETS.insert({ name ,texture });
		}
	}

}

std::shared_ptr<sf::Texture> GUIManager::getAsset(const std::string& name) noexcept
{
	return S_ASSETS[name];
}
