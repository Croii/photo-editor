#pragma once
#include <SFML/Graphics.hpp>


class GUIElement : public sf::Drawable
{
public:
	GUIElement(bool isVisible);
	virtual ~GUIElement() = default;

	//	virtual void render(sf::RenderTarget& target) = 0;
	virtual void update(sf::Event& ev) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
	virtual bool isHovered(const sf::Vector2f& mousePos) = 0;


	bool isVisible() const;

protected:
	bool m_visible;

};

