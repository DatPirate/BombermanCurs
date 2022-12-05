#ifndef ENEMY_H
#define ENEMY_H

#include <Entity.h>

class Enemy: public Entity{
    Q_OBJECT
public:
    Enemy(int type, QWidget* parent = NULL);
    ~Enemy();
private slots:
    void move();
private:
    void changeDirection();
    int enemy_type;
    int direction; //1-up, 2-down, 3-left, 4-right
    int lockDirection;
    QTimer* timer;
};

#endif // ENEMY_H
