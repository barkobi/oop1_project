#include "SettingsManager.h"
#include "ResourcesManager.h"

// enum for sound buttons
enum Sound_buttons_t{
    MUSIC,
    SOUND
};

/**
 * Singleton class for the sound switches.
 */
class SoundFlip {
public:
    // Functions
    static SoundFlip& instance();
    void draw(sf::RenderWindow &window);
    void checkIfContains(const sf::Event::MouseButtonEvent& event);
private:
    // private C-Tor
    SoundFlip();
    // members
    sf::CircleShape m_soundButtons[2];
    int m_fxClicked = 0,m_musicClicked = 0;
};


