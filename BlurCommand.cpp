#include "BlurCommand.h"

BlurCommand::BlurCommand(ImageManager& imageManager, std::unique_ptr<sf::Image> image) : m_imageManager(imageManager), m_oldImage(*image)
{
}

void BlurCommand::execute()
{
	m_oldImage = *m_imageManager.getImage();
	m_imageManager.blur();
}

void BlurCommand::undo()
{
	m_imageManager.loadImage(m_oldImage);
}