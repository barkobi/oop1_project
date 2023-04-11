# OOP1 Project

## Submitted by:
Ofek Gorgi & Bar Kobi

## Exercise description:
On this project we've been requested to create Super Pacman game with SFML library that we had
studied for this semester. In this game you can play as the Pacman character, you move with the arrows
on the keyboard(take a look at the help screen), and you need to collect all coins while various of
ghosts chasing you. when the game starts, you get 3 chances to do so, you can also collect gifts on
the way that gives you advantages. you get 3 levels, admins can add and edit stages.

## File list:
#### Event.h / Event.cpp
Class that builds and manage events in the game.

#### eventLoop.h / eventLoop.cpp
Singleton class of event queue that saves the events.

#### DynamicObjects.h / DynamicObjects.cpp
class of the objects that moves during the game, heiress from GameObject class.

#### Ghost.h / Ghost.cpp
Ghost class heiress from dynamic object.

#### RandomGhost.h / RandomGhost.cpp
Random ghost class heiress from Ghost.

#### SmartGhost.h / SmartGhost.cpp
Smart ghost class heiress from Ghost.

#### Pacman.h / Pacman.cpp
Pacman class heiress from Dynamic object class.

#### pacmanState.h / pacmanState.cpp
abstract class of pacman state, controls the current state of the pacman,
and deals collisions according to state, has two classes heiress from it.

#### StaticObjects.h / StaticObjects.cpp
Static Objects class that heiress from GameObjects class.

#### Gift.h / Gift.cpp
Gift class heiress from static objects.

#### GhostFreezeGift.h / GhostFreezeGift.cpp
GhostFreezeGift class heiress from Gift class.

#### LifIncGift.h / LifIncGift.cpp
LifIncGift class heiress from Gift class.

#### SuperPacGift.h / SuperPacGift.cpp
SuperPacGift class heiress from Gift class.

#### TimeAddGift.h / TimeAddGift.cpp
TimeAddGift class heiress from Gift class.

#### Cookie.h / Cookie.cpp
Cookie class heiress from static objects.

#### Door.h / Door.cpp
Door class heiress from static objects.

#### Key.h / Key.cpp
Key class heiress from static objects.

#### Wall.h / Wall.cpp
Wall class heiress from static objects.

#### Brain.h / Brain.cpp
namespace brain for calculating the demons path to pacman.

#### GameBar.h / GameBar.cpp
Game bar class responsible for showing and updating stats about the game.

#### GameBoard.h / GameBoard.cpp
Board class that responsible for handling the Board creation and management.

#### GameController.h / GameController.cpp
The main class that managing the game.

#### LeaderBoard.h / LeaderBoard.cpp
Leader board class that responsible for managing the records data.

#### Level.h / Level.cpp
Level class that load levels from file and checks the validation of them.

#### Menu.h / Menu.cpp
Menu class that responsible for loading and handling the menu screen.

#### ResourcesManager.h / ResourcesManager.cpp
Singleton class Resources class that responsible for loading all the textures,
sounds and images.

#### SettingsManager.h / SettingsManager.cpp
Singleton class that managing the settings of the game.

#### SettingsScreen.h / SettingsScreen.cpp
Settings class that handles the setting window display.

#### SoundFlip.h / SoundFlip.cpp
Singleton class for the sound switches.

## Data structures:
- 2D vector of Rectangles:     Holds matrix rectangles

- Vector of UniquePtr:         Holds special pointer to Static Objects.

- Vector of UniquePtr:         Holds special pointer to Dynamic Objects.

## Algorithms:

- BFS Algorithm:               Used for making demons "smart" and chase the 
                               pacman more efficiently.

- Calculate Level Time:        Used for calculating level time, according to the
                               level difficulty.

- Calculate Key-Door Dist:     Used for finding the closest Door.


## Photos:

<img src="https://user-images.githubusercontent.com/110122825/231173366-7e1fd137-a929-4206-8477-b63eb8a89971.png" width="30%">     <img src="https://user-images.githubusercontent.com/110122825/231173408-575f5515-5664-492d-9941-defaf5479caf.png" width="30%">     <img src="https://user-images.githubusercontent.com/110122825/231173434-378132cf-7c3e-488a-8fd5-fe347168298a.png" width="30%">
<img src="https://user-images.githubusercontent.com/110122825/231173456-0af2ba94-9997-4285-bcf3-7feb304e1401.png" width="30%">     <img src="https://user-images.githubusercontent.com/110122825/231173492-5b4ae355-f5b2-4376-9cb8-a01369532e0c.png" width="30%">     <img src="https://user-images.githubusercontent.com/110122825/231173497-3306bc9c-c6e1-4987-9d9f-62a697ef045e.png" width="30%">
<img src="https://user-images.githubusercontent.com/110122825/231173529-11193e20-0e1b-4025-a415-77fe060bc071.png" width="30%">

                               
