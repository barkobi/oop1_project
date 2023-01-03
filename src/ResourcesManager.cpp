#include "../include/ResourcesManager.h"

ResourcesManager::ResourcesManager() {
    for(int i = 0;i < MENU_BUTTONS;i++){
        m_textures[i].loadFromFile("../../../" + m_buttonString[i] + ".png");
    }
    m_sounds[0].loadFromFile("../../../menu_hover.wav");
}

sf::Font ResourcesManager::getFont() {
    return m_font;
}

ResourcesManager& ResourcesManager::instance(){
    static ResourcesManager inst;
    return inst;
}

sf::Texture *ResourcesManager::getTexture(const int loc) {
    return &m_textures[loc];
}

sf::SoundBuffer* ResourcesManager::getSound(const int index) {
    return &m_sounds[index];
}
