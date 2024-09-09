#pragma once
#include <SFML/Graphics.hpp>


class GUIElement
{
public:
	GUIElement(bool isVisible);
	virtual ~GUIElement() = default;

	virtual void render(sf::RenderTarget& target) = 0;
	virtual void update() = 0;

	virtual bool isHovered(const sf::Vector2f& mousePos) = 0;

	bool isVisible() const;



protected:
	bool visible;

};

