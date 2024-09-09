#include "Application.h"

//public

Application::Application()
	: title("Photo Editor")
{
	initVariables();
	initWindow();
	initTopBar();
}

Application::~Application()
{
	delete window;
}

const bool Application::running() const
{
	return window->isOpen();
}

void Application::pollEvents()
{
	while (window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				window->close();
			break;
		}
	}

}

void Application::update()
{
	pollEvents();

}

void Application::render()
{
	window->clear(sf::Color::Cyan);

	window->draw(topBar);

	window->display();
}



//private


void Application::initVariables()
{
	window = nullptr;
}

void Application::initWindow()
{
	videoMode = sf::VideoMode::getDesktopMode();
	window = new sf::RenderWindow(videoMode, title, sf::Style::Fullscreen);
}

void Application::initTopBar()
{
	topBar.setSize(sf::Vector2f(static_cast<float>(videoMode.width), 200.0f)); // Set size of top bar
	topBar.setFillColor(sf::Color::Blue); // Set color of top bar
	topBar.setPosition(0.0f, 0.0f); // Set position of top bar
}
