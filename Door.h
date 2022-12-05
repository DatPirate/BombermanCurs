#ifndef DOOR_H
#define DOOR_H

#include <Element.h>

class Door: public Element{
public:
    Door(QWidget* parent = NULL);
    void useDoor();
    void burnDoor();
};

#endif // DOOR_H
