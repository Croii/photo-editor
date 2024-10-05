#pragma once
#include "ICommand.h"
#include "Utility.h"

#include "ImageManager.h"

//class ImageManager;

class RotateImageCommand : public ICommand
{
public:
	RotateImageCommand(ImageManager& imageManager, Orientation newOrientation);
	void execute() override;
	void undo() override;

private:
	ImageManager& m_imageManager;
	Orientation m_newOrientation;
	Orientation m_oldOrientation;

};

