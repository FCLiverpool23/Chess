#include "Storage.hpp"

Storage::Storage() = default;

Storage* Storage::storage = nullptr;

void Storage::addTexture(int side, int figure, const std::string& path) {
    textures[side][figure].loadFromFile("sprites/" + path);
}

void Storage::addFont(const std::string& path) {
    font.loadFromFile(path);
}

sf::Texture Storage::getTexture(int side, int figure) {
    return textures[side][figure];
}
sf::Font Storage::getFont(const std::string& name) {
    return font;
}
