#include "Application.h"


Application::Application()
	: M_TITLE("Photo Editor")
{

	GUIManager::initializeAssests();
	m_initVariables();
	m_initWindow();
	m_initGUI();
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


void Application::m_initVariables()
{
	m_window = nullptr;
}

void Application::m_initWindow()
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
	m_commandManager.clear();

}

void Application::saveImage() const
{
	if (m_imageManager.getImage() == nullptr)
	{
		std::cout << "No image to save" << std::endl;
		return;
	}
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
	if (m_imageManager.getImage() == nullptr)
	{
		std::cout << "No image to modify" << std::endl;
		return;
	}
	std::unique_ptr <ICommand> command = std::make_unique<RotateImageCommand>(m_imageManager, orientation);

	m_commandManager.executeCommand(std::move(command));

}

void Application::grayScale()
{
	if (m_imageManager.getImage() == nullptr)
	{
		std::cout << "No image to modify" << std::endl;
		return;
	}
	std::unique_ptr<ICommand> command = std::make_unique<GrayscaleCommand>(m_imageManager, m_imageManager.getImage());
	m_commandManager.executeCommand(std::move(command));
}

void Application::blur()
{
	if (m_imageManager.getImage() == nullptr)
	{
		std::cout << "No image to modify" << std::endl;
		return;
	}
	std::unique_ptr<ICommand> command = std::make_unique < BlurCommand>(m_imageManager, m_imageManager.getImage());
	m_commandManager.executeCommand(std::move(command));
}

void Application::addButton(const std::string& text, const std::function<void()>& onClick, const sf::Vector2f& position, const sf::Vector2f& size)
{

	auto button = std::make_unique<Button>(position.x, position.y, size.x, size.y, text, onClick, true);
	m_guiManager.addElement(std::move(button));
}

void Application::addBar(sf::Color color, const std::function<void(float)>& onValueChanged, const sf::Vector2f& position, const sf::Vector2f& size)
{
	auto bar = std::make_unique<Bar>(position.x, position.y, size.x, size.y, color);
	m_guiManager.addElement(std::move(bar));
}


void Application::m_initGUI()
{
	addBar(sf::Color(28, 91, 161), [](float) {}, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(constants::NAVIGATION_BAR_WIDTH, constants::NAVIGATION_BAR_HEIGHT));

	addButton("selectFile", [this]() {
		this->loadImage();
		}, sf::Vector2f(50.0f, 50.0f), sf::Vector2f(100.0f, 100.0f));

	addButton("saveFile", [this]() {
		this->saveImage();
		}, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(100.0f, 100.0f));

	addButton("rotateLeft", [this]() {
		this->rotate(Orientation::LEFT);
		}, sf::Vector2f(350.0f, 50.0f), sf::Vector2f(100.0f, 100.0f));

	addButton("rotateRight", [this]() {
		this->rotate(Orientation::RIGHT);
		}, sf::Vector2f(500.0f, 50.0f), sf::Vector2f(100.0f, 100.0f));

	addButton("grayScale", [this]() {
		this->grayScale();
		}, sf::Vector2f(650.0f, 50.0f), sf::Vector2f(100.0f, 100.0f));

	addButton("blur", [this]() {
		this->blur();
		}, sf::Vector2f(800.0f, 50.0f), sf::Vector2f(100.0f, 100.0f));

	addButton("undo", [this]() {
		this->m_commandManager.undo();
		}, sf::Vector2f(950.0f, 50.0f), sf::Vector2f(100.0f, 100.0f));

	addButton("redo", [this]() {
		this->m_commandManager.redo();
		}, sf::Vector2f(1100.0f, 50.0f), sf::Vector2f(100.0f, 100.0f));

	addButton("zoomIn", [this]() {
		this->m_imageManager.zoomIn();
		}, sf::Vector2f(1250.0f, 50.0f), sf::Vector2f(100.0f, 100.0f));

	addButton("zoomOut", [this]() {
		this->m_imageManager.zoomOut();
		}, sf::Vector2f(1400.0f, 50.0f), sf::Vector2f(100.0f, 100.0f));

}