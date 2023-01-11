#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../resources/Consts.h"
#include <string.h>
#include "SettingsManager.h"


class ResourcesManager {
public:
    static ResourcesManager &instance();

    sf::Font &getFont();

    sf::Texture *getMenuTexture(const int loc);
    sf::Texture *getObjectTexture(const int loc);
    sf::Texture *getBackground();
    sf::Texture *getTitle();

//    sf::SoundBuffer *getSound(const int index);

    void playSound(const int index);
    void playBackgroundMusic();
    void stopBackgroundMusic();
    void updateMusic();

private:
    ResourcesManager();

    sf::Font m_font;
    sf::Sound m_sounds[NUMBER_OF_SOUNDS];
    sf::Music m_backgroundMusic;
    sf::SoundBuffer m_sounds_buffs[NUMBER_OF_SOUNDS];
    sf::Texture m_menuButtonTxt[MENU_BUTTONS];
    sf::Texture m_backGround;
    sf::Texture m_title;
    sf::Texture m_pictures[MENU_BUTTONS];
    std::string m_picturesString[OBJECTS] = { "pacmanSpreadSheet", "Key", "ghostsheet",
                                              "Door", "Wall", "coinsheet", "Gift"};
    std::string m_buttonString[MENU_BUTTONS] = {"PlayButton", "LeaderBoardButton", "AddStageButton",
                                                      "HelpButton", "SettingsButton", "QuitButton"};
    std::string m_sound_file_names[NUMBER_OF_SOUNDS] = {"menu_hover.wav", "start_game.wav","cookieEat.wav"};
};