#include "Application.h"

//public


Application::Application()
	: title("Photo Editor"), imageManager(openFileDialog())
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

std::string Application::openFileDialog()
{

	OPENFILENAMEA ofn;       // Common dialog box structure (A for ANSI version)
	char szFile[260];        // Buffer for file name (char for narrow chars)
	HWND hwnd = NULL;        // Owner window (can be NULL)

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';  // Initialize buffer to empty string
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Image Files\0*.jpg;*.jpeg;*.png;*.bmp;*.gif;*.tiff\0";  // Narrow string
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box
	if (GetOpenFileNameA(&ofn) == TRUE) {
		// Return the narrow string file path as std::string
		return std::string(ofn.lpstrFile);
	}
	else {
		// Handle cancellation or error
		return std::string();
	}

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
	auto topBar = std::make_unique<Bar>(0.0f, 0.0f, constants::NAVIGATION_BAR_WIDTH, constants::NAVIGATION_BAR_HEIGHT, sf::Color::Red);//need to fix 
	guiManager.addElement(std::move(topBar));

	//adding a buttons

	auto openFileButton = std::make_unique<Button>(50, 50, 100.0f, 100.0f, sf::Color::Black, []() {std::cout << "Open file" << std::endl; }, true);
	guiManager.addElement(std::move(openFileButton));


}

