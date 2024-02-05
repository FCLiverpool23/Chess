#include <SFML/Graphics.hpp>
#include <unordered_map>

class Storage {
	std::unordered_map<int, sf::Texture> textures;
	sf::Font font;

	static Storage* storage;

public:
	Storage();

	void addTexture(int res, const std::string& path);
	void addFont(const std::string& path);

	sf::Texture *getTexture(int res);
	sf::Font *getFont(const std::string& name);

	static Storage* getPtr();
};