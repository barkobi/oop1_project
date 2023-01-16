#include "../include/ResourcesManager.h"

ResourcesManager::ResourcesManager() {
    m_backgroundMusic.openFromFile("pacmanBackground.wav");
    for (int i = 0; i < MENU_BUTTONS; i++) {
        m_menuButtonTxt[i].loadFromFile(m_buttonString[i] + ".png");
    }
    for(int i = 0;i < 2;i++)
    {
        m_soundButton[i].loadFromFile(m_soundstring[i] + ".png");
    }
    for (int i = 0; i < NUMBER_OF_SOUNDS; i++) {
        m_sounds_buffs[i].loadFromFile(m_sound_file_names[i]);
        m_sounds[i].setBuffer(m_sounds_buffs[i]);
    }
    m_backGround.loadFromFile("backGroundimage.png");
    m_title.loadFromFile("Title.png");
    for(int i = 0;i < OBJECTS;i++){
        m_pictures[i].loadFromFile(m_picturesString[i] + ".png");
    }

    m_helpScreen.loadFromFile("HelpScreen.png");

    m_font.loadFromFile("PressStart2P.ttf");
}

sf::Font& ResourcesManager::getFont() {
    return m_font;
}

ResourcesManager &ResourcesManager::instance() {
    static ResourcesManager inst;
    return inst;
}

sf::Texture *ResourcesManager::getMenuTexture(const int loc) {
    return &m_menuButtonTxt[loc];
}

void ResourcesManager::playSound(const int index) {
    if(!SettingsManager::instance().getFXSwitch())
        return;
    m_sounds[index].setBuffer(m_sounds_buffs[index]);
    m_sounds[index].setLoop(false);
    m_sounds[index].setVolume(SettingsManager::instance().getVolume());
    m_sounds[index].play();
}

sf::Texture *ResourcesManager::getObjectTexture(const int loc) {
    return &m_pictures[loc];
}

void ResourcesManager::playBackgroundMusic() {
    if(!SettingsManager::instance().getMusicSwitch())
        return;

    m_backgroundMusic.setVolume(SettingsManager::instance().getBGMVolume());
    m_backgroundMusic.setLoop(true);
    m_backgroundMusic.play();
}

void ResourcesManager::updateSounds() {
    if(!SettingsManager::instance().getMusicSwitch()){
        m_backgroundMusic.stop();
        return;
    }

    if(m_backgroundMusic.getStatus() != sf::Music::Status::Playing)
        m_backgroundMusic.play();

    m_backgroundMusic.setVolume(SettingsManager::instance().getBGMVolume());
    m_backgroundMusic.setLoop(true);

}



sf::Texture *ResourcesManager::getBackground() {
    return &m_backGround;
}

sf::Texture *ResourcesManager::getTitle() {
    return &m_title;
}

sf::Texture *ResourcesManager::getSoundButton(const int loc) {
    return &m_soundButton[loc];
}

void ResourcesManager::pauseBackgroundMusic() {
    m_backgroundMusic.pause();
}

bool ResourcesManager::isBGMusicPlaying() {
    return m_backgroundMusic.getStatus() == sf::Music::Playing;
}

sf::Texture *ResourcesManager::getHelpScreen() {
    return &m_helpScreen;
}
