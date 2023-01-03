#include <SFML/Graphics.hpp>
#include "../include/ResourcesManager.h"


const int MENU_BUTTON_WIDTH = 500;
const int MENU_BUTTON_HEIGHT = 130;
const int MENU_BUTTON_W_INC = 550;
const int MENU_BUTTON_H_INC = 170;


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
    void EventGetter();
    void printWindow();
    void HandleClick(const sf::Event::MouseButtonEvent &clickevent);
    void HandleMove(const sf::Event::MouseMoveEvent &moveevent);
    void ButtonAnimation(sf::RectangleShape &rect);
private:
    sf::RenderWindow m_menuWindow;
    sf::Sprite m_buttons[MENU_BUTTONS];

    int m_lastMove;
};