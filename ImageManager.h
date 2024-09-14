#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"


#include <string>
#include <iostream>


class ImageManager
{
public:
	ImageManager(const std::string path);
	~ImageManager() = default;
	void displayImage(sf::RenderWindow& window) const;
	void update(const sf::Event& event);

private:

	void zoomUp();
	void zoomDown();
	void updateScale();


	float scale;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	void loadImage(const std::string& path);

};