#include "SettingsScreen.h"

SettingsScreen::SettingsScreen(sf::RenderWindow &window) : m_window(window) {

    m_font.loadFromFile("/Library/Fonts/Arial Unicode.ttf");
    auto volume = SettingsManager::instance().getVolume();
    std::string str = "volume: ";
    m_volume_text.setString(str + std::to_string(volume));
    m_volume_text.setPosition(WINDOW_WIDTH/2 , WINDOW_HEIGHT/2);
    m_volume_text.setFillColor(sf::Color::White);
    m_volume_text.setFont(m_font);

    m_sound_text.setString("sound: ");
    m_sound_text.setPosition(WINDOW_WIDTH/2 , (WINDOW_HEIGHT/2)-50);
    m_sound_text.setFillColor(sf::Color::White);
    m_sound_text.setFont(m_font);

    m_checkBox.setPosition(m_sound_text.getPosition().x + m_sound_text.getLocalBounds().width ,m_sound_text.getPosition().y + m_sound_text.getLocalBounds().height/2);
    m_checkBox.setSize(sf::Vector2f(m_sound_text.getLocalBounds().height,m_sound_text.getLocalBounds().height));
    m_checkBox.setOutlineColor(sf::Color::White);
    m_checkBox.setFillColor(SettingsManager::instance().getSoundSwitch() ? sf::Color::White : sf::Color::Transparent);
    m_checkBox.setOutlineThickness(2);

    m_volume_line.setSize(sf::Vector2f(300,5));
    m_volume_line.setFillColor(sf::Color::White);
    m_volume_line.setPosition(m_volume_text.getPosition().x+m_volume_text.getGlobalBounds().width+20, m_volume_text.getPosition().y+m_volume_text.getGlobalBounds().height);
    m_volume_drag.setRadius(10);
    m_volume_drag.setPosition(m_volume_line.getPosition().x + volume*3 ,m_volume_line.getPosition().y);
    m_volume_drag.setOrigin(5,5);
    m_volume_drag.setFillColor(sf::Color::White);
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
            }
        }

        m_window.clear();

        m_checkBox.setFillColor(SettingsManager::instance().getSoundSwitch() ? sf::Color::White : sf::Color::Transparent);
        int vol = m_volume_drag.getPosition().x - m_volume_line.getPosition().x;
        std::string str = "volume: ";
        m_volume_text.setString(str + std::to_string(vol/3));

        m_window.draw(m_volume_line);
        m_window.draw(m_volume_drag);
        m_window.draw(m_checkBox);
        m_window.draw(m_volume_text);
        m_window.draw(m_sound_text);
        m_window.display();

    }
    SettingsManager::instance().save_settings();
}

bool SettingsScreen::handleClick(const sf::Event::MouseButtonEvent &clickevent) {
    if(m_volume_clicked){
        m_volume_clicked = false;
        int vol = m_volume_drag.getPosition().x - m_volume_line.getPosition().x;
        SettingsManager::instance().setVolume(vol/3);
        return true;
    }

    if(m_checkBox.getGlobalBounds().contains(clickevent.x,clickevent.y))
        SettingsManager::instance().flipSoundSwitch();
    else
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