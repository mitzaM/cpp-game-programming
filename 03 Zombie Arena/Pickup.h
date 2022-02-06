#pragma once
#include <SFML/Graphics.hpp>

enum class PickupType { HEALTH, AMMO };

class Pickup {
private:
	const int HEALTH_START_VALUE = 50;
	const int AMMO_START_VALUE = 12;
	const int START_WAIT_TIME = 10;
	const int START_SECONDS_TO_LIVE = 5;

	sf::Sprite m_Sprite;
	sf::IntRect m_Arena;
	int m_Value;
	PickupType m_Type;

	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDespawn;
	float m_SecondsToLive;
	float m_SecondsToWait;

public:
	Pickup(PickupType type);
	void spawn();

	void setArena(sf::IntRect arena);
	sf::FloatRect getPosition();
	sf::Sprite getSprite();

	bool isSpawned();
	int gotIt();
	void upgrade();

	void update(float elapsedTime);
};
