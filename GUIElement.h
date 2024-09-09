#pragma once
#include <SFML/Graphics.hpp>


class GUIElement
{
public:
	GUIElement(sf::RectangleShape shape, bool isVisible);
	virtual ~GUIElement() = default;

	virtual void render(sf::RenderTarget& target) = 0;
	virtual void update() = 0;

	virtual bool isHovered(const sf::Vector2f& mousePos) = 0;




protected:
	sf::RectangleShape shape;
	bool isVisible;

};

