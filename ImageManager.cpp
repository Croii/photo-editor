#include "ImageManager.h"
#include "RotateImageCommand.h"

ImageManager::ImageManager() : m_imageLoader(std::unique_ptr<ImageLoader>()), m_scale(1.0f)
{

}

void ImageManager::draw(sf::RenderWindow& window, sf::RenderStates) const
{
	window.draw(m_sprite);
}

void ImageManager::update(const sf::Event& event)
{
	//switch (event.type)
	//{
	//case sf::Event::KeyPressed:
	//	if (event.key.code == sf::Keyboard::A)
	//		m_zoomDown();
	//	else if (event.key.code == sf::Keyboard::B)
	//		m_zoomUp();
	//}
}

bool ImageManager::saveImage(const std::string& path) const
{
	if (m_image == nullptr || m_image->getSize().x == 0 || m_image->getSize().y == 0 || path.size() == 0)
	{
		std::cout << "No image to save" << std::endl;
		return 0;
	}
	return m_imageLoader->saveImage(m_sprite.getTexture()->copyToImage(), path);

	//return m_imageLoader->saveImage(*m_image, path);
}


void ImageManager::zoomIn()
{
	m_scale = m_scale * 1.1f;
	m_updateScale();
}

void ImageManager::zoomOut()
{
	m_scale = m_scale * 0.9f;
	m_updateScale();
}

//update the image scale so that it fits the canvas
void ImageManager::m_updateScale()
{
	if (m_texture.getSize().x > constants::CANVAS_HEIGHT || m_texture.getSize().y > constants::CANVAS_WIDTH)
	{
		m_scale = std::min(static_cast<float>(constants::CANVAS_HEIGHT) / m_texture.getSize().y,
			static_cast<float>(constants::CANVAS_WIDTH) / m_texture.getSize().x);
	}
	else
	
	m_sprite.setScale(m_scale, m_scale);
	m_sprite.setPosition(0.0f + constants::CANVAS_X + constants::CANVAS_WIDTH / 2 - m_texture.getSize().x / 2 * m_scale,
		0.0f + constants::CANVAS_Y + constants::CANVAS_HEIGHT / 2 - m_texture.getSize().y / 2 * m_scale);
}


//load the image into a temporary object and process every pixel	
void ImageManager::rotateLeft()
{
	int oldWidth = m_image->getSize().x;
	int oldHeight = m_image->getSize().y;
	std::unique_ptr<sf::Image> newImage = std::make_unique<sf::Image>();
	newImage->create(oldHeight, oldWidth);

	for (int y = 0; y < oldHeight; y++)
		for (int x = 0; x < oldWidth; x++)
		{
			newImage->setPixel(y, (oldWidth - x - 1), m_image->getPixel(x, y));
		}
	//clear the old one and load the newly created one
	m_image.swap(newImage);
	m_texture.loadFromImage(*m_image);
	m_sprite.setTexture(m_texture, true);
	newImage = nullptr;
	m_updateScale();

}

void ImageManager::rotateRight()
{
	int oldWidth = m_image->getSize().x;
	int oldHeight = m_image->getSize().y;
	std::unique_ptr<sf::Image> newImage = std::make_unique<sf::Image>();
	newImage->create(oldHeight, oldWidth);

	for (int y = 0; y < oldHeight; y++)
		for (int x = 0; x < oldWidth; x++)
		{
			newImage->setPixel((oldHeight - y - 1), x, m_image->getPixel(x, y));
		}
	m_image.swap(newImage);
	m_texture.loadFromImage(*m_image);
	m_sprite.setTexture(m_texture, true);
	newImage = nullptr;
	m_updateScale();

}

void ImageManager::grayScale()
{
	int width = m_image->getSize().x;
	int height = m_image->getSize().y;

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			int red = m_image->getPixel(i, j).r;
			int green = m_image->getPixel(i, j).g;
			int blue = m_image->getPixel(i, j).b;

			red = static_cast<int>(red * 0.299);
			green = static_cast<int>(green * 0.299);
			blue = static_cast<int>(blue * 0.299);
			int gray = std::min(blue + red + blue, 255);
			m_image->setPixel(i, j, sf::Color(gray, gray, gray));
		}
	m_texture.loadFromImage(*m_image);
	m_sprite.setTexture(m_texture);
}

