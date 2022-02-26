#include "PlayableCharacter.h"

void PlayableCharacter::spawn(sf::Vector2f startPosition, float gravity) {
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	m_Gravity = gravity;

	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::update(float elapsedTime) {
	if (m_RightPressed) {
		m_Position.x += m_Speed * elapsedTime;
	}
	if (m_LeftPressed) {
		m_Position.x -= m_Speed * elapsedTime;
	}

	if (m_IsJumping) {
		m_TimeThisJump += elapsedTime;
		if (m_TimeThisJump < m_JumpDuration) {
			m_Position.y -= m_Gravity * 2 * elapsedTime;
		}
		else {
			m_IsJumping = false;
			m_IsFalling = true;
		}
	}
	if (m_IsFalling) {
		m_Position.y += m_Gravity * elapsedTime;
	}

	sf::FloatRect pos = getPosition();

	m_Feet.left = pos.left + 3;
	m_Feet.top = pos.top + pos.height - 1;
	m_Feet.width = pos.width - 6;
	m_Feet.height = 1;

	m_Head.left = pos.left;
	m_Head.top = pos.top + pos.height * 0.3f;
	m_Head.width = pos.width;
	m_Head.height = 1;

	m_Right.left = pos.left + pos.width - 2;
	m_Right.top = pos.top + pos.height * 0.35f;
	m_Right.width = 1;
	m_Right.height = pos.height * 0.3f;

	m_Left.left = pos.left;
	m_Left.top = pos.top + pos.height * 0.5f;
	m_Left.width = 1;
	m_Left.height = pos.height * 0.3f;

	m_Sprite.setPosition(m_Position);
}

sf::FloatRect PlayableCharacter::getPosition() {
	return m_Sprite.getGlobalBounds();
}

sf::Vector2f PlayableCharacter::getCenter() {
	return sf::Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

sf::FloatRect PlayableCharacter::getFeet() {
	return m_Feet;
}

sf::FloatRect PlayableCharacter::getHead() {
	return m_Head;
}

sf::FloatRect PlayableCharacter::getRight() {
	return m_Right;
}

sf::FloatRect PlayableCharacter::getLeft() {
	return m_Left;
}

sf::Sprite PlayableCharacter::getSprite() {
	return m_Sprite;
}

void PlayableCharacter::stopFalling(float position) {
	m_Position.y = position - getPosition().height;
	m_Sprite.setPosition(m_Position);
	m_IsFalling = false;
}

void PlayableCharacter::stopRight(float position) {
	m_Position.x = position - getPosition().width;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::stopLeft(float position) {
	m_Position.x = position + getPosition().width;
	m_Sprite.setPosition(m_Position);
}

void PlayableCharacter::stopJump() {
	m_IsJumping = false;
	m_IsFalling = true;
}
