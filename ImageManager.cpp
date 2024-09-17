#include "ImageManager.h"


ImageManager::ImageManager() : m_imageLoader(std::unique_ptr<ImageLoader>())
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

void ImageManager::rotate(float orientation)
{
	m_sprite.rotate(orientation);
}
