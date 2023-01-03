#include "../include/ResourcesManager.h"

ResourcesManager::ResourcesManager() {
    m_font.loadFromFile("/System/Library/Fonts/Supplemental/Arial Unicode.ttf");
    for(int i = 0;i < MENU_BUTTONS;i++){
        m_textures[i].loadFromFile("../../../" + m_buttonString[i] + ".png");
    }

}

sf::Font ResourcesManager::getFont() {
    return m_font;
}



ResourcesManager& ResourcesManager::instance()
{
    static ResourcesManager inst;
    return inst;
}

sf::Texture *ResourcesManager::getTexture(int loc) {
    return &m_textures[loc];
}
