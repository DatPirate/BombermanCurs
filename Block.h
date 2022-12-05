#ifndef BLOCK_H
#define BLOCK_H

#include <Element.h>

class BlockSteel: public Element{
public:
    BlockSteel(QWidget* parent = NULL);
    //~BlockSteel();
};

class BlockBrick: public Element{
public:
    BlockBrick(QWidget* parent = NULL);
    ~BlockBrick();
    void setDoor();
private:
    bool hasDoor;
};

#endif // BLOCK_H
