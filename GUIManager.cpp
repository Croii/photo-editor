#include "GUIManager.h"

std::vector<std::string > GUIManager::M_ASSETNAME = { "saveFile", "selectFile", "rotateLeft", "rotateRight", "grayScale"};
std::unordered_map<std::string, std::shared_ptr<sf::Texture>> GUIManager::M_ASSETS;

void GUIManager::addElement(std::unique_ptr<GUIElement>&& element)
{
	m_guiElements[priority++] = std::move(element);
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
	for (auto& name : M_ASSETNAME)
	{
		auto texture = std::make_shared<sf::Texture>();
		if (texture->loadFromFile("Assets\\" + name + ".png")) {
			//here is the good texture
			M_ASSETS.insert({ name ,texture });
		}
	}

}

std::shared_ptr<sf::Texture> GUIManager::getAsset(const std::string& name) noexcept
{
	return M_ASSETS[name];
}
