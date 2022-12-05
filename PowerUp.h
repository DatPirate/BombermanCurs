#ifndef POWERUP_H
#define POWERUP_H

#include <Element.h>

class PowerUp: public Element{
public:
    PowerUp(int type, QWidget* parent);
    void activate();
private:
    int powerUp_type;
};

#endif // POWERUP_H
