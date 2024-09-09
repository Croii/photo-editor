#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>


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

	//design 

	sf::RectangleShape topBar;

	void initTopBar();

	void initVariables();
	void initWindow();
};

