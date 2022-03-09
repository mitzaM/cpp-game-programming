#pragma once

#include <SFML/Audio.hpp>


class SoundManager
{
private:
    sf::SoundBuffer m_FireBuffer;
    sf::SoundBuffer m_FallInFireBuffer;
    sf::SoundBuffer m_FallInWaterBuffer;
    sf::SoundBuffer m_JumpBuffer;
    sf::SoundBuffer m_ReachGoalBuffer;

    sf::Sound m_Fire1Sound;
    sf::Sound m_Fire2Sound;
    sf::Sound m_Fire3Sound;
    sf::Sound m_FallInFireSound;

    sf::Sound m_FallInWaterSound;
    sf::Sound m_JumpSound;
    sf::Sound m_ReachGoalSound;

    int m_NextSound = 1;

public:
    SoundManager();

    void playFire(sf::Vector2f emitterLocation, sf::Vector2f listenerLocation);
    void playFallInFire();
    void playFallInWater();
    void playJump();
    void playReachGoal();
};
