#pragma once
#include "Constants.h"
#include "SFML/Graphics.hpp"
#include "Utility.h"

#include <iostream>
#include <string>


class ImageManager
{
public:
	ImageManager() = default;
	~ImageManager() = default;
	void displayImage(sf::RenderWindow& window) const;
	void update(const sf::Event& event);
	void saveImage();
	void loadImage(const std::string& path);

private:

	void zoomUp();
	void zoomDown();
	void updateScale();


	float scale;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

};