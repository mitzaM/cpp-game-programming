#include "Pickup.h"
#include "TextureHolder.h"

Pickup::Pickup(PickupType type) {
	m_Type = type;
	switch (m_Type) {
	case PickupType::AMMO:
		m_Sprite = sf::Sprite(TextureHolder::GetTexture("graphics/ammo_pickup.png"));
		m_Value = AMMO_START_VALUE;
		break;
	case PickupType::HEALTH:
		m_Sprite = sf::Sprite(TextureHolder::GetTexture("graphics/health_pickup.png"));
		m_Value = HEALTH_START_VALUE;
		break;
	}

	m_Sprite.setOrigin(25, 25);
	m_SecondsToLive = (float)START_SECONDS_TO_LIVE;
	m_SecondsToWait = (float)START_WAIT_TIME;

	m_SecondsSinceSpawn = m_SecondsSinceDespawn = 0;
	m_Spawned = false;
}

void Pickup::setArena(sf::IntRect arena) {
	m_Arena.left = arena.left + 50;
	m_Arena.width = arena.width - 50;
	m_Arena.top = arena.top + 50;
	m_Arena.height = arena.height - 50;

	spawn();
}

void Pickup::spawn() {
	srand((int)time(0) / ((int)m_Type + 1));
	int x = rand() % m_Arena.width;
	srand((int)time(0) * ((int)m_Type + 1));
	int y = rand() % m_Arena.height;

	m_SecondsSinceSpawn = 0;
	m_Spawned = true;
	m_Sprite.setPosition((float)x, (float)y);
}

sf::FloatRect Pickup::getPosition() {
	return m_Sprite.getGlobalBounds();
}

sf::Sprite Pickup::getSprite() {
	return m_Sprite;
}

bool Pickup::isSpawned() {
	return m_Spawned;
}

int Pickup::gotIt() {
	m_Spawned = false;
	m_SecondsSinceDespawn = 0;
	return m_Value;
}
