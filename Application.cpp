#include "Application.h"

//public


Application::Application()
	: title("Photo Editor")
{
	initVariables();
	initWindow();
	initGUI();
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
			//		case sf::Event::MouseMoved:
				//		std::cout << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << std::endl;
		}

		guiManager.updateAll(ev);


		window->setFramerateLimit(60);
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
	auto topBar = std::make_unique<Bar>(0.0f, 0.0f, videoMode.width, videoMode.height / 5.0f, sf::Color::Red);//need to fix 
	guiManager.addElement(std::move(topBar));

	//adding a buttons

	/*auto button2 = std::make_unique<Button>(50, 50, 100.0f, 100.0f, sf::Color::Black, true);
	guiManager.addElement(std::move(button2));

	auto button3 = std::make_unique<Button>(250, 50, 100.0f, 100.0f, sf::Color::Black);
	guiManager.addElement(std::move(button3));

	auto button4 = std::make_unique<Button>(450, 50, 100.0f, 100.0f, sf::Color::Black);
	guiManager.addElement(std::move(button4));

	auto button5 = std::make_unique<Button>(650, 50, 100.0f, 100.0f, sf::Color::Black);
	guiManager.addElement(std::move(button5));*/
	//basic 
	const int buttons_count = 9;
	for (int i = 0; i < buttons_count; i++)
	{
		auto button = std::make_unique<Button>(50 + 200 * i, 50, 100.0f, 100.0f, sf::Color::Black, [i]() {std::cout << i << std::endl; }, true);
		guiManager.addElement(std::move(button));
	}


}


//void Application::initTopBar()
//{
//	topBar.setSize(sf::Vector2f(static_cast<float>(videoMode.width), 200.0f)); // Set size of top bar
//	topBar.setFillColor(sf::Color::Blue); // Set color of top bar
//	topBar.setPosition(0.0f, 0.0f); // Set position of top bar
//}
