#include "RotateImageCommand.h"

RotateImageCommand::RotateImageCommand(ImageManager& imageManager, float newOrientation) : m_imageManager(imageManager), m_newOrientation(newOrientation)
{
}

void RotateImageCommand::execute()
{
	m_oldOrientation = m_newOrientation;
	m_imageManager.rotate(m_newOrientation);
}

void RotateImageCommand::undo()
{
	m_imageManager.rotate(m_oldOrientation);
}
