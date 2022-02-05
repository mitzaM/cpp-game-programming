#pragma once
#include<SFML/Graphics.hpp>

class Bullet {
private:
	sf::Vector2f m_Position;
	sf::RectangleShape m_BulletShape;

	bool m_InFlight = false;
	float m_BulletSpeed = 1000.0f;

	float m_BulletDistanceX;
	float m_BulletDistanceY;

	float m_MinX;
	float m_MaxX;
	float m_MinY;
	float m_MaxY;

public:
	Bullet();
	sf::FloatRect getPosition();
	sf::RectangleShape getShape();

	void shoot(float startX, float startY, float targetX, float targetY);
	void stop();
	bool isInFlight();

	void update(float elapsedTime);
};
