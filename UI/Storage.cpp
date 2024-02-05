#include "Storage.hpp"

Storage::Storage() = default;

Storage* Storage::storage = nullptr;

void Storage::addTexture(int res, const std::string& path) {
    textures[res].loadFromFile("sprites/alpha/" + path);
}

void Storage::addFont(const std::string& path) {
    font.loadFromFile(path);
}

void Storage::addCross(const std::string& path) {
    redCross.loadFromFile(path);
}

sf::Texture *Storage::getTexture(int res) {
    return &textures[res];
}
sf::Font *Storage::getFont() {
    return &font;
}

sf::Texture* Storage::getCross() {
    return &redCross;
}

Storage* Storage::getPtr() {
    if (storage == nullptr) {
        storage = new Storage();
    }
    return storage;
}