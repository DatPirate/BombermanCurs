#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>
#include "Bomb.h"

class Player: public Entity{
    Q_OBJECT
public:
    //constructor
    Player(QWidget* parent=NULL);
    //deconstructor
    ~Player();
public slots:
    void centerOnPlayer();
    void selfDelete();
private:
    QTimer* timer;
    void die();
    //reaction to movement keys
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    //collisions
    void powerUpCollision();
    void doorCollision();
    void enemyCollision();
};

#endif // PLAYER_H
