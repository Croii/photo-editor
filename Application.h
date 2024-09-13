#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>	
#include <iostream>
#include <filesystem>

#include <windows.h>
#include <commdlg.h>

#include "GUIManager.h"
#include "Bar.h"
#include "Button.h"
#include "ImageManager.h"
#include "Constants.h"


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

	std::string openFileDialog();
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

