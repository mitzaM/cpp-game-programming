#pragma once

#include <string>

#include "Component.h"


class UpdateComponent : public Component
{
private:
    std::string m_Type = "update";
    bool m_Enabled = false;

public:
    virtual void update(float fps) = 0;

    std::string Component::getType()
    {
        return m_Type;
    }

    void Component::disableComponent()
    {
        m_Enabled = false;
    }

    void Component::enableComponent()
    {
        m_Enabled = true;
    }

    bool Component::enabled()
    {
        return m_Enabled;
    }

    void Component::start(GameObjectSharer* gos, GameObject* self) {}
};
