#include <PowerUp.h>
#include "Game.h"

extern Game* game;

PowerUp::PowerUp(int type, QWidget *parent):Element(parent)
{
    powerUp_type = type;
    switch(type){
    case 1:
        imagePath = ":/images/powerup_maxbombs";
        setImage();
        break;
    case 2:
        imagePath = ":/images/powerup_bombpower";
        setImage();
        break;
    case 3:
        imagePath = ":/images/powerup_movespeed";
        setImage();
        break;
    case 4:
        imagePath = ":/images/powerup_bonuslife";
        setImage();
        break;
    }
}

void PowerUp::activate()
{
    switch(powerUp_type){
    case 1:
        if(game->max_bombs<10){
            game->max_bombs++;
        }
        deleteLater();
        break;
    case 2:
        if(game->bomb_power<10){
            game->bomb_power++;
        }
        deleteLater();
        break;
    case 3:
        if(game->player_movespeed>6){
            game->player_movespeed--;
        }
        deleteLater();
        break;
    case 4:
        game->player_lives++;
        break;
    }
}
