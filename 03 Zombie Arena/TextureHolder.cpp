#include <assert.h>

#include "TextureHolder.h"

using namespace sf;

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder() {
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

Texture& TextureHolder::GetTexture(std::string const& filename) {
	std::map<std::string, Texture>& m = m_s_Instance->m_Textures;
	std::map<std::string, Texture>::iterator keyValuePair = m.find(filename);

	if (keyValuePair != m.end()) {
		return keyValuePair->second;
	}
	else {
		Texture& texture = m[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}
