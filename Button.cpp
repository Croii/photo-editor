#include "Button.h"


Button::Button(float pozX, float pozY, float width, float height, sf::Color color, std::function<void()> onclick, bool isVisible) : GUIElement(isVisible), m_boundingBox({ width,height }), m_onclick(onclick)
{
	m_boundingBox.setPosition({ pozX,pozY });
	m_boundingBox.setFillColor(color);

}

Button::Button(float pozX, float pozY, float width, float height, std::string asset, std::function<void()> onclick, bool isVisible) : GUIElement(isVisible), m_boundingBox({ width,height }), m_onclick(onclick)
{
	m_boundingBox.setPosition({ pozX,pozY });
	const auto texture = GUIManager::getAsset(asset);
	m_boundingBox.setTexture(&(*texture));
	std::cout << m_boundingBox.getTexture()->getSize().x << " " << m_boundingBox.getTexture()->getSize().y << std::endl;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(m_boundingBox);
}

void Button::update(sf::Event& ev)
{
	if (ev.type == sf::Event::MouseButtonReleased)
	{

		if (isHovered({ static_cast<float>(ev.mouseButton.x), static_cast<float>(ev.mouseButton.y) }))
		{
			m_onclick();
		}
	}
}

bool Button::isHovered(const sf::Vector2f& mousePos) const
{

	return m_boundingBox.getGlobalBounds().contains(mousePos);
}


