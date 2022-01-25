#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player {
private:
	const float START_SPEED = 200.0f;
	const int START_HEALTH = 100;

	Vector2f m_Position;
	Sprite m_Sprite;
	Texture m_Texture;

	Vector2f m_Resolution;
	IntRect m_Arena;
	int m_TileSize;

	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;

	int m_Health;
	int m_MaxHealth;
	Time m_LastHit;
	float m_Speed;

public:
	Player();
	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	void resetPlayerStats();
	bool hit(Time timeHit);
	Time getLastHitTime();

	FloatRect getPosition();
	Vector2f getCenter();
	float getRotation();
	Sprite getSprite();

	void moveLeft();
	void stopLeft();
	void moveRight();
	void stopRight();
	void moveUp();
	void stopUp();
	void moveDown();
	void stopDown();

	void update(float elapsedTime, Vector2i mousePosition);
	void upgradeSpeed();
	void upgradeHealth();
	void increaseHealthLevel(int amount);
	int getHealth();
};
