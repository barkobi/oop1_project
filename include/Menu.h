#pragma once

#include <SFML/Graphics.hpp>
#include "ResourcesManager.h"
#include "SettingsScreen.h"
#include "SoundFlip.h"
#include "../include/ResourcesManager.h"
#include "signal.h"
#include "LeaderBoard.h"

const int MENU_BUTTON_WIDTH_ORIGINAL = 500;
const int MENU_BUTTON_HEIGHT_ORIGINAL = 130;

// enum for menu buttons
enum Menu_buttons_t{
    PLAY,
    LEADERBOARD,
    ADDSTAGE,
    HELP,
    SETTINGS,
    QUIT
};
/**
 * Menu class that responsible for loading and handling the menu screen
 */
class Menu {
public:
    // C-Tor
    Menu();
    // Functions
    void eventGetter();
    void printWindow();
    void printInitialScreen();
    void handleClick(const sf::Event::MouseButtonEvent &clickevent);
    void handleMove(const sf::Event::MouseMoveEvent &moveevent);
    void HelpScreenPrint();
    void enterPassword();
    // signal handlers
    void setSignal ();
    static void myHandlersigusr1 (int signum);
    static void myHandlersigusr2 (int signum);

private:
    // memebres
    bool m_adminMod = false;
    const std::string password = "123456";
    sf::Text m_inputText;
    sf::RenderWindow m_menuWindow;
    sf::RectangleShape m_title;
    sf::RectangleShape m_helpRect;
    sf::Sprite m_buttons[MENU_BUTTONS];
    sf::SoundBuffer m_soundBuffer;
    sf::Sound m_sound;
    float m_scaleHeight, m_scaleWidth;
    static int m_lastClick;
    static bool canPlay;
};
