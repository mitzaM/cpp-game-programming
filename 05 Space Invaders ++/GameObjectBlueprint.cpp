#include <string>
#include <vector>

#include "GameObjectBlueprint.h"


std::string GameObjectBlueprint::getName()
{
    return m_Name;
}

void GameObjectBlueprint::setName(std::string name)
{
    m_Name = "" + name;
}

std::vector<std::string>& GameObjectBlueprint::getComponentList()
{
    return m_ComponentList;
}

void GameObjectBlueprint::addToComponentList(std::string newComponent)
{
    m_ComponentList.push_back(newComponent);
}

std::string GameObjectBlueprint::getBitmapName()
{
    return m_BitmapName;
}

void GameObjectBlueprint::setBitmapName(std::string bitmapName)
{
    m_BitmapName = "" + bitmapName;
}

float GameObjectBlueprint::getWidth()
{
    return m_Width;
}

void GameObjectBlueprint::setWidth(float width)
{
    m_Width = width;
}

float GameObjectBlueprint::getHeight()
{
    return m_Height;
}

void GameObjectBlueprint::setHeight(float height)
{
    m_Height = height;
}

float GameObjectBlueprint::getLocationX()
{
    return m_LocationX;
}

void GameObjectBlueprint::setLocationX(float locationX)
{
    m_LocationX = locationX;
}

float GameObjectBlueprint::getLocationY()
{
    return m_LocationY;
}

void GameObjectBlueprint::setLocationY(float locationY)
{
    m_LocationY = locationY;
}

bool GameObjectBlueprint::getEncompassingRectCollider()
{
    return m_EncompassingRectCollider;
}

std::string GameObjectBlueprint::getEncompassingRectColliderLabel()
{
    return m_EncompassingRectColliderLabel;
}

void GameObjectBlueprint::setEncompassingRectCollider(std::string label)
{
    m_EncompassingRectCollider = true;
    m_EncompassingRectColliderLabel = "" + label;
}
