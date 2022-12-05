#ifndef TILEMAP_H
#define TILEMAP_H

#include <QList>
#include "Tile.h"

class TileMap{
public:
    //constructor
    TileMap();
    //destructor
    ~TileMap();
    //getters
    Tile* getTile(int i);

    // public methods
    void setMap();
    void setPath(int id);
    void clearPath();
private:
    QList<Tile*> tiles;
    int BoardSizeColumns;
    int BoardSizeLines;
    void setMapLine(int columns, int y);
};

#endif // TILEMAP_H
