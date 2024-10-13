#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

class ImageLoader
{
public:
	std::unique_ptr<sf::Image> loadImage(const std::string& path);
	bool saveImage(const sf::Image& image, const std::string& path) const;

private:
};

