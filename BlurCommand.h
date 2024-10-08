#pragma once
#include "ImageManager.h"
#include "ICommand.h"

class BlurCommand : public ICommand
{
public:
	BlurCommand(ImageManager& imageManager, std::unique_ptr<sf::Image> image);
	void execute() override;
	void undo() override;

private:
	ImageManager& m_imageManager;
	sf::Image m_oldImage;
};

