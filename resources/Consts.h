#pragma once

#include <SFML/Graphics.hpp>
#include <string.h>

const int OBJECTS = 13;
const int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height * 0.85;
const int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width * 0.85;

// level editor sidebar size
const int MENU_BUTTONS = 6;
const int NUMBER_OF_SOUNDS = 5;

//const float SPEED = WINDOW_WIDTH / 18;

const int IMAGE_DIMENSIONS = 512;

enum Sounds_t{
    MENU_SOUND,
    START_SOUND,
    CHEW_SOUND,
    OPEN_DOOR,
    GOT_GIFT
};

enum Characters {
    PACMAN,
    SUPERPACMAN,
    KEY,
    RANDOMGHOST,
    SMARTGHOST,
    SUPERPMGHOST,
    DOOR,
    WALL,
    COOKIE,
    SUPER_PM_GIFT,
    GHOST_FREEZE_GIFT,
    ADD_LIFE_GIFT,
    ADD_TIME_GIFT
};