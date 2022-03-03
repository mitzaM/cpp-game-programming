#pragma once

#include <SFML/Graphics.hpp>


class PlayableCharacter
{
protected:
    sf::Sprite m_Sprite;

    float m_JumpDuration{};
    bool m_JustJumped = false;
    float m_TimeThisJump = 0.0f;

    bool m_IsJumping = false;
    bool m_IsFalling = false;

    bool m_LeftPressed = false;
    bool m_RightPressed = false;

private:
    float m_Gravity{};
    float m_Speed = 400.0f;

    sf::Vector2f m_Position{};

    sf::FloatRect m_Feet{};
    sf::FloatRect m_Head{};
    sf::FloatRect m_Right{};
    sf::FloatRect m_Left{};

    sf::Texture m_Texture{};

public:
    void spawn(sf::Vector2f startPosition, float gravity);

    bool virtual handleInput() = 0;

    sf::FloatRect getPosition();
    sf::FloatRect getFeet();
    sf::FloatRect getHead();
    sf::FloatRect getRight();
    sf::FloatRect getLeft();

    sf::Sprite getSprite();

    void stopFalling(float position);
    void stopRight(float position);
    void stopLeft(float position);
    void stopJump();

    sf::Vector2f getCenter();

    void update(float elapsedTime);
};
