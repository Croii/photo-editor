#include "GrayscaleCommand.h"

GrayscaleCommand::GrayscaleCommand(ImageManager& imageManager, std::unique_ptr<sf::Image> image) : m_imageManager(imageManager),m_oldImage(std::move(image))
{
	
}

void GrayscaleCommand::execute()
{

	m_imageManager.grayScale();
}

void GrayscaleCommand::undo()
{
	m_imageManager.loadImage(std::move(m_oldImage));
}
