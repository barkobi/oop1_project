
#include "SettingsManager.h"

SettingsManager::SettingsManager() {
    load_settings();
}

SettingsManager& SettingsManager::instance(){
    static SettingsManager settings;
    return settings;
}

void SettingsManager::load_settings() {
    std::ifstream settings_file;
    settings_file.open("../../../settings.txt");

    if(!settings_file.is_open()){
        perror("Cannot open settings file");
        exit(EXIT_FAILURE);
    }

    settings_file.seekg(0);
    settings_file >> m_sound;
    settings_file >> m_volume;
    settings_file.close();
}

void SettingsManager::save_settings(){
    std::ofstream settings_file;
//    std::error_code ec;

    std::filesystem::remove("../../../settings.txt");
    settings_file.open("../../../settings.txt");

    if(!settings_file.is_open()){
        perror("Cannot open settings file");
        exit(EXIT_FAILURE);
    }
    settings_file.seekp(0);
    std::cout << m_sound << " " << m_volume << std::endl;
    settings_file << m_sound << " " << m_volume;
    settings_file.close();
}

const bool SettingsManager::getSoundSwitch() const {return m_sound;}

const int SettingsManager::getVolume() const {return m_volume;}

void SettingsManager::flipSoundSwitch() {
    m_sound = !m_sound;
}