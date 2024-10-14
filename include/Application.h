#pragma once
#include <filesystem>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>	


//#include "Bar.h"
#include "../include/GUI/Bar.h"
#include "../include/GUI/Button.h"
#include "Constants.h"
#include "GUIManager.h"
#include "ImageManager.h"
#include "../include/Command/RotateImageCommand.h"
#include "../include/Command/GrayscaleCommand.h"
#include "../include/Command/BlurCommand.h"

class Application
{
public:
	Application();
	~Application();

	const bool running() const;

	void pollEvents();
	void update();
	void draw();

	void loadImage();
	void saveImage() const;
	void rotate(Orientation orientation);
	void grayScale();
	void blur();

private:
	void addButton(const std::string& text, const std::function<void()>& onClick, const sf::Vector2f& position, const sf::Vector2f& size);
	void addBar(sf::Color color, const std::function<void(float)>& onValueChanged, const sf::Vector2f& position, const sf::Vector2f& size);
	
	
	std::unique_ptr<sf::RenderWindow> m_window;
	sf::VideoMode m_videoMode;
	sf::Event m_event;

	const std::string M_TITLE;

	GUIManager m_guiManager;
	ImageManager m_imageManager;
	CommandManager m_commandManager;

	//design 
	void m_initGUI();
	void m_initVariables();
	void m_initWindow();
};