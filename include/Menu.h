#pragma once

#include <SFML/Graphics.hpp>
#include "ResourcesManager.h"
#include "SettingsScreen.h"


const int MENU_BUTTON_WIDTH_ORIGINAL = 500;
const int MENU_BUTTON_HEIGHT_ORIGINAL = 130;

enum Menu_buttons_t{
    PLAY,
    LEADERBOARD,
    ADDSTAGE,
    HELP,
    SETTINGS,
    QUIT
};
class Menu {
public:
    Menu();
    void eventGetter();
    void printWindow();
    void handleClick(const sf::Event::MouseButtonEvent &clickevent);
    void handleMove(const sf::Event::MouseMoveEvent &moveevent);
private:
    sf::RenderWindow m_menuWindow;
    sf::Sprite m_buttons[MENU_BUTTONS];

    float m_scaleHeight, m_scaleWidth;
};