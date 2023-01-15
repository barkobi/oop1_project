#include "SettingsManager.h"
#include "ResourcesManager.h"

enum Sound_buttons_t{
    MUSIC,
    SOUND
};

class SoundFlip {
public:
    static SoundFlip& instance();
    void draw(sf::RenderWindow &m_window);
    void checkIfContains(const sf::Event::MouseButtonEvent& event);
private:
    SoundFlip();
    sf::CircleShape m_soundButtons[2];
    int m_fxClicked = 0,m_musicClicked = 0;
};


