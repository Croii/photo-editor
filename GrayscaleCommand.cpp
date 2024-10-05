#include "GrayscaleCommand.h"

GrayscaleCommand::GrayscaleCommand(ImageManager& imageManager) : m_imageManager(imageManager)
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
