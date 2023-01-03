#include <../include/Menu.h>

Menu::Menu() : m_menuWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),
                            "Pacman",sf::Style::Close | sf::Style::Titlebar){

    float menu_h = WINDOW_HEIGHT*0.7;
    float btn_h = (menu_h/MENU_BUTTONS) * 0.75;
    btn_h += (btn_h*0.25)/(MENU_BUTTONS-1);

    float proportion = MENU_BUTTON_WIDTH_ORIGINAL/MENU_BUTTON_HEIGHT_ORIGINAL;
    float btn_w = btn_h * proportion;

    m_scaleHeight = btn_h/MENU_BUTTON_HEIGHT_ORIGINAL;
    m_scaleWidth = btn_w/MENU_BUTTON_WIDTH_ORIGINAL;

    float menu_top_y = (WINDOW_HEIGHT*0.15) + btn_h/2;
    float menu_x = (float)WINDOW_WIDTH/2;

    for(int i = 0;i < MENU_BUTTONS;i++){
        m_buttons[i].setPosition(menu_x,menu_top_y);
        m_buttons[i].setTexture(*ResourcesManager::instance().getTexture(i));
        m_buttons[i].setOrigin(sf::Vector2f(MENU_BUTTON_WIDTH_ORIGINAL/2,
                                            MENU_BUTTON_HEIGHT_ORIGINAL/2));
        m_buttons[i].setScale(m_scaleWidth,m_scaleHeight);

        menu_top_y+=btn_h + btn_h*0.25;
    }

    eventGetter();
}

void Menu::printWindow() {
    m_menuWindow.clear(sf::Color(10,0,12,200));
    for(int i = 0;i < MENU_BUTTONS;i++)
    {
        m_menuWindow.draw(m_buttons[i]);
    }

    m_menuWindow.display();
}

void Menu::eventGetter() {
    printWindow();
    while(m_menuWindow.isOpen())
    {
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
            }
        }
        printWindow();
    }

}

void Menu::handleClick(const sf::Event::MouseButtonEvent &clickevent) {
    static sf::Sound sound;
    sound.setLoop(false);
    sound.setBuffer(ResourcesManager::instance().getSound(0));
    sound.setVolume(100);
    sound.stop();
    sound.play();

    for(int i = 0;i < MENU_BUTTONS;i++)
    {
        if(m_buttons[i].getGlobalBounds().contains(m_menuWindow.mapPixelToCoords({clickevent.x,clickevent.y})))
        {
            switch (i) {
                case PLAY:
                    break;
                case LEADERBOARD:
                    break;
                case ADDSTAGE:
                    break;
                case HELP:
                    break;
                case SETTINGS:
                    break;
                case QUIT:
                    m_menuWindow.close();
                    break;
            }
        }
    }
}

void Menu::handleMove(const sf::Event::MouseMoveEvent &moveevent){
    static sf::Sound sound;
    sound.setLoop(false);
    sound.setBuffer(ResourcesManager::instance().getSound(0));
    sound.setVolume(100);

    static int lastHovered = 0;
    m_buttons[lastHovered].setScale(m_scaleWidth,m_scaleHeight);

    for(int i = 0;i < MENU_BUTTONS;i++)
    {
        if(m_buttons[i].getGlobalBounds().contains(m_menuWindow.mapPixelToCoords({moveevent.x,moveevent.y}))){
            lastHovered = i;
            m_buttons[i].setScale(m_scaleWidth*1.1,m_scaleHeight*1.1);
            if(sound.getStatus() != sf::SoundSource::Playing){
                sound.setPlayingOffset(sf::microseconds(0.f));
                sound.play();
            }
        }
    }
}



