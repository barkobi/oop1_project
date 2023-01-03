#pragma once

#include <SFML/Graphics.hpp>
#include <string.h>

const int OBJECTS = 10;
const int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height * 0.7;
const int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width * 0.7;

// level editor sidebar size
const int MENU_WIDTH =  sf::VideoMode::getDesktopMode().width * 0.1;
const int MENU_START = sf::VideoMode::getDesktopMode().height * 0.1;
const int MENU_BUTTONS = 6;
const int NUMBER_OF_SOUNDS = 2;
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

enum Sounds{
    MENU_HOVER,
    START_GAME
};