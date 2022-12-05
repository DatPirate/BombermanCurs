#ifndef BOMB_H
#define BOMB_H

#include <Element.h>
#include <QTimer>

class Bomb: public Element{
    Q_OBJECT
public:
    //constructor
    Bomb(int type = 0, QWidget* parent=NULL);
    ~Bomb();
public slots:
    void explode();
private:
    QTimer* timer_timeBomb;
    void timeBomb();
    void triggerBomb();

};

#endif // BOMB_H
