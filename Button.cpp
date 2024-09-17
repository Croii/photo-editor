#include "Button.h"


Button::Button(float pozX, float pozY, float width, float height, sf::Color color, std::function<void()> onclick, bool isVisible) : GUIElement(isVisible), boundingBox({ width,height }), onclick(onclick)
{
	boundingBox.setPosition({ pozX,pozY });
	boundingBox.setFillColor(color);

}

Button::Button(float pozX, float pozY, float width, float height, std::string asset, std::function<void()> onclick, bool isVisible) : GUIElement(isVisible), boundingBox({ width,height }), onclick(onclick)
{
	boundingBox.setPosition({ pozX,pozY });
	const auto texture = GUIManager::getAsset(asset);
	boundingBox.setTexture(&(*texture));
	std::cout << boundingBox.getTexture()->getSize().x << " " << boundingBox.getTexture()->getSize().y << std::endl;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates state) const
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
		}
	}
}

bool Button::isHovered(const sf::Vector2f& mousePos)
{

	return boundingBox.getGlobalBounds().contains(mousePos);
}


