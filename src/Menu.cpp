#include <../include/Menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/GameController.h"

int Menu::m_lastClick = -1;
bool Menu::canPlay;

Menu::Menu() : m_menuWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "Pacman", sf::Style::Close | sf::Style::Titlebar) {
    m_menuWindow.setFramerateLimit(60);
    setSignal();
    ResourcesManager::instance().playBackgroundMusic();
    canPlay = std::filesystem::exists("lvl_1.txt");

    m_title.setTexture(ResourcesManager::instance().getTitle());
    m_title.setPosition(50,100);
    m_title.setSize(sf::Vector2f (420,77));

    float menu_h = WINDOW_HEIGHT * 0.7;
    float btn_h = (menu_h / MENU_BUTTONS) * 0.75;
    btn_h += (btn_h * 0.25) / (MENU_BUTTONS - 1);

    float proportion = MENU_BUTTON_WIDTH_ORIGINAL / MENU_BUTTON_HEIGHT_ORIGINAL;
    float btn_w = btn_h * proportion;

    m_scaleHeight = btn_h / MENU_BUTTON_HEIGHT_ORIGINAL;
    m_scaleWidth = btn_w / MENU_BUTTON_WIDTH_ORIGINAL;

    float menu_top_y = (WINDOW_HEIGHT * 0.08) + btn_h / 2;
    float menu_x = (float) WINDOW_WIDTH / 2;

    for (int i = 0; i < MENU_BUTTONS; i++) {
        m_buttons[i].setPosition(menu_x, menu_top_y);
        m_buttons[i].setTexture(*ResourcesManager::instance().getMenuTexture(i));
        m_buttons[i].setOrigin(sf::Vector2f(MENU_BUTTON_WIDTH_ORIGINAL / 2,
                                            MENU_BUTTON_HEIGHT_ORIGINAL / 2));
        m_buttons[i].setScale(m_scaleWidth, m_scaleHeight);

        menu_top_y += btn_h + btn_h * 0.25;
    }

    eventGetter();
}

void Menu::printWindow() {

    m_menuWindow.clear();
    auto background = sf::RectangleShape();
    background.setSize(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
    background.setTexture(ResourcesManager::instance().getBackground());

    m_menuWindow.draw(background);
    m_menuWindow.draw(m_title);
    for (int i = 0; i < MENU_BUTTONS; i++) {
        if(i == PLAY && !canPlay)
            continue;
        m_menuWindow.draw(m_buttons[i]);
    }

    m_menuWindow.display();
}

void Menu::eventGetter() {
    printWindow();
    while (m_menuWindow.isOpen()) {
        if (auto event = sf::Event{}; m_menuWindow.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    m_menuWindow.close();
                    break;
                case sf::Event::MouseMoved:
                    handleMove(event.mouseMove);
                    break;
                case sf::Event::MouseButtonReleased:
                    handleClick(event.mouseButton);
                    break;
                case sf::Event::KeyPressed:
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
                        SettingsManager::instance().flipSoundSwitch();
                        ResourcesManager::instance().updateMusic();
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        m_menuWindow.close();
                    break;
                }
            }
        }
        printWindow();
    }
}

void Menu::handleClick(const sf::Event::MouseButtonEvent &clickevent) {

    for (int i = 0; i < MENU_BUTTONS; i++) {
        if (m_buttons[i].getGlobalBounds().contains(m_menuWindow.mapPixelToCoords({clickevent.x, clickevent.y}))) {
            if (m_lastClick == i)
                break;
            switch (i) {
                case PLAY: {
                    if(!canPlay)
                        break;
                    m_menuWindow.clear(sf::Color(10, 0, 12, 200));
                    m_menuWindow.display();
                    auto controller = GameController(m_menuWindow);
                    controller.run();
                }
                    break;
                case LEADERBOARD:
                    break;
                case ADDSTAGE: {
                    m_lastClick = i;
                    pid_t status;
                    status = fork();
                    if (status == 0) {
                        if (execvp("./oop1_ex04", 0) != 0) {
                            perror("execvp() failed");
                            exit(EXIT_FAILURE);
                        }
                        exit(EXIT_SUCCESS);
                    }
                    break;
                }
                case HELP:
                    break;
                case SETTINGS: {
                    SettingsScreen settingsScreen = SettingsScreen(m_menuWindow);
                    break;
                }
                case QUIT:
                    m_menuWindow.close();
                    break;
            }
        }
    }
}

void Menu::handleMove(const sf::Event::MouseMoveEvent &moveevent) {
    static int btn_sound = -1;
    static int lastHovered = 0;
    m_buttons[lastHovered].setScale(m_scaleWidth, m_scaleHeight);
    bool onBtn = false;
    for (int i = 0; i < MENU_BUTTONS; i++) {
        if(i==PLAY && !canPlay)
            continue;
        if (m_buttons[i].getGlobalBounds().contains(m_menuWindow.mapPixelToCoords({moveevent.x, moveevent.y}))) {
            if (btn_sound != i) {
                ResourcesManager::instance().playSound(MENU_SOUND);
                btn_sound = i;
            }
            onBtn = true;
            lastHovered = i;
            m_buttons[i].setScale(m_scaleWidth * 1.1, m_scaleHeight * 1.1);
            break;
        }
    }
    if (!onBtn)
        btn_sound = -1;
}

void Menu::setSignal() {
    signal(SIGUSR1, Menu::myHandler);
}

void Menu::myHandler(int signum) {
    signal(SIGUSR1, Menu::myHandler);
    m_lastClick = -1;
    canPlay = std::filesystem::exists("lvl_1.txt");
}
