#pragma once
#include "SFML/Graphics.hpp"
#include "SettingsManager.h"
#include "../resources/Consts.h"

class SettingsScreen{
public:
    SettingsScreen(sf::RenderWindow& window);

private:
    sf::RenderWindow& m_window;
    sf::Font m_font;
    sf::Text m_volume_text;
    sf::Text m_sound_text;

    sf::RectangleShape m_checkBox;

    void display();
};