#include <SFML/Graphics.hpp>
#include <unordered_map>

class Storage {
	std::unordered_map<int, sf::Texture> textures;
	sf::Font font;
	sf::Texture redCross;

	static Storage* storage;

public:
	Storage();

	void addTexture(int res, const std::string& path);
	void addFont(const std::string& path);
	void addCross(const std::string& path);

	sf::Texture *getTexture(int res);
	sf::Font *getFont();
	sf::Texture* getCross();

	static Storage* getPtr();
};