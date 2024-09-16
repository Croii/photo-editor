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

#include "Bar.h"

Bar::Bar(float pozX, float pozY, float width, float height, sf::Color color, bool isVisible) : GUIElement(isVisible), boundingBox({ width,height })
{
	boundingBox.setPosition({ pozX,pozY });
	boundingBox.setFillColor(color);

}

void Bar::render(sf::RenderTarget& target)
{
	target.draw(boundingBox);
}

void Bar::update(sf::Event& ev)
{
}

bool Bar::isHovered(const sf::Vector2f& mousePos)
{
	return false;
}
#include "Button.h"


Button::Button(float pozX, float pozY, float width, float height, sf::Color color, std::function<void()> onclick, bool isVisible) : GUIElement(isVisible), boundingBox({ width,height }), onclick(onclick)
{
	boundingBox.setPosition({ pozX,pozY });
	boundingBox.setFillColor(color);

}

Button::Button(float pozX, float pozY, float width, float height, std::string asset, std::function<void()> onclick, bool isVisible) : GUIElement(isVisible), boundingBox({ width,height }), onclick(onclick)
{
	boundingBox.setPosition({ pozX,pozY });
	const auto texture = GUIManager::getAsset(asset);
	boundingBox.setTexture(&(*texture));
	std::cout << boundingBox.getTexture()->getSize().x << " " << boundingBox.getTexture()->getSize().y << std::endl;
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(boundingBox);
}

void Button::update(sf::Event& ev)
{
	if (ev.type == sf::Event::MouseButtonReleased)
	{

		if (isHovered({ static_cast<float>(ev.mouseButton.x), static_cast<float>(ev.mouseButton.y) }))
		{
			onclick();
		}
	}
}

bool Button::isHovered(const sf::Vector2f& mousePos)
{

	return boundingBox.getGlobalBounds().contains(mousePos);
}


#include "GUIElement.h"



GUIElement::GUIElement(bool visible) : visible(visible)
{
}



bool GUIElement::isVisible() const
{
	return visible;
}
#include "GUIManager.h"

std::vector<std::string > GUIManager::assetName = { "saveFile", "selectFile" };
std::unordered_map<std::string, std::shared_ptr<sf::Texture>> GUIManager::assets;

void GUIManager::addElement(std::unique_ptr<GUIElement>&& element)
{
	guiElements[priority++] = std::move(element);
}

void GUIManager::renderAll(sf::RenderWindow& window)
{
	for (auto& [_, element] : guiElements)
	{
		if (element->isVisible())
		{
			element->render(window);
		}
	}
}

void GUIManager::updateAll(sf::Event& ev)
{
	for (auto& [_, element] : guiElements)
	{
		element->update(ev);
	}
}


void GUIManager::initializeAssests()
{
	for (auto& name : assetName)
	{
		auto texture = std::make_shared<sf::Texture>();
		if (texture->loadFromFile("Assets\\" + name + ".png")) {
			//here is the good texture
			assets.insert({ name ,texture });
		}
	}

}

std::shared_ptr<sf::Texture> GUIManager::getAsset(const std::string& name) noexcept
{
	return assets[name];
}
#include "ImageManager.h"


void ImageManager::displayImage(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

void ImageManager::update(const sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::A)
			zoomDown();
		else if (event.key.code == sf::Keyboard::B)
			zoomUp();
		else if (event.key.code == sf::Keyboard::S)
			saveImage();
	}

}

void ImageManager::saveImage()
{
	if (image.getSize().x == 0 || image.getSize().y == 0)
	{
		std::cout << "No image to save" << std::endl;
		return;
	}
	std::string path = saveFile();
	std::cout << path << std::endl;
	path += "\\image.png";
	image.saveToFile(path);
}

void ImageManager::zoomUp()
{
	scale = scale * 1.1f;
	updateScale();
}

void ImageManager::zoomDown()
{
	scale = scale * 0.9f;
	updateScale();
}

void ImageManager::updateScale()
{
	sprite.setScale(scale, scale);
	sprite.setPosition(0.0f + constants::CANVAS_X + constants::CANVAS_WIDTH / 2.0f - texture.getSize().x / 2.0f * scale,
		0.0f + constants::CANVAS_Y + constants::CANVAS_HEIGHT / 2.0f - texture.getSize().y / 2.0f * scale);
}

void ImageManager::loadImage(const std::string& path)
{
	image = sf::Image();

	if (!image.loadFromFile(path))
	{
		std::cout << "Error loading the file" << std::endl;
	}
	else
	{
		std::cout << "The file was loaded succesfully" << std::endl;
	}

	texture = sf::Texture();
	sprite = sf::Sprite();

	scale = 1.0f;
	texture.loadFromImage(image);
	sprite.setScale(scale, scale);
	sprite.setTexture(texture);
	if (texture.getSize().x > constants::CANVAS_HEIGHT || texture.getSize().y > constants::CANVAS_WIDTH)
	{
		scale = std::min(static_cast<float>(constants::CANVAS_HEIGHT) / texture.getSize().y,
			static_cast<float>(constants::CANVAS_WIDTH) / texture.getSize().x);
	}

	sprite.setScale(scale, scale);
	sprite.setPosition(0.0f + constants::CANVAS_X + constants::CANVAS_WIDTH / 2 - texture.getSize().x / 2 * scale,
		0.0f + constants::CANVAS_Y + constants::CANVAS_HEIGHT / 2 - texture.getSize().y / 2 * scale);
	std::cout << sprite.getTexture()->getSize().x << " " << sprite.getTexture()->getSize().y << std::endl;

	std::cout << sprite.getGlobalBounds().width << " " << sprite.getGlobalBounds().height << std::endl;

}
#pragma once
#include "Application.h"

#include <iostream>
#include <string>

int main()
{

	Application engine;
	while (engine.running())
	{
		//Event handling
		engine.update();
		engine.render();
	}
	return 0;
}#include "Utility.h"

std::string openFile()
{
	char szFile[260] = { 0 };
	HWND hwnd = NULL;  // Owner window (can be NULL)
	// Use the common file open dialog for file selection (ANSI version)
	const char* filter = "Image Files\0*.jpg;*.jpeg;*.png;*.bmp;*.gif;*.tiff\0";

	OPENFILENAMEA ofn;  // Common dialog box structure (A for ANSI version)

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';  // Initialize buffer to empty string
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	// Display the Open dialog box for file selection
	if (GetOpenFileNameA(&ofn) == TRUE) {
		return std::string(ofn.lpstrFile);  // Return the selected file path
	}
	return std::string();
}

std::string saveFile()
{
	char szFile[260] = { 0 };
	BROWSEINFOA bi = { 0 };
	bi.lpszTitle = "Select Folder";
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;  // Only show file system directories

	// Display the folder selection dialog (ANSI version)
	LPITEMIDLIST pidl = SHBrowseForFolderA(&bi);

	if (pidl != NULL) {
		// Get the folder path from the item ID list (ANSI version)
		SHGetPathFromIDListA(pidl, szFile);
		IMalloc* imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc))) {
			imalloc->Free(pidl);  // Free memory
			imalloc->Release();
		}
		return std::string(szFile);  // Return the selected folder path
	}
	return std::string();
}
