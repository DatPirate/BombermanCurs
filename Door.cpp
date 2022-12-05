#include <Door.h>
#include "Game.h"

extern Game* game;

Door::Door(QWidget *parent): Element(parent)
{
    imagePath = ":/images/door";
    setImage();
}

void Door::useDoor()
{
    game->nextLevel();
}

void Door::burnDoor()
{

}
