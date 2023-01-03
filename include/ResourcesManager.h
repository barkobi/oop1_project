#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../resources/Consts.h"
#include <string.h>
class ResourcesManager{
public:
    static ResourcesManager& instance();
    sf::Font getFont();
    sf::Texture* getTexture(const int loc);
    sf::SoundBuffer* getSound(const int index);
    void playSound(const int index);

private:
    ResourcesManager();
    sf::Font m_font;
    sf::SoundBuffer m_sounds[NUMBER_OF_SOUNDS];
    sf::Sound m_sounds[NUMBER_OF_SOUNDS];
    sf::SoundBuffer m_sounds_buffs[NUMBER_OF_SOUNDS];
    sf::Texture m_textures[NUMBER_OF_TEXTURES];
    std::string m_buttonString[NUMBER_OF_TEXTURES] = {"PlayButton","LeaderBoardButton","AddStageButton",
                                                      "HelpButton","SettingsButton","QuitButton"};
    std::string m_sound_file_names[NUMBER_OF_SOUNDS] = {"menu_hover.wav","start_game.wav"};
};