#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "ResourcesManager.h"

/**
 * Singleton class that managing the settings of the game
 */
class SettingsManager {
public:
    static SettingsManager& instance();

    // Functions
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
    // private C-Tor
    SettingsManager();
    //members
    int m_volume, m_BGMVolume;

    bool m_fxsound,m_music;

    // private function
    void load_settings();

};
