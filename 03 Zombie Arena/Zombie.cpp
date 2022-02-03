#include <cstdlib>
#include <ctime>

#include "TextureHolder.h"
#include "Zombie.h"

void Zombie::spawn(float startX, float startY, ZombieType type, int seed) {
	switch (type) {
	case ZombieType::BLOATER:
		m_Sprite = sf::Sprite(TextureHolder::GetTexture("graphics/bloater.png"));
		m_Speed = BLOATER_SPEED;
		m_Health = BLOATER_HEALTH;
		break;
	case ZombieType::CHASER:
		m_Sprite = sf::Sprite(TextureHolder::GetTexture("graphics/chaser.png"));
		m_Speed = CHASER_SPEED;
		m_Health = CHASER_HEALTH;
		break;
	case ZombieType::CRAWLER:
		m_Sprite = sf::Sprite(TextureHolder::GetTexture("graphics/crawler.png"));
		m_Speed = CRAWLER_SPEED;
		m_Health = CRAWLER_HEALTH;
		break;
	}

	srand((int)time(0) * seed);
	float modifier = (float)(rand() % MAX_VARIANCE) + OFFSET;
	modifier /= 100;
	m_Speed *= modifier;

	m_Position.x = startX;
	m_Position.y = startY;

	m_Sprite.setOrigin(25, 25);
	m_Sprite.setPosition(m_Position);
}

bool Zombie::hit() {
	m_Health--;

	if (m_Health < 0) {
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/blood.png"));
		return true;
	}

	return false;
}

bool Zombie::isAlive() {
	return m_Alive;
}

sf::FloatRect Zombie::getPosition() {
	return m_Sprite.getGlobalBounds();
}

sf::Sprite Zombie::getSprite() {
	return m_Sprite;
}

void Zombie::update(float elapsedTime, sf::Vector2f playerLocation) {
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	if (playerX > m_Position.x) {
		m_Position.x += m_Speed * elapsedTime;
	}
	if (playerY > m_Position.y) {
		m_Position.y += m_Speed * elapsedTime;
	}

	if (playerX < m_Position.x) {
		m_Position.x -= m_Speed * elapsedTime;
	}
	if (playerY < m_Position.y) {
		m_Position.y -= m_Speed * elapsedTime;
	}

	m_Sprite.setPosition(m_Position);

	int dx = (int)(playerX - m_Position.x);
	int dy = (int)(playerY - m_Position.y);
	float angle = (float)((atan2(dy, dx) * 180) / 3.141);
	m_Sprite.setRotation(angle);
}
