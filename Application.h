#pragma once
#include <filesystem>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>	


#include "Bar.h"
#include "Button.h"
#include "Constants.h"
#include "GUIManager.h"
#include "ImageManager.h"
#include "RotateImageCommand.h"
#include "GrayscaleCommand.h"
#include "BlurCommand.h"

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

