#include <TileMap.h>
#include <QtAlgorithms>

#include <QMessageBox>
#include "Game.h"

extern Game* game;


//lines
//1.0-30 2.31-61 3.62-92 4.93-123 5.124-154 6.155-185 7.186-216
//8.217-247 9.248-278 10.279-309 11.310-340 12. 341-371 13. 372-402
TileMap::TileMap(){
    BoardSizeColumns = 31;
    BoardSizeLines = 13;
}

TileMap::~TileMap()
{
    qDeleteAll(tiles);
    //for(Tile* tile: tiles){
    //    game->scene->removeItem(tile);
    //}
    tiles.clear();
    tiles.squeeze();
}

Tile *TileMap::getTile(int i)
{
    return tiles[i];
}

void TileMap::setMap(){
    int x=0;
    int y=0;
    for (size_t j = 0, m = BoardSizeLines; j < m; j++){
        for (size_t i = 0, n = BoardSizeColumns; i < n; i++){
            Tile* tile = new Tile();
            x=i*(tile->getSize());
            y=j*(tile->getSize());
            tile->setCoord(x, y);
            tiles.append(tile);
            game->scene->addItem(tile);
        }
    }
}

void TileMap::setPath(int id)
{
    if(!(tiles[id]->pathVisited)){
        if(!(tiles[id-BoardSizeColumns]->isOccupied())){
            if(!(tiles[id-BoardSizeColumns]->pathVisited)){
                if(tiles[id-BoardSizeColumns]->pathLength>(tiles[id]->pathLength+1)){
                    tiles[id-BoardSizeColumns]->pathLength = tiles[id]->pathLength+1;
                    tiles[id-BoardSizeColumns]->pathNextId = id;
                    tiles[id-BoardSizeColumns]->pathNextDirection = 2;
                    game->pathTiles.append(id-BoardSizeColumns);
                }
            }
        }
        if(!(tiles[id+BoardSizeColumns]->isOccupied())){
            if(!(tiles[id+BoardSizeColumns]->pathVisited)){
                if(tiles[id+BoardSizeColumns]->pathLength>(tiles[id]->pathLength+1)){
                    tiles[id+BoardSizeColumns]->pathLength = tiles[id]->pathLength+1;
                    tiles[id+BoardSizeColumns]->pathNextId = id;
                    tiles[id+BoardSizeColumns]->pathNextDirection = 1;
                    game->pathTiles.append(id+BoardSizeColumns);
                }
            }
        }
        if(!(tiles[id-1]->isOccupied())){
            if(!(tiles[id-1]->pathVisited)){
                if(tiles[id-1]->pathLength>(tiles[id]->pathLength+1)){
                    tiles[id-1]->pathLength = tiles[id]->pathLength+1;
                    tiles[id-1]->pathNextId = id;
                    tiles[id-1]->pathNextDirection = 4;
                    game->pathTiles.append(id-1);
                }
            }
        }
        if(!(tiles[id+1]->isOccupied())){
            if(!(tiles[id+1]->pathVisited)){
                if(tiles[id+1]->pathLength>(tiles[id]->pathLength+1)){
                    tiles[id+1]->pathLength = tiles[id]->pathLength+1;
                    tiles[id+1]->pathNextId = id;
                    tiles[id+1]->pathNextDirection = 3;
                    game->pathTiles.append(id+1);
                }
            }
        }
        tiles[id]->pathVisited = 1;
    }
}

void TileMap::clearPath()
{
    for(Tile* tile: tiles){
        tile->setPathClear();
    }
}


