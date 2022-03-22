#pragma once

#ifndef SOUND_ENGINE_H
#define SOUND_ENGINE_H

#include <SFML/Audio.hpp>


class SoundEngine
{
private:
    sf::SoundBuffer m_ShootBuffer;
    sf::SoundBuffer m_PlayerExplodeBuffer;
    sf::SoundBuffer m_InvaderExplodeBuffer;
    sf::SoundBuffer m_ClickBuffer;

    sf::Sound m_ShootSound;
    sf::Sound m_PlayerExplodeSound;
    sf::Sound m_InvaderExplodeSound;
    sf::Sound m_UhSound;
    sf::Sound m_OhSound;
    sf::Sound m_ClickSound;

public:
    SoundEngine();

    static void playShoot();
    static void playPlayerExplode();
    static void playInvaderExplode();
    static void playClick();

    static SoundEngine* m_s_Instance;
};

#endif // !SOUND_ENGINE_H
