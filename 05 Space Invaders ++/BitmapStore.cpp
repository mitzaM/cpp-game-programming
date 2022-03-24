#include <assert.h>

#include "BitmapStore.h"


BitmapStore* BitmapStore::m_s_Instance = nullptr;

BitmapStore::BitmapStore()
{
    assert(m_s_Instance == nullptr);
    m_s_Instance = this;
}

void BitmapStore::addBitmap(std::string const& filename)
{
    std::map<std::string, sf::Texture>& bitmapsMap = m_s_Instance->m_BitmapsMap;
    std::map<std::string, sf::Texture>::iterator keyValuePair = bitmapsMap.find(filename);

    if (keyValuePair == bitmapsMap.end()) {
        sf::Texture& texture = bitmapsMap[filename];
        texture.loadFromFile(filename);
    }
}

sf::Texture& BitmapStore::getBitmap(std::string const& filename)
{
    std::map<std::string, sf::Texture>& m = m_s_Instance->m_BitmapsMap;
    std::map<std::string, sf::Texture>::iterator keyValuePair = m.find(filename);

    if (keyValuePair != m.end()) {
        return keyValuePair->second;
    } else {
        #ifdef debuggingOnConsole
        std::cout << "BitmapStore::getBitmap()Texture not found Crash!" << std::endl;
        #endif // debuggingOnConsole
        return keyValuePair->second;
    }
}
