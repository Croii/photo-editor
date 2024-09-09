#include "Application.h"

//public

Application::Application()
	: title("Photo Editor")
{
	initVariables();
	initWindow();
	initGUI();
	//initTopBar();
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

		guiManager.updateAll();

	}

}

void Application::update()
{
	pollEvents();

}

void Application::render()
{
	window->clear(sf::Color::Cyan);
	guiManager.renderAll(*window);

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

void Application::initGUI()
{
	//adding a top bar
	auto topBar = std::make_unique<Bar>(0.0f, 0.0f, videoMode.width, videoMode.height / 5.0f, sf::Color::Red, true);//need to fix 
	guiManager.addElement(std::move(topBar));

}


//void Application::initTopBar()
//{
//	topBar.setSize(sf::Vector2f(static_cast<float>(videoMode.width), 200.0f)); // Set size of top bar
//	topBar.setFillColor(sf::Color::Blue); // Set color of top bar
//	topBar.setPosition(0.0f, 0.0f); // Set position of top bar
//}
