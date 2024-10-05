#pragma once
#include "GUIElement.h"
#include "SFML/Graphics.hpp"

#include <cstdint>



class Bar : public GUIElement
{
public:
	Bar(float pozX, float pozY, float width, float height, sf::Color color, bool isVisible = true);
	~Bar() = default;


	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(sf::Event& event) override;
	bool isHovered(const sf::Vector2f& mousePos) override;

private:
	sf::RectangleShape m_boundingBox;

};