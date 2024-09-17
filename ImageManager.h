#pragma once
#include "ImageLoader.h"
#include "Constants.h"
#include "SFML/Graphics.hpp"
#include "Utility.h"

#include <iostream>
#include <string>


class ImageManager
{
public:
	ImageManager();
	~ImageManager() = default;
	void draw(sf::RenderWindow& window, sf::RenderStates state) const;
	void update(const sf::Event& event);

	bool saveImage(const std::string& path) const;
	bool loadImage(const std::string& path);
	void rotate(float orientation);

private:

	void m_imageFitting();
	void zoomUp();
	void zoomDown();
	void updateScale();

	float m_scale;
	std::unique_ptr < ImageLoader> m_imageLoader;
	std::unique_ptr<sf::Image> m_image;
	sf::Texture m_texture;
	sf::Sprite m_sprite;


};