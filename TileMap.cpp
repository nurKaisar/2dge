#include "TileMap.h"

TileMap::TileMap()
{
	this->tileSheet1.loadFromFile("res/Textures/TILESHEET1.png");
	
    sf::Sprite sprite;
	for (size_t i = 0; i < 6; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			sprite.setTexture(this->tileSheet1);
			sprite.setTextureRect(sf::IntRect(64 * i, 64 * j, 64, 64));
			sprite.setPosition(j * 64 + 600.f, i * 64+700.f);
			this->selectSprite.push_back(sprite);
		}

	}
	sp.setTexture(this->tileSheet1);

	for (size_t i = 6; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			sprite.setTexture(this->tileSheet1);
			sprite.setTextureRect(sf::IntRect(64 * i, 64 * j, 64, 64));
			sprite.setPosition(j* 64 + 600.f, (i - 6) * 64 + 700.f);
			this->selectSprite2.push_back(sprite);
		}
	}
}

TileMap::~TileMap()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		    delete this->tiles[i];
	}
}

void TileMap::update(const float& dt)
{
}

void TileMap::render(sf::RenderWindow* window,bool showFirst)
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
			if (this->tiles[i] != nullptr)
			{
				this->tiles[i]->render(window);
			}
	}

	if (showFirst)
	{
		for (int i = 0; i < this->selectSprite.size(); i++)
		{
			window->draw(this->selectSprite[i]);

		}
	}
	else
	{

		for (int i = 0; i < this->selectSprite2.size(); i++)
		{
			window->draw(this->selectSprite2[i]);
		}
	}
}

void TileMap::savetoFile(std::string path)
{
	std::ofstream file;
	file.open(path);

	if (file.is_open())
	{

		file << this->tiles.size()<<"\n";

		for (size_t i = 0; i < this->tiles.size(); i++)
		{
			    file << this->tiles[i]->tile.getGlobalBounds().left<<" " << this->tiles[i]->tile.getGlobalBounds().top << " " << 
				this->tiles[i]->tile.getGlobalBounds().width << " "<<
				this->tiles[i]->tile.getGlobalBounds().height << " "<<
				this->tiles[i]->tile.getPosition().x << " " << this->tiles[i]->tile.getPosition().y << " " <<
				this->tiles[i]->collision;

		}
	}
	else
	{
		std::cout << "Prectedgsc" << std::endl;
	}

	file.close();
}

void TileMap::loadFromFile(const std::string path)
{
	std::ifstream file;

	file.open(path);


	if (file.is_open())
	{

		int size = 0;
		int left = 0;
		int top = 0;
		int width = 0;
		int height = 0;
		float x, y;
		bool collision = false;
		file >> size;

		/*if (!this->tiles.empty())
		{
			for (int i = 0; i < this->tiles.size(); i++)
			{
				if (this->tiles[i] != nullptr)
					delete this->tiles[i];
			}
			this->tiles.clear();
		}*/

		this->tiles.resize(size);

		for (size_t i = 0; i < size; i++)
		{
			this->tiles[i] = NULL;
		}
         

		for (int i = 0; i < size; i++)
		{
			file >> left >> top >> width >> height >> x >> y >> collision;

			this->tiles[i]->tile.setTexture(this->tileSheet1);
			this->tiles[i]->tile.setTextureRect(sf::IntRect(left, top, width, height));
			this->tiles[i]->tile.setPosition(x, y);
			this->tiles[i]->collision = collision;
		}
	}
	else
	{
		std::cout << "kakakkakakakak" << std::endl;
	}

	file.close();
}
