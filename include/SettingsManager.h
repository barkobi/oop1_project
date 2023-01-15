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
    const bool getMusicSwitch() const;
    const bool getFXSwitch() const;
    void flipMusicSwitch();
    void flipFXSwitch();
    void setVolume(const int volume);
    void setBGMusicVolume(const int volume);
    void save_settings();

private:
    int m_volume, m_BGMVolume;

    bool m_fxsound,m_music;

    SettingsManager();
    void load_settings();

};
