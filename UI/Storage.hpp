#include <SFML/Graphics.hpp>
#include <array>

class Storage {
	std::array<std::array<sf::Texture, 6>, 2> textures;
	sf::Font font;

	static Storage* storage;

public:
	Storage();

	void addTexture(int side, int figure, const std::string& path);
	void addFont(const std::string& path);

	sf::Texture getTexture(int side, int figure);
	sf::Font getFont(const std::string& name);
};