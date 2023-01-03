#include <SFML/Graphics.hpp>
#include <string.h>
const int OBJECTS = 10;
const int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height / 1.3;
const int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width / 1.3;
const int MENU_WIDTH =  sf::VideoMode::getDesktopMode().width / 10;
const int MENU_START = sf::VideoMode::getDesktopMode().height / 10;
const int MENU_BUTTONS = 6;
const int NUMBER_OF_SOUNDS = 1;
const int NUMBER_OF_TEXTURES = 6;

enum Characters {
    PACMAN,
    GHOST,
    GIFT,
    KEY,
    COOKIE,
    DOOR,
    WALL,
    ERASE,
    DELETE,
    SAVE
};