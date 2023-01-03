#include "../include/ResourcesManager.h"

ResourcesManager::ResourcesManager() {
    for (int i = 0; i < MENU_BUTTONS; i++) {
        m_textures[i].loadFromFile("../../../" + m_buttonString[i] + ".png");
    }
    for (int i = 0; i < NUMBER_OF_SOUNDS; i++) {
        m_sounds_buffs[i].loadFromFile("../../../" + m_sound_file_names[i]);
        m_sounds[i].setBuffer(m_sounds_buffs[i]);
    }
}

sf::Font ResourcesManager::getFont() {
    return m_font;
}

ResourcesManager &ResourcesManager::instance() {
    static ResourcesManager inst;
    return inst;
}

sf::Texture *ResourcesManager::getTexture(const int loc) {
    return &m_textures[loc];
}

void ResourcesManager::playSound(const int index) {
    m_sounds[index].setBuffer(m_sounds_buffs[index]);
    m_sounds[index].setLoop(false);
    m_sounds[index].setVolume(100);
    m_sounds[index].play();
}
