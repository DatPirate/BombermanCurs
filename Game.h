#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QVector>
#include <QPushButton>
#include <QGraphicsTextItem>
#include <QTimer>
#include "TileMap.h"
#include "Player.h"
#include "Bomb.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    //contructor
    Game();
    //deconstructor
    ~Game();
    //public methods
    void start();
    void mainMenu();
    void nextLevel();
    void setPaths();
    void setPowerUp(int tileId);
    void PlayerReset();
    void doorBurned();
    //public attributes
    QGraphicsScene* scene;
    TileMap* tileMap;
    Player* player;
    QList<Bomb*> bombs;
    QVector<int> pathTiles;
    int noRestart;
    int max_bombs;
    int player_movespeed;
    int bomb_power;
    int bomb_type;
    int set_bombs;
    int player_lives;
public slots:
    void pressStart();
    void pressHelp();
    void pressAbout();
    void removeResetScreen();
    void timerCountdown();
private:
    //private methods
    void setBlocks();
    void setBlocksSteelCenter(int line);
    void setBlocksBrickCenter();
    void setEnemies();
    void restart();
    void resetScreen();
    void setLevelTimer();
    //private attributes
    int level;
    QGraphicsTextItem* titleText;
    QPushButton* startButton;
    QPushButton* helpButton;
    QPushButton* aboutButton;
    QTimer* resetScreenTimer;
    QGraphicsTextItem* timerText;
    int levelTimer;
    QTimer* levelTimerCountdown;
};

#endif // GAME_H
