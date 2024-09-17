#include "Bar.h"

Bar::Bar(float pozX, float pozY, float width, float height, sf::Color color, bool isVisible) : GUIElement(isVisible), boundingBox({ width,height })
{
	boundingBox.setPosition({ pozX,pozY });
	boundingBox.setFillColor(color);

}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states)  const
{
	target.draw(boundingBox);
}

void Bar::update(sf::Event& ev)
{
}

bool Bar::isHovered(const sf::Vector2f& mousePos)
{
	return false;
}
