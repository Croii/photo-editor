#include "RotateImageCommand.h"
#include "ImageManager.h"

RotateImageCommand::RotateImageCommand(ImageManager& imageManager, Orientation newOrientation) : m_imageManager(imageManager), m_newOrientation(newOrientation)
{
}

void RotateImageCommand::execute()
{
	m_oldOrientation = m_newOrientation;
	if (m_newOrientation == Orientation::LEFT)
		m_imageManager.rotateLeft();
	else
		m_imageManager.rotateRight();
}

void RotateImageCommand::undo()
{
	if (m_oldOrientation == Orientation::LEFT)
		m_imageManager.rotateRight();
	else if (m_oldOrientation == Orientation::RIGHT)
		m_imageManager.rotateLeft();
}
