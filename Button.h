#pragma once
#include "GUIElement.h"

#include <functional>

class Button :
	public GUIElement
{
public:
	Button(float pozX, float pozY, float width, float height, sf::Color color, std::function<void()>, bool isVisible = true);
	~Button() = default;

	void render(sf::RenderTarget& target);
	void update(sf::Event& ev);

	bool isHovered(const sf::Vector2f& mousePos);

private:
	sf::RectangleShape boundingBox;
	std::function<void()> onclick;
};

