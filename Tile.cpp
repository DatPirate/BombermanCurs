#include <Tile.h>

Tile::Tile(){
    // draw
    xCoord = 0;
    yCoord = 0;
    size=60;
    setRect(xCoord,yCoord,size,size);
    this->hide();
    //set default on spawn
    TileOccupied=0;
    pathVisited=0;
    pathLength=999;
    pathNextId=0;
    pathNextDirection=0;
}

void Tile::setCoord(int x, int y){
    xCoord = x;
    yCoord = y;
    this->setPos(xCoord, yCoord);
}

void Tile::setPathClear()
{
    pathVisited=0;
    pathLength=999;
}

void Tile::setOccupied(){
    TileOccupied=1;
}

void Tile::setUnoccupy()
{
    TileOccupied=0;
}

bool Tile::isOccupied(){
    return TileOccupied;
}

int Tile::getSize(){
    return size;
}

int Tile::getCoordX(){
    return xCoord;
}

int Tile::getCoordY(){
    return yCoord;
}
