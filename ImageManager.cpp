#include "ImageManager.h"

ImageManager::ImageManager(const std::string path)
{
	scale = 1;
	loadImage(path);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	//display the image in the middle of the canvas


	if (texture.getSize().x > constants::CANVAS_HEIGHT || texture.getSize().y > constants::CANVAS_WIDTH)
	{
		scale = std::min(static_cast<float>(constants::CANVAS_HEIGHT) / texture.getSize().y,
			static_cast<float>(constants::CANVAS_WIDTH) / texture.getSize().x);
	}

	sprite.setScale(scale, scale);
	sprite.setPosition(0.0f + constants::CANVAS_X + constants::CANVAS_WIDTH / 2 - texture.getSize().x / 2 * scale,
		0.0f + constants::CANVAS_Y + constants::CANVAS_HEIGHT / 2 - texture.getSize().y / 2 * scale);

	std::cout << scale << '\n';

}


void ImageManager::displayImage(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

void ImageManager::update(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::A)
			zoomDown();
		else if (event.key.code == sf::Keyboard::B)
			zoomUp();
	}

}

void ImageManager::zoomUp()
{
	scale = scale * 1.1;
	updateScale();
}

void ImageManager::zoomDown()
{
	scale = scale * 0.9;
	updateScale();
}

void ImageManager::updateScale()
{
	sprite.setScale(scale, scale);
	sprite.setPosition(0.0f + constants::CANVAS_X + constants::CANVAS_WIDTH / 2 - texture.getSize().x / 2 * scale,
		0.0f + constants::CANVAS_Y + constants::CANVAS_HEIGHT / 2 - texture.getSize().y / 2 * scale);
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
