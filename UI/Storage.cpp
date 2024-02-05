#include "Storage.hpp"

Storage::Storage() = default;

Storage* Storage::storage = nullptr;

void Storage::addTexture(int res, const std::string& path) {
    textures[res].loadFromFile("sprites/alpha/" + path);
}

void Storage::addFont(const std::string& path) {
    font.loadFromFile(path);
}

sf::Texture *Storage::getTexture(int res) {
    return &textures[res];
}
sf::Font *Storage::getFont(const std::string& name) {
    return &font;
}

Storage* Storage::getPtr() {
    if (storage == nullptr) {
        storage = new Storage();
    }
    return storage;
}