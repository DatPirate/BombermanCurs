#include <Bomb.h>
#include "Game.h"
#include "BombFire.h"

extern Game* game;

Bomb::Bomb(int type, QWidget *parent): Element(parent)
{
    imagePath = ":/images/bomb";
    setImage();
    occupy = 1;
    switch (type){
    case 0:
        timeBomb();
        break;
    case 1:
        triggerBomb();
        break;
    }
}

Bomb::~Bomb()
{
    timer_timeBomb->stop();
    delete timer_timeBomb;
    game->tileMap->getTile(getTile())->setUnoccupy();
    game->set_bombs--;
    //game->bombs.removeFirst();
}

void Bomb::timeBomb()
{
    timer_timeBomb = new QTimer();
    connect(timer_timeBomb, SIGNAL(timeout()), this, SLOT(explode()));
    timer_timeBomb->start(3000);
}

void Bomb::triggerBomb()
{
    explode();
}

void Bomb::explode()
{
    int tile_id = getTile();
    BombFire* center = new BombFire(0, game->tileMap->getTile(tile_id), game);
    center->collision();
    for(int i=1, max = game->bomb_power; i<=max; i++){
        BombFire* left = new BombFire(1, game->tileMap->getTile(tile_id-i), game);
        if(left->collision()){
            break;
        }
    };
    for(int i=1, max = game->bomb_power; i<=max; i++){
        BombFire* right = new BombFire(1, game->tileMap->getTile(tile_id+i), game);
        if(right->collision()){
            break;
        }
    };
    for(int i=1, max = game->bomb_power; i<=max; i++){
        BombFire* up = new BombFire(2, game->tileMap->getTile(tile_id-i*31), game);
        if(up->collision()){
            break;
        }
    };
    for(int i=1, max = game->bomb_power; i<=max; i++){
        BombFire* down = new BombFire(2, game->tileMap->getTile(tile_id+i*31), game);
        if(down->collision()){
            break;
        }
    };
    deleteLater();
}
