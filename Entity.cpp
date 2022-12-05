#include <Entity.h>
#include <QList>
#include <QMessageBox>
#include "Block.h"
#include "Bomb.h"
#include "BombFire.h"
#include "Game.h"

extern Game* game;
Entity::Entity(QWidget *parent): Element(parent)
{
    //default
    move_speed = 1;
    timer_speed = 10;
    alive = 1;
}

void Entity::move_up()
{
    if(alive){
        moveElement(xCoord, yCoord-move_speed);
        if (collide()){
            moveElement(xCoord, yCoord+move_speed);
            stop = 1;
        }else{
            stop = 0;
        }
    }
}

void Entity::move_down()
{
    if(alive){
        moveElement(xCoord, yCoord+move_speed);
        if (collide()){
            moveElement(xCoord, yCoord-move_speed);
            stop = 1;
        }else{
            stop = 0;
        }
    }
}

void Entity::move_left()
{
    if(alive){
        moveElement(xCoord-move_speed, yCoord);
        if (collide()){
            moveElement(xCoord+move_speed, yCoord);
            stop = 1;
        }else{
            stop = 0;
        }
    }
}

void Entity::move_right()
{
    if(alive){
        moveElement(xCoord+move_speed, yCoord);
        if (collide()){
            moveElement(xCoord-move_speed, yCoord);
            stop = 1;
        }else{
            stop = 0;
        }
    }
}

bool Entity::collide()
{
    QList<QGraphicsItem *> colliding_items = collidingItems(Qt::IntersectsItemBoundingRect);
    for (QGraphicsItem* item: colliding_items){
        if((dynamic_cast<BlockSteel*> (item))||(dynamic_cast<BlockBrick*> (item))){
            return 1;
        }
    }
    return 0;
}

bool Entity::burn()
{
    QList<QGraphicsItem *> colliding_items = collidingItems(Qt::IntersectsItemShape);
    for (QGraphicsItem* item: colliding_items){
        if(dynamic_cast<BombFire*> (item)){
            return 1;
        }
    }
    return 0;
}

bool Entity::bombCollide()
{
    QList<QGraphicsItem *> colliding_items = collidingItems(Qt::IntersectsItemBoundingRect);
    for (QGraphicsItem* item: colliding_items){
        if(dynamic_cast<Bomb*> (item)){
            return 1;
        }
    }
    return 0;
}

void Entity::die()
{
    alive = 0;
    imagePath = imageDie;
    setImage();
    timer_dead = new QTimer();
    connect(timer_dead, SIGNAL(timeout()), this, SLOT(selfDelete()));
    timer_dead->start(3000);
}

void Entity::selfDelete()
{
    timer_dead->stop();
    delete(timer_dead);
    deleteLater();
}
