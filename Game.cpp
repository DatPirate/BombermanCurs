#include <Game.h>
#include <QRandomGenerator>
#include <QMessageBox>
#include <time.h>
#include "Block.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUp.h"

Game::Game(){
    //screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1040,780);
    //scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1860,780);
    scene->setBackgroundBrush(Qt::darkCyan);
    setScene(scene);
    //starting stats
    level = 1;
    player_lives = 3;
    max_bombs = 1;
    player_movespeed = 10;
    bomb_power = 1;
    bomb_type = 0;
    set_bombs = 0;
}

Game::~Game(){
    delete(tileMap);
    delete(scene);
}

void Game::start(){
    setInteractive(1);
    levelTimer = 200;
    scene->setBackgroundBrush(Qt::green);
    noRestart = 1;
    tileMap = new TileMap();
    tileMap->setMap();
    setBlocks();
    setEnemies();
    player = new Player(this);
    player->setElement(tileMap->getTile(32));
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    centerOn(player);
    setLevelTimer();
}

void Game::mainMenu()
{
    setInteractive(0);
    titleText = new QGraphicsTextItem(QString("BomberMan"));
    QFont titleFont ("sans serif", 100, QFont::Bold);
    titleText->setFont(titleFont);
    int xTitleText = scene->width()/2 - titleText->boundingRect().width()/2;
    int yTitleText = 100;
    titleText->setPos(xTitleText, yTitleText);
    scene->addItem(titleText);

    startButton = new QPushButton("Start", this);
    int xStartButton = this->width()/2 - startButton->width()/2;
    int yStartButton = 300;
    startButton->setGeometry(xStartButton, yStartButton, 200, 100);
    startButton->show();
    connect(startButton, SIGNAL(released()), this, SLOT(pressStart()));

    helpButton = new QPushButton("Help", this);
    int xHelpButton = this->width()/2 - helpButton->width()/2;
    int yHelpButton = 450;
    helpButton->setGeometry(xHelpButton, yHelpButton, 200, 100);
    helpButton->show();
    connect(helpButton, SIGNAL(released()), this, SLOT(pressHelp()));

    aboutButton = new QPushButton("About", this);
    int xAboutButton = this->width()/2 - aboutButton->width()/2;
    int yAboutButton = 600;
    aboutButton->setGeometry(xAboutButton, yAboutButton, 200, 100);
    aboutButton->show();
    connect(aboutButton, SIGNAL(released()), this, SLOT(pressAbout()));
}


void Game::resetScreen()
{
    setInteractive(0);
    scene->setBackgroundBrush(Qt::darkCyan);
    if(player_lives<0){
        titleText = new QGraphicsTextItem(QString("YOU LOST"));
        QFont titleFont ("sans serif", 100, QFont::Bold);
        titleText->setFont(titleFont);
        int xTitleText = scene->width()/2 - titleText->boundingRect().width()/2;
        int yTitleText = 100;
        titleText->setPos(xTitleText, yTitleText);
        centerOn(scene->width()/2, yTitleText);
        scene->addItem(titleText);
    }else if(level>3){
        titleText = new QGraphicsTextItem(QString("YOU WON"));
        QFont titleFont ("sans serif", 100, QFont::Bold);
        titleText->setFont(titleFont);
        int xTitleText = scene->width()/2 - titleText->boundingRect().width()/2;
        int yTitleText = 100;
        titleText->setPos(xTitleText, yTitleText);
        centerOn(scene->width()/2, yTitleText);
        scene->addItem(titleText);
    }else{
        QString textLevel = "Level: " + QString::number(level);
        QString textLives = "Lives: " + QString::number(player_lives);
        titleText = new QGraphicsTextItem(textLevel+QString("\n")+textLives);
        QFont titleFont ("sans serif", 100, QFont::Bold);
        titleText->setFont(titleFont);
        int xTitleText = scene->width()/2 - titleText->boundingRect().width()/2;
        int yTitleText = 100;
        titleText->setPos(xTitleText, yTitleText);
        centerOn(scene->width()/2, yTitleText);
        scene->addItem(titleText);
        resetScreenTimer = new QTimer();
        connect(resetScreenTimer, SIGNAL(timeout()), this, SLOT(removeResetScreen()));
        resetScreenTimer->start(3000);
    }
}

void Game::setLevelTimer()
{
    setWindowTitle(QString("Time: ") + QString::number(levelTimer));
    //QFont titleFont ("sans serif", 20, QFont::Normal);
    //timerText->setFont(titleFont);
    //int xTitleText = this->x() + this->width()/2 - timerText->boundingRect().width()/2;
    //int yTitleText = this->y() + 10;
    //timerText->setPos(pos());
    //scene->addItem(timerText);

    levelTimerCountdown = new QTimer();
    connect(levelTimerCountdown, SIGNAL(timeout()), this, SLOT(timerCountdown()));
    levelTimerCountdown->start(1000);
}

void Game::timerCountdown()
{
    if (levelTimer){
        levelTimer--;
        setWindowTitle(QString("Time: ") + QString::number(levelTimer));
    }else{
        int setEnemies = 0;
        QRandomGenerator* randGen = new QRandomGenerator(time(NULL));
        int randomTile;
        while (setEnemies<6){
            randomTile = randGen->bounded(35, 370);
            if ((randomTile!=63)&&(tileMap->getTile(randomTile)->isOccupied()==0)){
                Enemy* enemy = new Enemy(3, this);
                enemy->setElement(tileMap->getTile(randomTile));
                setEnemies++;
            }
        }
        delete(randGen);
        levelTimerCountdown->stop();
    }
}

