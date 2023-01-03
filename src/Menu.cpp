#include <../include/Menu.h>
#include <iostream>
Menu::Menu() : m_menuWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width / 1.3,sf::VideoMode::getDesktopMode().height / 1.3),
                            "Pacman",sf::Style::Close | sf::Style::Titlebar),m_lastMove(0){
    for(int i = 0;i < MENU_BUTTONS;i++)
    {
        m_buttons[i].setPosition(float(WINDOW_WIDTH / 2),float(i * (MENU_BUTTON_HEIGHT + MENU_BUTTON_HEIGHT / 2) + MENU_START + 90));
        m_buttons[i].setTexture(*ResourcesManager::instance().getTexture(i));
        m_buttons[i].setOrigin(sf::Vector2f(MENU_BUTTON_WIDTH / 2,
                                            MENU_BUTTON_HEIGHT / 2));

    }
}

void Menu::printWindow() {
    m_menuWindow.clear(sf::Color(10,0,12,200));
    for(int i = 0;i < MENU_BUTTONS;i++)
    {
        m_menuWindow.draw(m_buttons[i]);
    }

    m_menuWindow.display();


}

void Menu::EventGetter() {

    printWindow();
    while(m_menuWindow.isOpen())
    {
        if (auto event = sf::Event{}; m_menuWindow.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    m_menuWindow.close();
                    break;
                case sf::Event::MouseMoved:
                    HandleMove(event.mouseMove);
                    break;
                case sf::Event::MouseButtonReleased:
                    HandleClick(event.mouseButton);
            }
        }
        printWindow();
    }

}

void Menu::HandleClick(const sf::Event::MouseButtonEvent &clickevent) {

    for(int i = 0;i < MENU_BUTTONS;i++)
    {
        if(m_buttons[i].getGlobalBounds().contains(m_menuWindow.mapPixelToCoords({clickevent.x,clickevent.y})))
        {
            switch (i) {
                case PLAY:
                    ;
                case LEADERBOARD:
                    ;
                case ADDSTAGE:
                    ;
                case HELP:
                    ;
                case SETTINGS:
                    ;
                case QUIT:
                    m_menuWindow.close();
                    break;
            }
        }
    }
}

void Menu::HandleMove(const sf::Event::MouseMoveEvent &moveevent) {
    m_buttons[m_lastMove].setScale(1,1);

    for(int i = 0;i < MENU_BUTTONS;i++)
    {
        if(m_buttons[i].getGlobalBounds().contains(m_menuWindow.mapPixelToCoords({moveevent.x,moveevent.y}))){
            m_lastMove = i;
            m_buttons[i].setScale(1.1f,1.1f);
            sf::sleep(sf::microseconds(80));
        }
    }
}



