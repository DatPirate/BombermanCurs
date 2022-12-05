#ifndef ELEMENT_H
#define ELEMENT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QString>
#include <QWidget>
#include <QObject>
#include "Tile.h"
#include "TileMap.h"

class Element: public QGraphicsPixmapItem, public QObject{
public:
    //constructor
    Element(QWidget* parent);
    //destructor
    ~Element();
    //setters
    void setElement(Tile* spawnPoint);
    //getters
    int getTile();
protected:
    //private setters for internal functions
    void moveHitbox(int x, int y);
    void moveImage(int x, int y);
    void setImage();
    void moveElement(int x, int y);
    //private arguments
    QPixmap* pixmap;
    Tile* hitbox;
    TileMap* tilemap;
    //bool collision = NULL;
    QString imagePath = NULL;
    int xCoord;
    int yCoord;
    int hitSize;
    bool occupy;
};

#endif // ELEMENT_H
