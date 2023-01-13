#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "ResourcesManager.h"

class SettingsManager {
public:
    static SettingsManager& instance();

    const int getVolume() const;
    const int getBGMVolume() const;
    const bool getSoundSwitch() const;
    void flipSoundSwitch();
    void setVolume(const int volume);
    void setBGMusicVolume(const int volume);
    void save_settings();

private:
    int m_volume, m_BGMVolume;

    bool m_sound;

    SettingsManager();
    void load_settings();

};
