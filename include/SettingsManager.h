#pragma once

#include <fstream>

class SettingsManager {
public:
    static SettingsManager& instance();

    const int getVolume() const;
    const bool getSoundSwitch() const;
    void flipSoundSwitch();

private:
    std::ifstream m_settings_file;
    int m_volume;
    bool m_sound;

    SettingsManager();
    void load_settings();
    void save_settings();

};
