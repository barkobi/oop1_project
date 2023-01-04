#pragma once

#include <fstream>
#include <iostream>
#include <string>

class SettingsManager {
public:
    static SettingsManager& instance();

    const int getVolume() const;
    const bool getSoundSwitch() const;
    void flipSoundSwitch();
    void save_settings();

private:
    int m_volume;

    bool m_sound;

    SettingsManager();
    void load_settings();

};
