#pragma once

#include "ICommand.h"
#include "ImageManager.h"


class GrayscaleCommand : public ICommand
{
public:
	GrayscaleCommand(ImageManager& imageManager, std::unique_ptr<sf::Image> image);
	void execute() override;
	void undo() override;

private:
	ImageManager& m_imageManager;
	sf::Image m_oldImage;
};

