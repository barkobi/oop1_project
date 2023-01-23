
#include "SettingsManager.h"

SettingsManager::SettingsManager() {
    load_settings();
}

/**
 * get instance of the settings manager.
 * @return instance of settingsManager
 */
SettingsManager& SettingsManager::instance(){
    static SettingsManager settings;
    return settings;
}

/**
 * load the saved settings from the file.
 */
void SettingsManager::load_settings() {
    if(!std::filesystem::exists("settings.txt")){
        m_fxsound = true;
        m_music = true;
        m_volume = 100;
        m_BGMVolume = 100;
        return;
    }

    std::ifstream settings_file;
    settings_file.open("settings.txt");

    if(!settings_file.is_open()){
        perror("Cannot open settings file");
        exit(EXIT_FAILURE);
    }

    settings_file.seekg(0);
    settings_file >> m_fxsound;
    settings_file >> m_music;
    settings_file >> m_volume;
    settings_file >> m_BGMVolume;
    settings_file.close();
}

/**
 * save the settings to the file.
 */
void SettingsManager::save_settings(){
    std::ofstream settings_file;

    if(std::filesystem::exists("settings.txt")){
        std::filesystem::remove("settings.txt");
    }
    settings_file.open("settings.txt");

    if(!settings_file.is_open()){
        perror("Cannot open settings file");
        exit(EXIT_FAILURE);
    }
    settings_file.seekp(0);
    settings_file << m_fxsound << " " << m_music << " " << m_volume << " " << m_BGMVolume;
    settings_file.close();
}


const bool SettingsManager::getMusicSwitch() const {return m_music;}

const int SettingsManager::getVolume() const {return m_volume;}

const int SettingsManager::getBGMVolume() const {return m_BGMVolume;}

const bool SettingsManager::getFXSwitch() const {return m_fxsound;}

void SettingsManager::flipMusicSwitch() {
    m_music = !m_music;
}

void SettingsManager::setVolume(const int volume) {
    m_volume = volume;
}

void SettingsManager::setBGMusicVolume(const int volume) {
    m_BGMVolume = volume;
}

void SettingsManager::flipFXSwitch() {
    m_fxsound = !m_fxsound;
}


