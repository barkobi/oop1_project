#pragma once

#include <SFML/Graphics.hpp>
#include <string.h>

const int OBJECTS = 9;
const int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height * 0.85;
const int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width * 0.85;

// level editor sidebar size
const int MENU_WIDTH =  sf::VideoMode::getDesktopMode().width * 0.1;
const int MENU_START = sf::VideoMode::getDesktopMode().height * 0.1;
const int MENU_BUTTONS = 6;
const int NUMBER_OF_SOUNDS = 3;
const int NUMBER_OF_TEXTURES = 7;

const float SPEED = WINDOW_WIDTH / 15;

const int IMAGE_DIMENSIONS = 512;

enum Sounds_t{
    MENU_SOUND,
    START_SOUND,
    CHEW_SOUND
};

enum Characters {
    PACMAN,
    SUPERPACMAN,
    KEY,
    RANDOMGHOST,
    SMARTGHOST,
    DOOR,
    WALL,
    COOKIE,
    GIFT
};