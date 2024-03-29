#include <../include/Menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/GameController.h"

int Menu::m_lastClick = -1;
bool Menu::canPlay;

/**
 * create menu and run.
 * init all the components on the screen.
 * show the menu to the screen.
 */
Menu::Menu() : m_menuWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "Pacman", sf::Style::Close | sf::Style::Titlebar) {
    m_menuWindow.setFramerateLimit(60);
    m_inputText.setFont(ResourcesManager::instance().getFont());
    m_inputText.setPosition(WINDOW_WIDTH / 3,WINDOW_HEIGHT/2);
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

    enterPassword();
    eventGetter();
}

/**
 * print the menu to the screen.
 */
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

    SoundFlip::instance().draw(m_menuWindow);
    m_menuWindow.display();
}

/**
 * event handler,
 * zoom buttons when hovered,
 * click handler,
 * close the window.
 */
void Menu::eventGetter() {
    printWindow();
    while (m_menuWindow.isOpen()) {
        if (auto event = sf::Event{}; m_menuWindow.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:{
                    m_menuWindow.close();
                    SettingsManager::instance().save_settings();
                    break;
                }
                case sf::Event::MouseMoved:
                    handleMove(event.mouseMove);
                    break;
                case sf::Event::MouseButtonReleased:
                    handleClick(event.mouseButton);
                    break;
                case sf::Event::KeyPressed:
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        m_menuWindow.close();
                    break;
            }
        }
        printWindow();
    }
}

/**
 * handle mouse click.
 * @param clickevent event
 */
void Menu::handleClick(const sf::Event::MouseButtonEvent &clickevent) {
    SoundFlip::instance().checkIfContains(clickevent);
    for (int i = 0; i < MENU_BUTTONS; i++) {
        if (m_buttons[i].getGlobalBounds().contains(m_menuWindow.mapPixelToCoords({clickevent.x, clickevent.y}))) {
            if (m_lastClick == i)
                break;
            switch (i) {
                case PLAY: {
                    if(!canPlay)
                        break;
                    ResourcesManager::instance().playSound(START_SOUND);
                    auto controller = GameController(m_menuWindow);
                    controller.run();
                }
                    break;
                case LEADERBOARD:{
                    auto leader = LeaderBoard(m_menuWindow);
                    leader.print();
                    break;
                }
                    break;
                case ADDSTAGE: {
                    if(m_adminMod){
                        m_lastClick = i;
                        pid_t status;
                        status = fork();
                        if (status == 0) {
                            auto str = std::to_string(SettingsManager::instance().getMusicSwitch());
                            char * c = str.data();
                            char *argv[1000] = {"./oop1_ex04",c,NULL};
                            if (execvp(argv[0],argv) != 0) {
                                perror("execvp() failed");
                                exit(EXIT_FAILURE);
                            }
                            exit(EXIT_SUCCESS);
                        }
                    }
                    break;
                }
                case HELP:
                    HelpScreenPrint();
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

/**
 * handle mouse movement.
 * @param moveevent event
 */
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

/**
 * set signal handlers for communication with the level editor
 */
void Menu::setSignal() {
    signal(SIGUSR1, Menu::myHandlersigusr1);
    signal(SIGUSR2, Menu::myHandlersigusr2);
}

/**
 * signal handler for SIGUSR1, use to know when the level editor closed.
 * @param signum signal code
 */
void Menu::myHandlersigusr1(int signum) {
    signal(SIGUSR1, Menu::myHandlersigusr1);
    m_lastClick = -1;
    canPlay = std::filesystem::exists("lvl_1.txt");
}

/**
 * signal handler for SIGUSR2, use to know if the level editor flip the sound switch.
 * @param signum signal code
 */
void Menu::myHandlersigusr2(int signum) {
    signal(SIGUSR2, Menu::myHandlersigusr2);
    SettingsManager::instance().flipMusicSwitch();
    ResourcesManager::instance().updateSounds();
}

/**
 * print the help screen to the window.
 */
void Menu::HelpScreenPrint() {
    m_menuWindow.clear();
    m_helpRect.setSize(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
    m_helpRect.setTexture(ResourcesManager::instance().getHelpScreen());
    m_menuWindow.draw(m_helpRect);
    m_menuWindow.display();
    while(m_menuWindow.isOpen()){
        auto event = sf::Event{};
        m_menuWindow.waitEvent(event);
        if(event.type == event.KeyReleased)
            return;
    }

}

void Menu::enterPassword() {

    printInitialScreen();
    std::string tempinput;
    std::string hidden;
    while (m_menuWindow.isOpen()) {
        auto event = sf::Event{};
        m_menuWindow.waitEvent(event);
        if (event.type == sf::Event::Closed)
            m_menuWindow.close();
        if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Escape)
            return;
        if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::BackSpace) {
            if (!tempinput.empty()) {
                hidden.pop_back();
                tempinput.pop_back();
                std::cout << tempinput << "\n";
                m_inputText.setString(hidden);
                printInitialScreen();
            }
            continue;
        }
        if (event.type == event.KeyPressed && event.key.code == sf::Keyboard::Enter) {
            const char *c = tempinput.c_str();
            const char *d = password.c_str();
            if (strcmp(c, d) == 0)
                m_adminMod = true;
            return;
        }
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == ' ' || event.text.unicode == '\b')
                continue;
            if (tempinput.size() < 20){
                tempinput += event.text.unicode;
                hidden += '*';
            }
            m_inputText.setString(hidden);
            printInitialScreen();
        }
    }
}
void Menu::printInitialScreen() {
    m_menuWindow.clear();
    auto background = sf::RectangleShape();
    background.setSize(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
    background.setTexture(ResourcesManager::instance().getPassScreen());
    m_menuWindow.draw(background);
    m_menuWindow.draw(m_inputText);
    m_menuWindow.display();
}

