#include "Bar.h"

Bar::Bar(float pozX, float pozY, float width, float height, sf::Color color, bool isVisible = true) : GUIElement(isVisible), boundingBox({ width,height })
{
	boundingBox.setOrigin({ pozX,pozY });
	boundingBox.setFillColor(color);

}

void Bar::render(sf::RenderTarget& target)
{
	target.draw(boundingBox);
}

void Bar::update()
{
}

bool Bar::isHovered(const sf::Vector2f& mousePos)
{
	return false;
}