//convolution between the image and the kernel
void ImageManager::blur()
{
	int width = m_image->getSize().x;
	int height = m_image->getSize().y;

	sf::Image newImage;
	newImage.create(width, height);

	const int DIRECTIONS = 9;
	const int KERNELSIZE = 3;

	//blur kernel
	const std::array<std::array<int, KERNELSIZE>, KERNELSIZE> KERNEL = { { {1,2,1},{2,0,2},{1,2,1} } };
	//every neighbour + the cell itself up 
	const std::array<int, DIRECTIONS> dx = { 0, 0, 0, 1, 1, 1, -1, -1, -1 };
	const std::array<int, DIRECTIONS> dy = { 0, -1, 1, 1, 0, -1, 1, 0, -1 };


	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			unsigned int newR = 0;
			unsigned int newG = 0;
			unsigned int newB = 0;

			int cnt = 0;
			for (int k = 0; k < DIRECTIONS; k++)
			{
				int x = i + dx[k];
				int y = j + dy[k];



				bool outOfBoundX = (x < 0) || (x >= width);
				bool outOfBoundY = (y < 0) || (y >= height);
				
				//cnt used for normalization
				if (!outOfBoundX && !outOfBoundY)
				{
					cnt += KERNEL[dx[k] + 1][dy[k] + 1];
					newR += m_image->getPixel(x, y).r * KERNEL[dx[k] + 1][dy[k] + 1];
					newG += m_image->getPixel(x, y).g * KERNEL[dx[k] + 1][dy[k] + 1];
					newB += m_image->getPixel(x, y).b * KERNEL[dx[k] + 1][dy[k] + 1];
				}

			}
			newR /= cnt;
			newG /= cnt;
			newB /= cnt;
			newImage.setPixel(i, j, sf::Color(newR, newG, newB));
		}
	m_image = std::make_unique<sf::Image>(newImage);
	m_texture.loadFromImage(*m_image);
	m_sprite.setTexture(m_texture);
}


//create a new unqiue ptr and return the old one
std::unique_ptr<sf::Image> ImageManager::getImage() const
{
	if (m_image == nullptr)
		return nullptr;

	int width = m_image->getSize().x;
	int height = m_image->getSize().y;
	auto imageCopy = std::make_unique<sf::Image>();
	imageCopy->create(width, height);
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
		{
			imageCopy->setPixel(i, j, m_image->getPixel(i, j));
		}
	return imageCopy;
}

//loads the image from the image object and scale it accordingly
bool ImageManager::loadImage(sf::Image& image)
{
	if (image.getSize().x == 0 || image.getSize().y == 0)
		return 0;
	m_image = std::make_unique<sf::Image>(image);
	m_texture.loadFromImage(*m_image);
	m_sprite.setScale(m_scale, m_scale);
	m_sprite.setTexture(m_texture);
	m_updateScale();

}

bool ImageManager::loadImage(std::unique_ptr<sf::Image> image)
{
	if (image == nullptr)
		return false;
	m_image = nullptr;
	m_image = std::move(image);
	m_texture.loadFromImage(*m_image);
	m_sprite.setScale(m_scale, m_scale);
	m_sprite.setTexture(m_texture);

	m_updateScale();
	return true;
}

void ImageManager::rotate(Orientation orientation)
{
	if (orientation == Orientation::LEFT)
		rotateLeft();
	else if (orientation == Orientation::RIGHT)
		rotateRight();
}

bool ImageManager::loadImage(const std::string& path)
{

	auto loadedImage = m_imageLoader->loadImage(path);
	if (loadedImage == nullptr)
	{
		return false;
	}

	m_scale = 1.0f;


	//reinitialization prevents visual glitch
	m_image = std::make_unique<sf::Image>();
	m_image = std::move(loadedImage);
	m_texture = sf::Texture();
	m_texture.loadFromImage(*m_image);
	m_sprite = sf::Sprite();
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(m_scale, m_scale);

	m_updateScale();
	return true;
}