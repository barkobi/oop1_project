
#include "SettingsManager.h"

SettingsManager::SettingsManager() {
    load_settings();
}

SettingsManager& SettingsManager::instance(){
    static SettingsManager settings;
    return settings;
}

void SettingsManager::load_settings() {
    if(!std::filesystem::exists("settings.txt")){
        m_sound = true;
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
    settings_file >> m_sound;
    settings_file >> m_volume;
    settings_file >> m_BGMVolume;
    settings_file.close();
}

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
    settings_file << m_sound << " " << m_volume << " " << m_BGMVolume;
    settings_file.close();
}

const bool SettingsManager::getSoundSwitch() const {return m_sound;}

const int SettingsManager::getVolume() const {return m_volume;}

const int SettingsManager::getBGMVolume() const {return m_BGMVolume;}


void SettingsManager::flipSoundSwitch() {
    m_sound = !m_sound;
}

void SettingsManager::setVolume(const int volume) {
    m_volume = volume;
}

void SettingsManager::setBGMusicVolume(const int volume) {
    m_BGMVolume = volume;
    ResourcesManager::instance().updateMusic();
}

