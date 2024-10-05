#include "ImageManager.h"
#include "RotateImageCommand.h"

ImageManager::ImageManager() : m_imageLoader(std::unique_ptr<ImageLoader>()), m_scale(1.0f)
{

}

void ImageManager::draw(sf::RenderWindow& window, sf::RenderStates) const
{
	window.draw(m_sprite);
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

bool ImageManager::saveImage(const std::string& path) const
{
	if (m_image == nullptr || m_image->getSize().x == 0 || m_image->getSize().y == 0 || path.size() == 0)
	{
		std::cout << "No image to save" << std::endl;
		return 0;
	}
	return m_imageLoader->saveImage(m_sprite.getTexture()->copyToImage(), path);

	//return m_imageLoader->saveImage(*m_image, path);
}

void ImageManager::m_imageFitting()
{
}

void ImageManager::zoomUp()
{
	m_scale = m_scale * 1.1f;
	updateScale();
}

void ImageManager::zoomDown()
{
	m_scale = m_scale * 0.9f;
	updateScale();
}

void ImageManager::updateScale()
{
	if (m_texture.getSize().x > constants::CANVAS_HEIGHT || m_texture.getSize().y > constants::CANVAS_WIDTH)
	{
		m_scale = std::min(static_cast<float>(constants::CANVAS_HEIGHT) / m_texture.getSize().y,
			static_cast<float>(constants::CANVAS_WIDTH) / m_texture.getSize().x);
	}

	m_sprite.setScale(m_scale, m_scale);
	m_sprite.setPosition(0.0f + constants::CANVAS_X + constants::CANVAS_WIDTH / 2 - m_texture.getSize().x / 2 * m_scale,
		0.0f + constants::CANVAS_Y + constants::CANVAS_HEIGHT / 2 - m_texture.getSize().y / 2 * m_scale);
}

void ImageManager::rotateLeft()
{
	int oldWidth = m_image->getSize().x;
	int oldHeight = m_image->getSize().y;
	std::unique_ptr<sf::Image> newImage = std::make_unique<sf::Image>();
	newImage->create(oldHeight, oldWidth);

	for (int y = 0; y < oldHeight; y++)
		for (int x = 0; x < oldWidth; x++)
		{
			newImage->setPixel(y, (oldWidth - x - 1), m_image->getPixel(x, y));
		}
	m_image.swap(newImage);
	m_texture.loadFromImage(*m_image);
	m_sprite.setTexture(m_texture, true);
	newImage = nullptr;
	updateScale();

}

void ImageManager::rotateRight()
{
	int oldWidth = m_image->getSize().x;
	int oldHeight = m_image->getSize().y;
	std::unique_ptr<sf::Image> newImage = std::make_unique<sf::Image>();
	newImage->create(oldHeight, oldWidth);

	for (int y = 0; y < oldHeight; y++)
		for (int x = 0; x < oldWidth; x++)
		{
			newImage->setPixel((oldHeight - y - 1), x, m_image->getPixel(x, y));
		}
	m_image.swap(newImage);
	m_texture.loadFromImage(*m_image);
	m_sprite.setTexture(m_texture, true);
	newImage = nullptr;
	updateScale();

}

void ImageManager::grayScale()
{
	int width = m_image->getSize().x;
	int height = m_image->getSize().y;

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			int red = m_image->getPixel(i, j).r;
			int green = m_image->getPixel(i, j).g;
			int blue = m_image->getPixel(i, j).b;

			red = static_cast<int>(red * 0.299);
			green = static_cast<int>(green * 0.299);
			blue = static_cast<int>(blue * 0.299);
			m_image->setPixel(i, j, sf::Color(red,green,blue));
		}
	m_texture.loadFromImage(*m_image);
	m_sprite.setTexture(m_texture);
}

std::unique_ptr<sf::Image> ImageManager::getImage() const
{
	int width = m_image->getSize().x;
	int height = m_image->getSize().y;
	std::unique_ptr<sf::Image> imageCopy = std::make_unique<sf::Image>();
	imageCopy->create(width, height);
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			imageCopy->setPixel(i,j ,m_image->getPixel(i,j));
		}
	return imageCopy;
}

bool ImageManager::loadImage(sf::Image& image)
{
	if (image.getSize().x == 0 || image.getSize().y == 0)
		return 0;
	m_image = std::make_unique<sf::Image>(image);
	m_texture.loadFromImage(*m_image);
	m_sprite.setScale(m_scale, m_scale);
	m_sprite.setTexture(m_texture);
	updateScale();

}

bool ImageManager::loadImage(std::unique_ptr<sf::Image> image)
{
	if (image == nullptr)
		return false;
	m_image = nullptr;
	m_image = std::move(image);
	m_texture.loadFromImage(*m_image);
	m_sprite.setScale(m_scale, m_scale);
	m_sprite.setTexture(m_texture);

	updateScale();
	return true;
}

void ImageManager::rotate(Orientation orientation)
{
	if (orientation == Orientation::LEFT)
		rotateLeft();
	else if (orientation == Orientation::RIGHT)
		rotateRight();
}

bool ImageManager::loadImage(const std::string& path)
{
	auto loadedImage = m_imageLoader.get()->loadImage(path);
	if (loadedImage == nullptr)
	{
		return false;
	}


	m_scale = 1.0f;
	m_image = std::move(loadedImage);
	m_texture.loadFromImage(*m_image);
	m_sprite.setScale(m_scale, m_scale);
	m_sprite.setTexture(m_texture);

	updateScale();
	return true;
}

//void ImageManager::rotate(Orientation orientation)
//{
//	if (m_image == nullptr)
//		return;
//	auto command = std::make_unique<RotateImageCommand>(*this, orientation);
//	m_commandManager.executeCommand(std::move(command));
//
//
//}


