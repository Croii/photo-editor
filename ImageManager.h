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


private:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	void loadImage(const std::string& path);

};