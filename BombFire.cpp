#include <BombFire.h>
#include "Block.h"
#include "Door.h"

BombFire::BombFire(int type, Tile* tile, QWidget *parent): Element(parent)
{
    switch (type){ //0 center, 1 horizontal, 2 vertical
    case 0:
        imagePath = ":/images/bomb_explode_center.png";
        break;
    case 1:
        imagePath = ":/images/bomb_explode_horizontal.png";
        break;
    case 2:
        imagePath = ":/images/bomb_explode_vertical.png";
        break;
    }
    setImage();
    setElement(tile);
}

bool BombFire::collision()
{
    QList<QGraphicsItem *> colliding_items = collidingItems(Qt::IntersectsItemShape);
    for (QGraphicsItem* item: colliding_items){
        if(dynamic_cast<BlockBrick*> (item)){
            delete(item);
            deleteLater();
            return 1;
        }else if(dynamic_cast<BlockSteel*> (item)){
            deleteLater();
            return 1;
        }else if(Door* door = dynamic_cast<Door*> (item)){
            door->burnDoor();
            deleteLater();
            return 1;
        }
    }
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(selfDelete()));
    timer->start(1000);
    return 0;
}

void BombFire::selfDelete()
{
    timer->stop();
    delete(timer);
    deleteLater();
}
