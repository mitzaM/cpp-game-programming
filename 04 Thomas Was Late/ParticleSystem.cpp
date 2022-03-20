#include <SFML/Graphics.hpp>

#include "ParticleSystem.h"


void ParticleSystem::init(int numParticles)
{
    m_Vertices.setPrimitiveType(sf::Points);
    m_Vertices.resize(numParticles);

    for (int i = 0; i < numParticles; i++) {
        srand((unsigned int)time(0) + i);
        float angle = (rand() % 360) * 3.14f / 180.0f;
        float speed = (rand() % 600) + 600.0f;

        sf::Vector2f direction(cos(angle) * speed, sin(angle) * speed);
        m_Particles.push_back(Particle(direction));
    }
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_Vertices, states);
}

bool ParticleSystem::running() {
    return m_IsRunning;
}

void ParticleSystem::update(float dt)
{
    m_Duration -= dt;
    m_IsRunning = m_Duration >= 0;

    int currentVertex = 0;
    for (std::vector<Particle>::iterator it = m_Particles.begin(); it != m_Particles.end(); it++) {
        (*it).update(dt);
        m_Vertices[currentVertex++].position = it->getPosition();
    }
}

void ParticleSystem::emitParticles(sf::Vector2f startPosition)
{
    m_IsRunning = true;
    m_Duration = 2.0f;

    int currentVertex = 0;
    for (std::vector<Particle>::iterator it = m_Particles.begin(); it != m_Particles.end(); it++) {
        m_Vertices[currentVertex++].color = sf::Color::Yellow;
        it->setPosition(startPosition);
    }
}
