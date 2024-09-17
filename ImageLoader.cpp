#include "ImageLoader.h"

std::unique_ptr<sf::Image> ImageLoader::loadImage(const std::string& path)
{
	std::unique_ptr<sf::Image> image = std::make_unique<sf::Image>();
	if (!image->loadFromFile(path)) {

		return nullptr;
	}
	return std::move(image);
}

bool ImageLoader::saveImage(const sf::Image& image, const std::string& path)
{
	return image.saveToFile(path + "\\image.png");
}
