#pragma once
#include "../../include/Command/ICommand.h"
#include "../../include/Utility.h"

#include "../../include/ImageManager.h"


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

