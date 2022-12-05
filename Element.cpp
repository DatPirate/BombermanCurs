#include <Element.h>
#include <QMessageBox>
#include <math.h>
#include "Game.h"

extern Game* game;

Element::Element(QWidget* parent): QObject(parent){
    hitbox = new Tile();
    hitSize = hitbox->getSize();
    xCoord = 0;
    yCoord = 0;
    occupy = 0;
    game->scene->addItem(this);
    game->scene->addItem(hitbox);
}

Element::~Element()
{
    delete hitbox;
    delete pixmap;
}

void Element::moveHitbox(int x, int y){
    hitbox->setCoord(x, y);
}

void Element::moveImage(int x, int y){
    int offsetX = (hitSize-(pixmap->width()))/2;
    int offsetY = (hitSize-(pixmap->height()))/2;
    setPos(x+offsetX,y+offsetY);
}

void Element::setElement(Tile *spawnPoint){
        xCoord = spawnPoint->getCoordX();
        yCoord = spawnPoint->getCoordY();
        moveHitbox(xCoord, yCoord);
        moveImage(xCoord, yCoord);
        if (occupy){
            spawnPoint->setOccupied();
        }
}

int Element::getTile(){
    int x = (round((float)xCoord/hitSize));
    int y = (round((float)yCoord/hitSize));
    int id = x+y*31;
    return id;
}

void Element::setImage(){
    pixmap = new QPixmap(imagePath);
    *pixmap = pixmap->scaled(hitSize, hitSize, Qt::KeepAspectRatio, Qt::FastTransformation);
    setPixmap(*pixmap);
}

void Element::moveElement(int x, int y)
{
    xCoord = x;
    yCoord = y;
    moveHitbox(xCoord, yCoord);
    moveImage(xCoord, yCoord);
}
