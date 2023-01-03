#include "SettingsScreen.h"

SettingsScreen::SettingsScreen(sf::RenderWindow &window) : m_window(window) {
    display();
}

void SettingsScreen::display() {

    while (m_window.isOpen()){
        if (auto event = sf::Event{}; m_window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::MouseButtonReleased:
                    if(m_checkBox.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y))
                        SettingsManager::instance().flipSoundSwitch();
                    else
                        return;
                    break;
            }
        }

        m_window.clear();

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

        m_window.draw(m_checkBox);
        m_window.draw(m_volume_text);
        m_window.draw(m_sound_text);
        m_window.display();
    }

}
