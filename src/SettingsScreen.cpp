#include "SettingsScreen.h"
#include "SoundFlip.h"

SettingsScreen::SettingsScreen(sf::RenderWindow &window) : m_window(window) {

    auto volume = SettingsManager::instance().getVolume();
    std::string str = "volume: ";
    m_volume_text.setString(str + std::to_string(volume));
    m_volume_text.setPosition(WINDOW_WIDTH/2 , WINDOW_HEIGHT*0.4);
    m_volume_text.setFillColor(sf::Color::White);
    m_volume_text.setFont(ResourcesManager::instance().getFont());

    m_volume_line.setSize(sf::Vector2f((WINDOW_WIDTH - (m_volume_text.getPosition().x + m_volume_text.getGlobalBounds().width))*0.5,5));
    m_volume_line.setFillColor(sf::Color::White);
    m_volume_line.setPosition(m_volume_text.getPosition().x+m_volume_text.getGlobalBounds().width*1.3, m_volume_text.getPosition().y+(m_volume_text.getGlobalBounds().height/2)-5);

    auto width = (m_volume_line.getPosition().x + m_volume_line.getGlobalBounds().width)- m_volume_text.getPosition().x;
    m_volume_text.move(-(width/2),0);
    m_volume_line.move(-(width/2),0);

    m_volume_drag.setRadius(20);
    m_volume_drag.setPosition(m_volume_line.getPosition().x + ((m_volume_line.getGlobalBounds().width)* volume/100) ,m_volume_line.getPosition().y-m_volume_line.getSize().y);
    m_volume_drag.setOrigin(m_volume_drag.getRadius()/2,m_volume_drag.getRadius()/2);
    m_volume_drag.setFillColor(sf::Color::White);

    str = "music: ";
    volume = SettingsManager::instance().getBGMVolume();
    m_music_text.setString(str + std::to_string(volume));
    m_music_text.setPosition(m_volume_text.getPosition().x , m_volume_text.getPosition().y + (m_volume_text.getGlobalBounds().height*4));
    m_music_text.setFillColor(sf::Color::White);
    m_music_text.setFont(ResourcesManager::instance().getFont());

    m_music_line.setSize(m_volume_line.getSize());
    m_music_line.setFillColor(sf::Color::White);
    m_music_line.setPosition(m_volume_line.getPosition().x, m_music_text.getPosition().y+(m_music_text.getGlobalBounds().height/2)-5);

    m_music_drag.setRadius(20);
    m_music_drag.setPosition(m_music_line.getPosition().x + ((m_music_line.getGlobalBounds().width)* volume/100) ,m_music_line.getPosition().y-m_music_line.getSize().y);
    m_music_drag.setOrigin(m_music_drag.getRadius()/2,m_music_drag.getRadius()/2);
    m_music_drag.setFillColor(sf::Color::White);

    m_backBtn.setString("<-");
    m_backBtn.setFont(ResourcesManager::instance().getFont());
    m_backBtn.setCharacterSize(40);
    m_backBtn.setPosition(WINDOW_WIDTH*0.05,WINDOW_WIDTH*0.05);
    m_backBtn.setFillColor(sf::Color::White);


    run();
}

void SettingsScreen::run() {
    bool exit = false;
    while (m_window.isOpen() && !exit){
        eventHandler(exit);
        printScreen();
    }
    SettingsManager::instance().save_settings();
}

bool SettingsScreen::handleClick(const sf::Event::MouseButtonEvent &clickevent) {
    if (m_volume_clicked) {
        m_volume_clicked = false;
    }
    else if(m_music_clicked)
        m_music_clicked = false;

    else if(m_backBtn.getGlobalBounds().contains(clickevent.x,clickevent.y))
        return false;

    SoundFlip::instance().checkIfContains(clickevent);

    return true;
}

void SettingsScreen::handleMouseMove(const sf::Event::MouseMoveEvent &moveevent) {
    if(m_volume_clicked){
        m_volume_drag.setPosition(moveevent.x, m_volume_drag.getPosition().y);
        if(m_volume_drag.getPosition().x < m_volume_line.getPosition().x)
            m_volume_drag.setPosition(m_volume_line.getPosition().x, m_volume_drag.getPosition().y);
        else if(m_volume_drag.getPosition().x > m_volume_line.getPosition().x+m_volume_line.getGlobalBounds().width)
            m_volume_drag.setPosition(m_volume_line.getPosition().x+m_volume_line.getGlobalBounds().width, m_volume_drag.getPosition().y);

        int vol = ((m_volume_drag.getPosition().x - m_volume_line.getPosition().x) /(m_volume_line.getGlobalBounds().width))*100;
        SettingsManager::instance().setVolume(vol);
    }
    else if(m_music_clicked){
        m_music_drag.setPosition(moveevent.x, m_music_drag.getPosition().y);
        if(m_music_drag.getPosition().x < m_music_line.getPosition().x)
            m_music_drag.setPosition(m_music_line.getPosition().x, m_music_drag.getPosition().y);
        else if(m_music_drag.getPosition().x > m_music_line.getPosition().x+m_music_line.getGlobalBounds().width)
            m_music_drag.setPosition(m_music_line.getPosition().x+m_music_line.getGlobalBounds().width, m_music_drag.getPosition().y);

        int vol = ((m_music_drag.getPosition().x - m_music_line.getPosition().x) /(m_music_line.getGlobalBounds().width))*100;
        SettingsManager::instance().setBGMusicVolume(vol);
        ResourcesManager::instance().updateSounds();
    }


}

void SettingsScreen::eventHandler(bool &exit) {
    if (auto event = sf::Event{}; m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::MouseButtonReleased:
                exit = !handleClick(event.mouseButton);
                break;
            case sf::Event::MouseButtonPressed:
                if(m_volume_drag.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y))
                    m_volume_clicked = true;
                if(m_music_drag.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y))
                    m_music_clicked = true;
                break;
            case sf::Event::MouseMoved:
                if(m_volume_clicked || m_music_clicked)
                    handleMouseMove(event.mouseMove);
                break;
            case sf::Event::Closed:
                m_window.close();
                break;
        }
    }
}

void SettingsScreen::printScreen() {
    m_window.clear();
    auto background = sf::RectangleShape();
    background.setSize(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
    background.setTexture(ResourcesManager::instance().getBackground());

    m_window.draw(background);

    int vol = SettingsManager::instance().getVolume();
    std::string str = "volume: ";
    m_volume_text.setString(str + std::to_string(vol));

    vol = SettingsManager::instance().getBGMVolume();
    str = "music: ";
    m_music_text.setString(str + std::to_string(vol));

    m_window.draw(m_volume_line);
    m_window.draw(m_volume_drag);
    m_window.draw(m_volume_text);
    m_window.draw(m_backBtn);
    m_window.draw(m_music_text);
    m_window.draw(m_music_drag);
    m_window.draw(m_music_line);

    SoundFlip::instance().draw(m_window);

    m_window.display();

}