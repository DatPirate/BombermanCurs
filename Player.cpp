#include <Player.h>
#include <QKeyEvent>
#include <QMessageBox>
#include "Game.h"
#include "PowerUp.h"
#include "Door.h"

extern Game* game;

Player::Player(QWidget *parent): Entity(parent)
{
    imagePath = ":/images/bomberman_player_down_idle";
    imageDie = ":/images/bomberman_player_dead";
    setImage();
    timer_speed = game->player_movespeed;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(centerOnPlayer()));
    timer->start(move_speed);
    timer_up = new QTimer();
    connect(timer_up, SIGNAL(timeout()), this, SLOT(move_up()));
    timer_down = new QTimer();
    connect(timer_down, SIGNAL(timeout()), this, SLOT(move_down()));
    timer_left = new QTimer();
    connect(timer_left, SIGNAL(timeout()), this, SLOT(move_left()));
    timer_right = new QTimer();
    connect(timer_right, SIGNAL(timeout()), this, SLOT(move_right()));
}

Player::~Player()
{
    timer->stop();
    timer_up->stop();
    timer_down->stop();
    timer_left->stop();
    timer_right->stop();
    delete timer;
    delete timer_up;
    delete timer_down;
    delete timer_left;
    delete timer_right;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up){
        if (event->isAutoRepeat()){
            return;
        }
        imagePath = ":/images/bomberman_player_up_idle";
        setImage();
        timer_up->start(timer_speed);
    }
    else if (event->key() == Qt::Key_Down){
        if (event->isAutoRepeat()){
            return;
        }
        imagePath = ":/images/bomberman_player_down_idle";
        setImage();
        timer_down->start(timer_speed);
    }
    else if (event->key() == Qt::Key_Left){
        if (event->isAutoRepeat()){
            return;
        }
        imagePath = ":/images/bomberman_player_left_idle";
        setImage();
        timer_left->start(timer_speed);
    }
    else if (event->key() == Qt::Key_Right){
        if (event->isAutoRepeat()){
            return;
        }
        imagePath = ":/images/bomberman_player_right_idle";
        setImage();
        timer_right->start(timer_speed);
    }
    else if (event->key() == Qt::Key_Z){
        if (event->isAutoRepeat()){
            return;
        }
        if ((game->set_bombs < game->max_bombs)&&(!(game->tileMap->getTile(getTile())->isOccupied()))){
            Bomb* bomb = new Bomb(game->bomb_type, game);
            //game->bombs.append(bomb);
            bomb->setElement(game->tileMap->getTile(getTile()));
            game->set_bombs++;
        }
    }
    else if(event->key() == Qt::Key_K){
        if (event->isAutoRepeat()){
            return;
        }
        game->PlayerReset();
    }
    /*else if(event->key() == Qt::Key_L){
        if (event->isAutoRepeat()){
            return;
        }
        QMessageBox msgBox;
        msgBox.setWindowTitle("speed");
        msgBox.setText(QString::number(timer_speed));
        msgBox.exec();
    }*/
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Up){
        if (event->isAutoRepeat()){
            return;
        }
        timer_up->stop();
    }
    else if (event->key() == Qt::Key_Down){
        if (event->isAutoRepeat()){
            return;
        }
        timer_down->stop();
    }
    else if (event->key() == Qt::Key_Left){
        if (event->isAutoRepeat()){
            return;
        }
        timer_left->stop();
    }
    else if (event->key() == Qt::Key_Right){
        if (event->isAutoRepeat()){
            return;
        }
        timer_right->stop();
    }
}

void Player::powerUpCollision()
{
    QList<QGraphicsItem *> colliding_items = collidingItems(Qt::IntersectsItemShape);
    for (QGraphicsItem* item: colliding_items){
        if(PowerUp* powerUp = dynamic_cast<PowerUp*> (item)){
            powerUp->activate();
            timer_speed = game->player_movespeed;
        }
    }
}

void Player::doorCollision()
{
    QList<QGraphicsItem *> colliding_items = collidingItems(Qt::IntersectsItemShape);
    for (QGraphicsItem* item: colliding_items){
        if(Door* door = dynamic_cast<Door*> (item)){
            door->useDoor();
        }
    }
}

void Player::centerOnPlayer()
{
    powerUpCollision();
    game->centerOn(this);
    game->setPaths();
    if(alive){
        if(burn()){
            Player::die();
        }
    }
    doorCollision();
}

void Player::die()
{
    alive = 0;
    imagePath = imageDie;
    setImage();
    timer_dead = new QTimer();
    connect(timer_dead, SIGNAL(timeout()), this, SLOT(selfDelete()));
    timer_dead->start(3000);
}

void Player::selfDelete()
{
    timer_dead->stop();
    delete(timer_dead);
    game->PlayerReset();
}
