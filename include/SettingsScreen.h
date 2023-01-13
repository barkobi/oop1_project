#pragma once
#include "SFML/Graphics.hpp"
#include "SettingsManager.h"
#include "../resources/Consts.h"

class SettingsScreen{
public:
    SettingsScreen(sf::RenderWindow& window);

private:
    sf::RenderWindow& m_window;
    sf::Text m_volume_text, m_music_text;
    sf::Text m_sound_text;
    sf::CircleShape m_volume_drag;
    sf::RectangleShape m_volume_line;
    sf::CircleShape m_music_drag;
    sf::RectangleShape m_music_line;
    sf::Text m_backBtn;

    sf::RectangleShape m_checkBox;
    bool m_volume_clicked = false;
    bool m_music_clicked = false;

    void run();
    bool handleClick(const sf::Event::MouseButtonEvent &clickevent);
    void handleMouseMove(const sf::Event::MouseMoveEvent &moveevent);
    void eventHandler(bool &exit);
    void printScreen();
};