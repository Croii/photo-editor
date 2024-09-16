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


class Application
{
public:
	Application();
	~Application();

	const bool running() const;

	void pollEvents();
	void update();
	void render();


private:

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	const std::string title;

	GUIManager guiManager;
	ImageManager imageManager;

	//design 
	void initGUI();
	void initVariables();
	void initWindow();
};

