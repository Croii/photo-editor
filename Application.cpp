#include "Application.h"

//public


Application::Application()
	: M_TITLE("Photo Editor")
{

	GUIManager::initializeAssests();
	initVariables();
	initWindow();
	initGUI();
}

Application::~Application()
{

}

const bool Application::running() const
{
	return m_window->isOpen();
}

void Application::pollEvents()
{

	while (m_window->pollEvent(m_event))
	{
		switch (m_event.type)
		{
		case sf::Event::Closed:
			m_window->close();
			break;
		case sf::Event::KeyPressed:
			if (m_event.key.code == sf::Keyboard::Escape)
				m_window->close();
			else if (m_event.key.code == sf::Keyboard::Z)
			{
				m_imageManager.undo();
			}
			else if (m_event.key.code == sf::Keyboard::R)
			{
				m_imageManager.redo();
			}
			break;

		}

		m_guiManager.updateAll(m_event);
		m_imageManager.update(m_event);
		m_window->setFramerateLimit(60);
	}

}

void Application::update()
{
	pollEvents();

}

void Application::draw()
{
	m_window->clear(sf::Color(41, 33, 89));
	m_imageManager.draw(*m_window, sf::RenderStates::Default);
	m_guiManager.drawAll(*m_window);
	m_window->display();
}
//private


void Application::initVariables()
{
	m_window = nullptr;
}

void Application::initWindow()
{
	m_videoMode = sf::VideoMode::getDesktopMode();
	m_window = std::make_unique<sf::RenderWindow>(m_videoMode, M_TITLE, sf::Style::Fullscreen);
}

void Application::loadImage()
{
	std::string path = openFile();
	if (path.empty())
	{
		std::cout << "No file selected";
		return;
	}

	if (!m_imageManager.loadImage(path))
	{
		std::cout << "Error loading the file" << std::endl;
		return;
	}

	std::cout << "File loaded successfully" << std::endl;


}

void Application::saveImage()
{
	std::string path = saveFile();
	if (path.empty())
	{
		std::cout << "No directory to save selected" << std::endl;
		return;
	}

	if (!m_imageManager.saveImage(path))
	{
		std::cout << "Error saving the file" << std::endl;
		return;
	}
	std::cout << "File save successfully" << std::endl;

}

void Application::rotate(Orientation orientation)
{

	m_imageManager.rotate(orientation);
}

void Application::grayScale()
{
	m_imageManager.grayScale();
}

void Application::initGUI()
{
	//adding a top bar
	auto topBar = std::make_unique<Bar>(0.0f, 0.0f, constants::NAVIGATION_BAR_WIDTH, constants::NAVIGATION_BAR_HEIGHT, sf::Color(28, 91, 161));//need to fix 
	m_guiManager.addElement(std::move(topBar));

	//adding a buttons

	auto openFileButton = std::make_unique<Button>(50.0f, 50.0f, 100.0f, 100.0f, "selectFile", [this]() {
		this->loadImage();
		}, true);
	m_guiManager.addElement(std::move(openFileButton));

	auto saveFileButton = std::make_unique<Button>(200.0f, 50.0f, 100.0f, 100.0f, "saveFile", [this]() {
		this->saveImage();
		}, true);
	m_guiManager.addElement(std::move(saveFileButton));

	auto rotateLeftButton = std::make_unique<Button>(350.0f, 50.0f, 100.0f, 100.0f, "rotateLeft", [this]() {
		this->rotate(Orientation::LEFT);
		}, true);
	m_guiManager.addElement(std::move(rotateLeftButton));

	auto rotateRightButton = std::make_unique<Button>(500.0f, 50.0f, 100.0f, 100.0f, "rotateRight", [this]() {
		this->rotate(Orientation::RIGHT);
		}, true);
	m_guiManager.addElement(std::move(rotateRightButton));

	auto grayScaleButton = std::make_unique<Button>(650.0f, 50.0f, 100.0f, 100.0f, "grayScale", [this]() {
		this->grayScale();
		}, true);
	m_guiManager.addElement(std::move(grayScaleButton));
}

