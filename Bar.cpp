#include "Bar.h"

Bar::Bar(float pozX, float pozY, float width, float height, sf::Color color, bool isVisible) : GUIElement(isVisible), m_boundingBox({ width,height })
{
	m_boundingBox.setPosition({ pozX,pozY });
	m_boundingBox.setFillColor(color);

}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(m_boundingBox);
}

void Bar::update(sf::Event& ev)
{
}

bool Bar::isHovered(const sf::Vector2f& mousePos) const
{
	return m_boundingBox.getGlobalBounds().contains(mousePos);
}
