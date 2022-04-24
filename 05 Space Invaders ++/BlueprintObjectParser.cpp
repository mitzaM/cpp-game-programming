#include <fstream>
#include <string>

#include "BlueprintObjectParser.h"
#include "GameObjectBlueprint.h"
#include "ObjectTags.h"


void BlueprintObjectParser::parseNextObjectForBlueprint(std::ifstream& reader, GameObjectBlueprint& bp)
{
    std::string lineFromFile;
    std::string value = "";

    while (std::getline(reader, lineFromFile)) {
        if (lineFromFile.find(ObjectTags::COMPONENT) != std::string::npos) {
            bp.addToComponentList(
                extractStringBetweenTags(lineFromFile, ObjectTags::COMPONENT, ObjectTags::COMPONENT_END)
            );
        } else if (lineFromFile.find(ObjectTags::NAME) != std::string::npos) {
            bp.setName(
                extractStringBetweenTags(lineFromFile, ObjectTags::NAME, ObjectTags::NAME_END)
            );
        } else if (lineFromFile.find(ObjectTags::WIDTH) != std::string::npos) {
            bp.setWidth(
                std::stof(extractStringBetweenTags(lineFromFile, ObjectTags::WIDTH, ObjectTags::WIDTH_END))
            );
        } else if (lineFromFile.find(ObjectTags::HEIGHT) != std::string::npos) {
            bp.setHeight(
                std::stof(extractStringBetweenTags(lineFromFile, ObjectTags::HEIGHT, ObjectTags::HEIGHT_END))
            );
        } else if (lineFromFile.find(ObjectTags::LOCATION_X) != std::string::npos) {
            bp.setLocationX(
                std::stof(extractStringBetweenTags(lineFromFile, ObjectTags::LOCATION_X, ObjectTags::LOCATION_X_END))
            );
        } else if (lineFromFile.find(ObjectTags::LOCATION_Y) != std::string::npos) {
            bp.setLocationY(
                std::stof(extractStringBetweenTags(lineFromFile, ObjectTags::LOCATION_Y, ObjectTags::LOCATION_Y_END))
            );
        } else if (lineFromFile.find(ObjectTags::BITMAP_NAME) != std::string::npos) {
            bp.setBitmapName(
                extractStringBetweenTags(lineFromFile, ObjectTags::BITMAP_NAME, ObjectTags::BITMAP_NAME_END)
            );
        } else if (lineFromFile.find(ObjectTags::ENCOMPASSING_RECT_COLLIDER) != std::string::npos) {
            bp.setEncompassingRectCollider(
                extractStringBetweenTags(lineFromFile, ObjectTags::ENCOMPASSING_RECT_COLLIDER, ObjectTags::ENCOMPASSING_RECT_COLLIDER_END)
            );
        } else if (lineFromFile.find(ObjectTags::END_OF_OBJECT) != std::string::npos) {
            return;
        }
    }
}

std::string BlueprintObjectParser::extractStringBetweenTags(std::string stringToSearch, std::string startTag, std::string endTag)
{
    int start = startTag.length();
    int count = stringToSearch.length() - start - endTag.length();

    return stringToSearch.substr(start, count);
}
