#ifndef BOMBFIRE_H
#define BOMBFIRE_H

#include <Element.h>
#include <QTimer>
#include "Tile.h"

class BombFire: public Element{
    Q_OBJECT
public:
    BombFire(int type, Tile* tile, QWidget* parent = NULL);
    bool collision();
public slots:
    void selfDelete();
private:
    QTimer* timer;
};

#endif // BOMBFIRE_H
