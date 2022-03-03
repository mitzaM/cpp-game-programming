#include "Bob.h"
#include "TextureHolder.h"


Bob::Bob()
{
    m_Sprite = sf::Sprite(TextureHolder::GetTexture("graphics/bob.png"));
    m_JumpDuration = 0.25f;
}

bool Bob::handleInput()
{
    m_JustJumped = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (!m_IsJumping && !m_IsFalling) {
            m_IsJumping = true;
            m_TimeThisJump = 0.0f;
            m_JustJumped = true;
        }
    } else {
        m_IsJumping = false;
        m_IsFalling = true;
    }
    m_LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    m_RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

    return m_JustJumped;
}
