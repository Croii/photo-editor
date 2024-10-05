#pragma once

#include "ICommand.h"
#include "ImageManager.h"


class GrayscaleCommand : public ICommand
{
public:
	GrayscaleCommand(ImageManager& imageManager);
	void execute() override;
	void undo() override;

private:
	ImageManager& m_imageManager;
	std::unique_ptr<sf::Image> m_oldImage;
};

