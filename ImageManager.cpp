#include "ImageManager.h"


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
		else if (event.key.code == sf::Keyboard::S)
			saveImage();
	}

}

void ImageManager::saveImage()
{
	if (image.getSize().x == 0 || image.getSize().y == 0)
	{
		std::cout << "No image to save" << std::endl;
		return;
	}
	std::string path = saveFile();
	std::cout << path << std::endl;
	path += "\\image.png";
	image.saveToFile(path);
}

void ImageManager::zoomUp()
{
	scale = scale * 1.1f;
	updateScale();
}

void ImageManager::zoomDown()
{
	scale = scale * 0.9f;
	updateScale();
}

void ImageManager::updateScale()
{
	sprite.setScale(scale, scale);
	sprite.setPosition(0.0f + constants::CANVAS_X + constants::CANVAS_WIDTH / 2.0f - texture.getSize().x / 2.0f * scale,
		0.0f + constants::CANVAS_Y + constants::CANVAS_HEIGHT / 2.0f - texture.getSize().y / 2.0f * scale);
}

void ImageManager::loadImage(const std::string& path)
{
	image = sf::Image();

	if (!image.loadFromFile(path))
	{
		std::cout << "Error loading the file" << std::endl;
	}
	else
	{
		std::cout << "The file was loaded succesfully" << std::endl;
	}

	texture = sf::Texture();
	sprite = sf::Sprite();

	scale = 1.0f;
	texture.loadFromImage(image);
	sprite.setScale(scale, scale);
	sprite.setTexture(texture);
	if (texture.getSize().x > constants::CANVAS_HEIGHT || texture.getSize().y > constants::CANVAS_WIDTH)
	{
		scale = std::min(static_cast<float>(constants::CANVAS_HEIGHT) / texture.getSize().y,
			static_cast<float>(constants::CANVAS_WIDTH) / texture.getSize().x);
	}

	sprite.setScale(scale, scale);
	sprite.setPosition(0.0f + constants::CANVAS_X + constants::CANVAS_WIDTH / 2 - texture.getSize().x / 2 * scale,
		0.0f + constants::CANVAS_Y + constants::CANVAS_HEIGHT / 2 - texture.getSize().y / 2 * scale);
	std::cout << sprite.getTexture()->getSize().x << " " << sprite.getTexture()->getSize().y << std::endl;

	std::cout << sprite.getGlobalBounds().width << " " << sprite.getGlobalBounds().height << std::endl;

}
