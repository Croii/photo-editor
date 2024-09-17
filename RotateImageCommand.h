#pragma once
#include "ICommand.h"
#include "ImageManager.h"

class RotateImageCommand : public ICommand
{
public:
	RotateImageCommand(ImageManager& imageManager, float newOrientation);
	void execute() override;
	void undo() override;

private:
	ImageManager& m_imageManager;
	float m_newOrientation;
	float m_oldOrientation;

};

