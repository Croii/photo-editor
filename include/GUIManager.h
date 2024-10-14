#pragma once

#include "../include/GUI/GUIElement.h"
#include <memory>
#include <unordered_map>

class GUIManager
{
public:
	GUIManager() = default;
	~GUIManager() = default;

	void addElement(std::unique_ptr<GUIElement>&& element);

	void drawAll(sf::RenderWindow& window);
	void updateAll(sf::Event& event);

	static void initializeAssests();
	static std::shared_ptr<sf::Texture> getAsset(const std::string& name) noexcept;

private:
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> S_ASSETS;
	static std::vector<std::string > S_ASSETNAME;

	int m_priority = 0;
	using GUIElement_ptr = std::unique_ptr<GUIElement>;
	std::unordered_map <int, GUIElement_ptr > m_guiElements;

};

