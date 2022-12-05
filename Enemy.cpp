#include <Enemy.h>
#include <QRandomGenerator>
#include <time.h>
#include "Game.h"

extern Game* game;

Enemy::Enemy(int type, QWidget *parent): Entity(parent)
{
    direction = 0;
    enemy_type = type;
    lockDirection = 0;
    switch(type){
    case 0:
        imagePath = ":/images/enemy_basic";
        imageDie = ":/images/enemy_basic_dead";
        setImage();
        timer_speed = 12;
        follow_distance = 1;
        break;
    case 1:
        imagePath = ":/images/enemy_fast";
        imageDie = ":/images/enemy_fast_dead";
        setImage();
        timer_speed = 10;
        follow_distance = 3;
        break;
    case 2:
        imagePath = ":/images/enemy_basic_fast";
        imageDie = ":/images/enemy_basic_fast_dead";
        setImage();
        timer_speed = 8;
        follow_distance = 0;
        break;
    case 3:
        imagePath = ":/images/enemy_killer";
        imageDie = ":/images/enemy_killer_dead";
        setImage();
        timer_speed = 6;
        follow_distance = 999;
        break;
    }
    timer = new QTimer();
    changeDirection();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(timer_speed);
}

Enemy::~Enemy()
{
    timer->stop();
    delete(timer);
}

void Enemy::move()
{
    if(!(bombCollide())){
        if(lockDirection){
            lockDirection = 0;
        }
        int pathFollow = game->tileMap->getTile(getTile())->pathLength;
        if(pathFollow<=follow_distance){
            int pathDirection = game->tileMap->getTile(getTile())->pathNextDirection;
            if(pathDirection){
                if((pathDirection==1)||(pathDirection==2)){
                    if(xCoord<game->tileMap->getTile(getTile())->getCoordX()){
                        direction=4;
                    }else if(xCoord>game->tileMap->getTile(getTile())->getCoordX()){
                        direction=3;
                    }else{
                        direction=pathDirection;
                    }
                }else if((pathDirection==3)||(pathDirection==4)){
                    if(yCoord<game->tileMap->getTile(getTile())->getCoordY()){
                        direction=2;
                    }else if(yCoord>game->tileMap->getTile(getTile())->getCoordY()){
                        direction=1;
                    }else{
                        direction=pathDirection;
                    }
                }
            }
        }
    }else{
        if(!lockDirection){
            switch(direction){
            case 1:
                direction = 2;
                break;
            case 2:
                direction = 1;
                break;
            case 3:
                direction = 4;
                break;
            case 4:
                direction = 3;
                break;
            }
            lockDirection = 1;
        }
    }
    switch(direction){
    case 1:
        move_up();
        break;
    case 2:
        move_down();
        break;
    case 3:
        move_left();
        break;
    case 4:
        move_right();
        break;
    }
    if(stop){
        changeDirection();
        stop = 0;
    }
    if(alive){
        if(burn()){
            die();
        }
    }
}

void Enemy::changeDirection()
{
    QRandomGenerator* randGen = new QRandomGenerator(time(NULL));
    int randomDirection = randGen->bounded(1, 4);
    switch(direction){
    case 1:
        if (randomDirection == 1){
            randomDirection = 2;
        }
        break;
    case 2:
        if (randomDirection == 2){
            randomDirection = 1;
        }
        break;
    case 3:
        if (randomDirection == 3){
            randomDirection = 4;
        }
        break;
    case 4:
        if (randomDirection == 4){
            randomDirection = 3;
        }
        break;
    default:
        break;
    }
    direction = randomDirection;
    delete(randGen);
}
