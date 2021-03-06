#pragma once
#include <SFML/Graphics.hpp>

enum class ZombieType { BLOATER, CHASER, CRAWLER };

class Zombie {
private:
	const float BLOATER_SPEED = 40.0f;
	const float CHASER_SPEED = 80.0f;
	const float CRAWLER_SPEED = 20.0f;

	const int BLOATER_HEALTH = 5;
	const int CHASER_HEALTH = 1;
	const int CRAWLER_HEALTH = 3;

	const int MAX_VARIANCE = 30;
	const int OFFSET = 101 - MAX_VARIANCE;

	sf::Vector2f m_Position;
	sf::Sprite m_Sprite;
	float m_Speed;
	int m_Health;
	bool m_Alive;

public:
	void spawn(float startX, float startY, ZombieType type, int seed);

	sf::FloatRect getPosition();
	sf::Sprite getSprite();

	bool hit();
	bool isAlive();
	void update(float elapsedTime, sf::Vector2f playerLocation);
};
