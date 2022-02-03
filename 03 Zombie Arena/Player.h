#pragma once
#include <SFML/Graphics.hpp>

class Player {
private:
	const float START_SPEED = 200.0f;
	const int START_HEALTH = 100;

	sf::Vector2f m_Position;
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;

	sf::Vector2u m_Resolution;
	sf::IntRect m_Arena;
	int m_TileSize;

	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	int m_Health;
	int m_MaxHealth;
	sf::Time m_LastHit;
	float m_Speed;

public:
	Player();
	void spawn(sf::IntRect arena, sf::Vector2u resolution, int tileSize);

	void resetPlayerStats();
	bool hit(sf::Time timeHit);
	sf::Time getLastHitTime();

	sf::FloatRect getPosition();
	sf::Vector2f getCenter();
	float getRotation();
	sf::Sprite getSprite();

	void moveLeft();
	void stopLeft();
	void moveRight();
	void stopRight();
	void moveUp();
	void stopUp();
	void moveDown();
	void stopDown();

	void update(float elapsedTime, sf::Vector2i mousePosition);
	void upgradeSpeed();
	void upgradeHealth();
	void increaseHealthLevel(int amount);
	int getHealth();
};
