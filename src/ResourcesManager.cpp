#include "../include/ResourcesManager.h"

/**
 * initial all the members, read all the files, load all the sounds and textures.
 */
ResourcesManager::ResourcesManager() {
    m_passScreen.loadFromFile("PasswordScreen.png");
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

ResourcesManager &ResourcesManager::instance() {
    static ResourcesManager inst;
    return inst;
}

sf::Font& ResourcesManager::getFont() {
    return m_font;
}

/**
 * get menu button
 * @param loc what button to get.
 * @return button
 */
sf::Texture *ResourcesManager::getMenuTexture(const int loc) {
    return &m_menuButtonTxt[loc];
}

/**
 * play sound, will be played if the user set the flip to play.
 * @param index what sound to play
 */
void ResourcesManager::playSound(const int index) {
    if(!SettingsManager::instance().getFXSwitch())
        return;
    m_sounds[index].setBuffer(m_sounds_buffs[index]);
    m_sounds[index].setLoop(false);
    m_sounds[index].setVolume(SettingsManager::instance().getVolume());
    m_sounds[index].play();
}

/**
 * get texture.
 * @param loc what texture to get.
 * @return texture
 */
sf::Texture *ResourcesManager::getObjectTexture(const int loc) {
    return &m_pictures[loc];
}

/**
 * play background music, play only if sound flip is on.
 */
void ResourcesManager::playBackgroundMusic() {
    if(!SettingsManager::instance().getMusicSwitch())
        return;

    m_backgroundMusic.setVolume(SettingsManager::instance().getBGMVolume());
    m_backgroundMusic.setLoop(true);
    m_backgroundMusic.play();
}

/**
 * update/stop background music and volume.
 */
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

/**
 * get the background texture.
 * @return background.
 */
sf::Texture *ResourcesManager::getBackground() {
    return &m_backGround;
}

/**
 * get the title texture.
 * @return title.
 */
sf::Texture *ResourcesManager::getTitle() {
    return &m_title;
}

/**
 * get the sound button texture.
 * @return sound button.
 */
sf::Texture *ResourcesManager::getSoundButton(const int loc) {
    return &m_soundButton[loc];
}

/**
 * pause the background music.
 */
void ResourcesManager::pauseBackgroundMusic() {
    m_backgroundMusic.pause();
}

/**
 * is the background music currently playing.
 */
bool ResourcesManager::isBGMusicPlaying() {
    return m_backgroundMusic.getStatus() == sf::Music::Playing;
}

/**
 * get the help screen image.
 * @return help screen.
 */
sf::Texture *ResourcesManager::getHelpScreen() {
    return &m_helpScreen;
}

/**
 * stop playing sound
 * @param index the sound to stop.
 */
void ResourcesManager::stopSound(const int index) {
    m_sounds[index].stop();
}

sf::Texture *ResourcesManager::getPassScreen() {
    return &m_passScreen;
}
