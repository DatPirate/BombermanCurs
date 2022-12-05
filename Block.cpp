#include <Block.h>
#include "Game.h"
#include "Door.h"

extern Game* game;

BlockSteel::BlockSteel(QWidget *parent): Element(parent)
{
    occupy = 1;
    imagePath = ":/images/bomberman_block_steel";
    setImage();
}

BlockBrick::BlockBrick(QWidget *parent): Element(parent)
{
    occupy = 1;
    hasDoor = 0;
    imagePath = ":/images/bomberman_block_brick";
    setImage();
}

BlockBrick::~BlockBrick()
{
    if((hasDoor)&&(game->noRestart)){
        Door* door = new Door(game);
        door->setElement(game->tileMap->getTile(getTile()));
    }
    game->tileMap->getTile(getTile())->setUnoccupy();
    game->setPowerUp(getTile());
}

void BlockBrick::setDoor()
{
    hasDoor = 1;
}
