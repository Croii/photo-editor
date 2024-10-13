#include "ImageLoader.h"

std::unique_ptr<sf::Image> ImageLoader::loadImage(const std::string& path)
{
	std::unique_ptr<sf::Image> image = std::make_unique<sf::Image>();
	if (!image->loadFromFile(path)) {

		return nullptr;
	}
	return image;
}

//save image to the specified path
bool ImageLoader::saveImage(const sf::Image& image, const std::string& path) const
{
	return image.saveToFile(path + "\\image.png");
}
