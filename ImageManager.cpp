#include "ImageManager.h"

ImageManager::ImageManager(const std::string path)
{
	loadImage(path);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	//display the image in the middle of the canvas


	float scale = std::min(static_cast<float>(constants::CANVAS_HEIGHT) / texture.getSize().y,
		static_cast<float>(constants::CANVAS_WIDTH) / texture.getSize().x);
	if (texture.getSize().x > constants::CANVAS_HEIGHT || texture.getSize().y > constants::CANVAS_WIDTH)
	{
		sprite.setScale(scale, scale);
		sprite.setPosition(0.0f + constants::CANVAS_X + constants::CANVAS_WIDTH / 2 - texture.getSize().x / 2 * scale,
			0.0f + constants::CANVAS_Y + constants::CANVAS_HEIGHT / 2 - texture.getSize().y / 2 * scale);
	}
	else
	{
		sprite.setPosition(0.0f + constants::CANVAS_X + constants::CANVAS_WIDTH / 2 - texture.getSize().x / 2,
			0.0f + constants::CANVAS_Y + constants::CANVAS_HEIGHT / 2 - texture.getSize().y / 2);
	}

	std::cout << scale << '\n';

}


void ImageManager::displayImage(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

void ImageManager::loadImage(const std::string& path)
{
	if (!image.loadFromFile(path))
	{
		std::cout << "Error loading the file" << std::endl;
	}
	else
	{
		std::cout << "The file was loaded succesfully" << std::endl;
	}
}
