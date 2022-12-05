#ifndef ENTITY_H
#define ENTITY_H

#include <Element.h>
#include <QTimer>
#include <QString>

class Entity:public Element{
    Q_OBJECT
public:
    //constructor
    Entity(QWidget* parent=NULL);
public slots:
    //movement methods
    void move_up();
    void move_down();
    void move_left();
    void move_right();
    void selfDelete();
protected:
    bool collide();
    bool burn();
    bool bombCollide();
    void die();
    bool stop;
    bool alive;
    int move_speed;
    int timer_speed;
    int follow_distance;
    QString imageDie = NULL;
    QTimer* timer_dead;
    QTimer* timer_up;
    QTimer* timer_down;
    QTimer* timer_left;
    QTimer* timer_right;
};

#endif // ENTITY_H
