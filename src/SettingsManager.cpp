
#include "SettingsManager.h"

SettingsManager::SettingsManager() {
    m_settings_file.open("../../../settings.txt");
    if(!m_settings_file.is_open()){
        perror("Cannot open settings file");
        exit(EXIT_FAILURE);
    }
    load_settings();
}

SettingsManager& SettingsManager::instance() {
    static SettingsManager settings;
    return settings;
}

void SettingsManager::load_settings() {
    m_settings_file.seekg(0);
    m_settings_file >> m_sound;
    m_settings_file >> m_volume;
}

void SettingsManager::save_settings() {
//    m_settings_file.seekp(0);
//    m_settings_file << m_sound << " " << m_volume;
}

const bool SettingsManager::getSoundSwitch() const {return m_sound;}

const int SettingsManager::getVolume() const {return m_volume;}

void SettingsManager::flipSoundSwitch() {
    m_sound = !m_sound;
}
