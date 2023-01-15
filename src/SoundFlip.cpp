#include "SoundFlip.h"

SoundFlip::SoundFlip() {
    int prevloc = 0;
    for(int i = 0;i < 2;i++){
        m_soundButtons[i].setRadius(WINDOW_WIDTH / 40);
        m_soundButtons[i].setPosition((WINDOW_WIDTH - WINDOW_WIDTH / 7) + prevloc,WINDOW_HEIGHT/20);
        m_soundButtons[i].setTexture(ResourcesManager::instance().getSoundButton(i));
        m_soundButtons[i].setTextureRect(sf::IntRect(0,0,512,512));
        prevloc = m_soundButtons[i].getLocalBounds().width + m_soundButtons[i].getLocalBounds().width/5;
    }
    m_fxClicked = SettingsManager::instance().getFXSwitch();
    m_musicClicked = SettingsManager::instance().getMusicSwitch();
}

SoundFlip &SoundFlip::instance() {
    static SoundFlip inst;
    return inst;
}

void SoundFlip::draw(sf::RenderWindow &m_window) {

    for(int i = 0;i<2;i++)
    {
        if(i == MUSIC)
            if(m_musicClicked)
                m_soundButtons[MUSIC].setTextureRect(sf::IntRect(0,0,512,512));
            else
                m_soundButtons[MUSIC].setTextureRect(sf::IntRect(512,0,512,512));
        if(i == SOUND)
            if(m_fxClicked)
                m_soundButtons[SOUND].setTextureRect(sf::IntRect(0,0,512,512));
            else
                m_soundButtons[SOUND].setTextureRect(sf::IntRect(512,0,512,512));
        m_window.draw(m_soundButtons[i]);
    }
}

void SoundFlip::checkIfContains(const sf::Event::MouseButtonEvent &event) {
    for (int i = 0; i < 2; i++) {
        if (m_soundButtons[i].getGlobalBounds().contains(event.x, event.y)) {
            if(i == MUSIC)
            {
                m_musicClicked = !m_musicClicked;
                SettingsManager::instance().flipMusicSwitch();
                ResourcesManager::instance().updateSounds();
            }

            if(i == SOUND)
            {
                m_fxClicked = !m_fxClicked;
                SettingsManager::instance().flipFXSwitch();
            }

        }
    }
}
