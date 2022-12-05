#ifndef TILE_H
#define TILE_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QObject>

class Tile: public QGraphicsRectItem, public QObject{
public:
    //constructors
    Tile();
    //getters
    bool isOccupied();
    int getSize();
    int getCoordX();
    int getCoordY();
    //setters
    void setOccupied();
    void setUnoccupy();
    void setCoord(int x, int y);
    void setPathClear();
    //attributes
    bool pathVisited;
    int pathNextId;
    int pathNextDirection; //1-up,2-down,3-left,4-right
    int pathLength;
private:
    bool TileOccupied;
    int xCoord;
    int yCoord;
    int size;
};

#endif // TILE_H
