#pragma once

#include <string>
#include <vector>


class GameObjectBlueprint
{
private:
    std::string m_Name = "";
    std::vector<std::string> m_ComponentList;
    std::string m_BitmapName = "";

    float m_Width;
    float m_Height;
    float m_LocationX;
    float m_LocationY;
    float m_Speed;

    bool m_EncompassingRectCollider = false;
    std::string m_EncompassingRectColliderLabel = "";

public:
    std::string getName();
    void setName(std::string name);

    std::vector<std::string>& getComponentList();
    void addToComponentList(std::string newComponent);

    std::string getBitmapName();
    void setBitmapName(std::string bitmapName);

    float getWidth();
    void setWidth(float width);

    float getHeight();
    void setHeight(float height);

    float getLocationX();
    void setLocationX(float locationX);

    float getLocationY();
    void setLocationY(float locationY);

    bool getEncompassingRectCollider();
    std::string getEncompassingRectColliderLabel();
    void setEncompassingRectCollider(std::string label);
};
