#include "Button.h"

#include <iostream>

Button::Button(float pozX, float pozY, float width, float height, sf::Color color, std::function<void()> onclick, bool isVisible) : GUIElement(isVisible), boundingBox({ width,height }), onclick(onclick)
{
	boundingBox.setPosition({ pozX,pozY });
	boundingBox.setFillColor(color);
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(boundingBox);
}

void Button::update(sf::Event& ev)
{
	if (ev.type == sf::Event::MouseButtonReleased)
	{

		if (isHovered({ static_cast<float>(ev.mouseButton.x), static_cast<float>(ev.mouseButton.y) }))
		{
			onclick();
			std::cout << std::endl;
			if (boundingBox.getFillColor() == sf::Color::Black)
				boundingBox.setFillColor(sf::Color::Green);
			else
				boundingBox.setFillColor(sf::Color::Black);

		}
	}
}

bool Button::isHovered(const sf::Vector2f& mousePos)
{

	return boundingBox.getGlobalBounds().contains(mousePos);
}


