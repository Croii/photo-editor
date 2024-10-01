#pragma once
#include "CommandManger.h"
#include "Constants.h"
#include "ImageLoader.h"

#include "SFML/Graphics.hpp"
#include "Utility.h"

#include <cstdint>
#include <iostream>
#include <string>
//#include "RotateImageCommand.h"

class RotateImageCommand;

class ImageManager
{
public:
	ImageManager();
	~ImageManager() = default;
	void draw(sf::RenderWindow& window, sf::RenderStates state) const;
	void update(const sf::Event& event);

	bool saveImage(const std::string& path) const;
	bool loadImage(const std::string& path);
	void rotate(Orientation orientation);

	void undo();
	void redo();
	void executeCommand(std::unique_ptr <ICommand> command);


	void rotateLeft();
	void rotateRight();
private:

	void m_imageFitting();
	void zoomUp();
	void zoomDown();
	void updateScale();

	float m_scale;
	std::unique_ptr <ImageLoader> m_imageLoader;
	std::unique_ptr<sf::Image> m_image;
	CommandManger m_commandManager;
	sf::Texture m_texture;
	sf::Sprite m_sprite;



};