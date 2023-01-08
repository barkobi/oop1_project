#include "SettingsScreen.h"

SettingsScreen::SettingsScreen(sf::RenderWindow &window) : m_window(window) {

    auto volume = SettingsManager::instance().getVolume();
    std::string str = "volume: ";
    m_volume_text.setString(str + std::to_string(volume));
    m_volume_text.setPosition(WINDOW_WIDTH/2 , WINDOW_HEIGHT/2);
    m_volume_text.setFillColor(sf::Color::White);
    m_volume_text.setFont(ResourcesManager::instance().getFont());

    m_sound_text.setString("sound: ");
    m_sound_text.setPosition(WINDOW_WIDTH/2 , (WINDOW_HEIGHT/2)-50);
    m_sound_text.setFillColor(sf::Color::White);
    m_sound_text.setFont(ResourcesManager::instance().getFont());

    m_checkBox.setPosition(m_sound_text.getPosition().x + m_sound_text.getLocalBounds().width + 20 ,m_sound_text.getPosition().y);
    m_checkBox.setSize(sf::Vector2f(m_sound_text.getLocalBounds().height,m_sound_text.getLocalBounds().height));
    m_checkBox.setOutlineColor(sf::Color::White);
    m_checkBox.setFillColor(SettingsManager::instance().getSoundSwitch() ? sf::Color::White : sf::Color::Transparent);
    m_checkBox.setOutlineThickness(2);

    m_volume_line.setSize(sf::Vector2f((WINDOW_WIDTH - (m_volume_text.getPosition().x + m_volume_text.getGlobalBounds().width))*0.5,5));
    m_volume_line.setFillColor(sf::Color::White);
    m_volume_line.setPosition(m_volume_text.getPosition().x+m_volume_text.getGlobalBounds().width*1.3, m_volume_text.getPosition().y+(m_volume_text.getGlobalBounds().height/2)-5);

    m_volume_drag.setRadius(20);
    m_volume_drag.setPosition(m_volume_line.getPosition().x + ((m_volume_line.getGlobalBounds().width)* volume/100) ,m_volume_line.getPosition().y-m_volume_line.getSize().y);
    m_volume_drag.setOrigin(m_volume_drag.getRadius()/2,m_volume_drag.getRadius()/2);
    m_volume_drag.setFillColor(sf::Color::White);

    m_backBtn.setString("<-");
    m_backBtn.setFont(ResourcesManager::instance().getFont());
    m_backBtn.setCharacterSize(40);
    m_backBtn.setPosition(WINDOW_WIDTH*0.05,WINDOW_WIDTH*0.05);
    m_backBtn.setFillColor(sf::Color::White);

    display();
}

void SettingsScreen::display() {
    bool exit = false;
    while (m_window.isOpen() && !exit){
        if (auto event = sf::Event{}; m_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::MouseButtonReleased:
                    exit = !handleClick(event.mouseButton);
                    break;
                case sf::Event::MouseButtonPressed:
                    if(m_volume_drag.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y))
                        m_volume_clicked = true;
                    break;
                case sf::Event::MouseMoved:
                    if(m_volume_clicked)
                        handleMouseMove(event.mouseMove);
                    break;
                case sf::Event::Closed:
                    m_window.close();
                    break;

            }
        }

        m_window.clear();
        auto background = sf::RectangleShape();
        background.setSize(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
        background.setTexture(ResourcesManager::instance().getBackground());

        m_window.draw(background);
        m_checkBox.setFillColor(SettingsManager::instance().getSoundSwitch() ? sf::Color::White : sf::Color::Transparent);
        int vol = ((m_volume_drag.getPosition().x - m_volume_line.getPosition().x) /(m_volume_line.getGlobalBounds().width))*100;
        std::string str = "volume: ";
        m_volume_text.setString(str + std::to_string(vol));

        m_window.draw(m_volume_line);
        m_window.draw(m_volume_drag);
        m_window.draw(m_checkBox);
        m_window.draw(m_volume_text);
        m_window.draw(m_sound_text);
        m_window.draw(m_backBtn);

        m_window.display();

    }
    SettingsManager::instance().save_settings();
}

bool SettingsScreen::handleClick(const sf::Event::MouseButtonEvent &clickevent) {
    if (m_volume_clicked) {
        m_volume_clicked = false;
        int vol = ((m_volume_drag.getPosition().x - m_volume_line.getPosition().x) /
                   (m_volume_line.getGlobalBounds().width)) * 100;
        SettingsManager::instance().setVolume(vol);
        ResourcesManager::instance().updateMusic();
    }
    else if (m_checkBox.getGlobalBounds().contains(clickevent.x, clickevent.y)){
        SettingsManager::instance().flipSoundSwitch();
        ResourcesManager::instance().updateMusic();
    }
    else if(m_backBtn.getGlobalBounds().contains(clickevent.x,clickevent.y))
        return false;

    return true;
}

void SettingsScreen::handleMouseMove(const sf::Event::MouseMoveEvent &moveevent) {
    m_volume_drag.setPosition(moveevent.x, m_volume_drag.getPosition().y);
    if(m_volume_drag.getPosition().x < m_volume_line.getPosition().x)
        m_volume_drag.setPosition(m_volume_line.getPosition().x, m_volume_drag.getPosition().y);
    else if(m_volume_drag.getPosition().x > m_volume_line.getPosition().x+m_volume_line.getGlobalBounds().width)
        m_volume_drag.setPosition(m_volume_line.getPosition().x+m_volume_line.getGlobalBounds().width, m_volume_drag.getPosition().y);
}