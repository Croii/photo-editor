#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>	
#include <iostream>


#include "GUIManager.h"
#include "Bar.h"
#include "Button.h"

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


	//design 
	void initGUI();
	void initVariables();
	void initWindow();
};

