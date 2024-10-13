#pragma once
#include "GUIElement.h"
#include "GUIManager.h"
#include <functional>
#include <iostream>

class Button :
	public GUIElement
{
public:
	Button(float pozX, float pozY, float width, float height, sf::Color color, std::function<void()>, bool isVisible = true);
	Button(float pozX, float pozY, float width, float height, std::string asset, std::function<void()>, bool isVisible = true);
	~Button() = default;

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	void update(sf::Event& ev);

	bool isHovered(const sf::Vector2f& mousePos) const override;

private:
	sf::RectangleShape m_boundingBox;
	sf::Texture m_texture;
	std::function<void()> m_onclick;
};