void Game::setPaths()
{
    int i = 0;
    pathTiles.clear();
    pathTiles.squeeze();
    tileMap->clearPath();
    tileMap->getTile(player->getTile())->pathLength = 0;
    pathTiles.append(player->getTile());
    while(1){
        tileMap->setPath(pathTiles[i]);
        if((i+1)>=pathTiles.length()){
            break;
        }
        i++;
    }
}

void Game::setPowerUp(int tileId)
{
    if(noRestart){
        Tile* powerUpTile = tileMap->getTile(tileId);
        QRandomGenerator* randGen = new QRandomGenerator(time(NULL));
        int randomChance = randGen->bounded(1, 20);
        if(randomChance==10){
            int randomPowerUp = randGen->bounded(1, 4);
            switch(randomPowerUp){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            }
            PowerUp* powerUp = new PowerUp(randomPowerUp, this);
            powerUp->setElement(powerUpTile);
        }
        delete(randGen);
    }
}

void Game::PlayerReset()
{
    player_lives--;
    restart();
}

void Game::nextLevel()
{
    level++;
    restart();
}

void Game::restart(){
    noRestart = 0;
    levelTimerCountdown->stop();
    delete(levelTimerCountdown);
    const QList<QGraphicsItem *> items = scene->items();
    for(QGraphicsItem* item: items){
        if(!dynamic_cast<Tile*> (item)){
        delete(item);
        }
    }
    delete(tileMap);
    /*QList<QGraphicsItem *> newitems = scene->items();
    int newint = 0;
    for(QGraphicsItem* item: newitems){
        if(item){
            newint++;
        }
    }
    QMessageBox msgBox;
    msgBox.setWindowTitle("NEW");
    msgBox.setText(QString::number(newint));
    msgBox.exec();*/
    resetScreen();
}

void Game::pressStart()
{
    delete(titleText);
    delete(startButton);
    delete(helpButton);
    delete(aboutButton);
    start();
}

void Game::pressHelp()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Help");
    msgBox.setText("CONTROLS:\n WALK: W - up, S - down, A - left, D - right\n Press Z to place bomb\n Use bombs to destroy blocks and kill enemies\n Destroy blocks to find a door to exit\n Be careful, enemies and your own bombs kill you!");
    msgBox.exec();
}

void Game::pressAbout()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.setText("Made by:\n Александров Данила Дмитриевич\n Group М8О-213Б-21");
    msgBox.exec();
}

void Game::removeResetScreen()
{
    delete(titleText);
    delete(resetScreenTimer);
    start();
}

void Game::setBlocks(){
    //borders steel
    for (int i=0; i<=30; i++){
        BlockSteel* block = new BlockSteel(this);
        block->setElement(tileMap->getTile(i));
    }
    for (int i=372; i<=402; i++){
        BlockSteel* block = new BlockSteel(this);
        block->setElement(tileMap->getTile(i));
    }
    for (int i=31; i<=341; i+=31){
        BlockSteel* block = new BlockSteel(this);
        block->setElement(tileMap->getTile(i));
    }
    for (int i=61; i<=371; i+=31){
        BlockSteel* block = new BlockSteel(this);
        block->setElement(tileMap->getTile(i));
    }
    //inner steel
    for (int i=0; i<5; i++){
        this->setBlocksSteelCenter(i);
    }
    //inner brick
    this->setBlocksBrickCenter();
}

void Game::setBlocksSteelCenter(int line){
    int coordStart = 64 + (line*62);
    for (int i=coordStart; i<=(coordStart+26); i+=2){
        BlockSteel* block = new BlockSteel(this);
        block->setElement(tileMap->getTile(i));
    }
}

void Game::setBlocksBrickCenter(){
    int setBlocks = 0;
    QRandomGenerator* randGen = new QRandomGenerator(time(NULL));
    int randomTile;
    while (setBlocks<56){
        randomTile = randGen->bounded(34, 370);
        if ((randomTile!=63)&&(tileMap->getTile(randomTile)->isOccupied()==0)){
            BlockBrick* block = new BlockBrick(this);
            block->setElement(tileMap->getTile(randomTile));
            if(!setBlocks){
                block->setDoor();
            }
            setBlocks++;
        }
    }
    delete(randGen);
}

void Game::setEnemies(){
    int setEnemies = 0;
    QRandomGenerator* randGen = new QRandomGenerator(time(NULL));
    int randomTile;
    while (setEnemies<6){
        randomTile = randGen->bounded(35, 370);
        if ((randomTile!=63)&&(tileMap->getTile(randomTile)->isOccupied()==0)){
            Enemy* enemy = new Enemy(0, this);
            enemy->setElement(tileMap->getTile(randomTile));
            setEnemies++;
        }
    }
    if(level>1){
        while (setEnemies<9){
            randomTile = randGen->bounded(35, 370);
            if ((randomTile!=63)&&(tileMap->getTile(randomTile)->isOccupied()==0)){
                Enemy* enemy = new Enemy(1, this);
                enemy->setElement(tileMap->getTile(randomTile));
                setEnemies++;
            }
        }
    }
    if(level>2){
        while (setEnemies<12){
            randomTile = randGen->bounded(35, 370);
            if ((randomTile!=63)&&(tileMap->getTile(randomTile)->isOccupied()==0)){
                Enemy* enemy = new Enemy(2, this);
                enemy->setElement(tileMap->getTile(randomTile));
                setEnemies++;
            }
        }
    }
    delete(randGen);

}
