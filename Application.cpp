#include "Application.h"

//public


Application::Application()
	: title("Photo Editor")
{

	GUIManager::initializeAssests();
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
			//case sf::Event::MouseMoved:
			//	std::cout << sf::Mouse::getPosition().x << " " << sf::Mouse::getPosition().y << std::endl;
		}

		guiManager.updateAll(ev);
		imageManager.update(ev);
		window->setFramerateLimit(60);
	}

}

void Application::update()
{
	pollEvents();

}

void Application::render()
{
	window->clear(sf::Color(41, 33, 89));
	guiManager.renderAll(*window);
	imageManager.displayImage(*window);
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
	auto topBar = std::make_unique<Bar>(0.0f, 0.0f, constants::NAVIGATION_BAR_WIDTH, constants::NAVIGATION_BAR_HEIGHT, sf::Color(28, 91, 161));//need to fix 
	guiManager.addElement(std::move(topBar));

	//adding a buttons

	auto openFileButton = std::make_unique<Button>(50.0f, 50.0f, 100.0f, 100.0f, "selectFile", [this]() {
		this->imageManager.loadImage(openFile());
		std::cout << "Open file" << std::endl; }, true);
	guiManager.addElement(std::move(openFileButton));

	auto saveFileButton = std::make_unique<Button>(200.0f, 50.0f, 100.0f, 100.0f, "saveFile", [this]() {
		this->imageManager.saveImage();
		std::cout << "Save file" << std::endl; }, true);
	guiManager.addElement(std::move(saveFileButton));


}

