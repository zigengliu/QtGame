/*Zigeng Liu
 * 504188798
 * Summury:This is the implementation of GameBoard class and the interfaces and logics of the board.
 * The code for ui interface is in the .ui files.
 * The constructor of the game will paint the grid and walls and portals and egg.
 * The keyPressEvent funtion will be in charge of the movement and paint the duck.
 * Other methods will support keyPressEvent.
******************************************************************
******************************************************************
******************************************************************
*******    Use  W A S D to move duck!!!!!!!   ********************
*******   Cannot go through wall!!!!!!        ********************
*******    Hawk will chase you and eat you!!! ********************
******************************************************************
******************************************************************
******************************************************************
******************************************************************
******************************************************************
******************************************************************
******************************************************************
 */

#include "gameboard.h"

#include "mainwindow.h"
#include "ui_gameboard.h"
#include <QPushButton>
#include <QDebug>


GameBoard::GameBoard(QWidget *parent, size_t board_sz, unsigned int level) :
    QWidget(parent),
    ui(new Ui::GameBoard), boardSize(board_sz), currentLvl(level)
{
    ui->setupUi(this);
/*Initializing some of the private variables
 */
    gameOn = true;
    if(currentLvl==1) wallArraySize = 37;
    else if(currentLvl==2) wallArraySize = 39;
    else wallArraySize = 238;
    holePassed = false;    
    hawkStep = 1;

    bros = 3;
 /*Initializing Pixmaps
  */
    QString filename1(":/image/duck.jpg");
    QString filename2(":/image/wall.jpg");
    QString filename3(":/image/egg.jpg");
    QString filename4(":/image/hole.jpg");
    QString filename5(":/image/grass.jpg");
    QString filename6(":/image/hawk.jpg");
    duck = new QPixmap(filename1);
    hole = new QPixmap(filename4);
    wall = new QPixmap(filename2);
    egg = new QPixmap(filename3);
    grass = new QPixmap(filename5);
    hawk = new QPixmap(filename6);

/*1. finalLayout has three widgets: titleAndLives, boardGrid, and lastWidget
 */
    this->setStyleSheet("background-image: url(:/image/back1.jpg)");
    QVBoxLayout* finalLayout = new  QVBoxLayout(this);
    finalLayout->setSpacing(0);
    finalLayout->setMargin(0);
    QWidget* titleAndLives = new QWidget;
    QWidget* boardGrid = new QWidget;
    QWidget* lastWidget = new QWidget;

    finalLayout->addWidget(titleAndLives);
    finalLayout->addWidget(boardGrid);
    finalLayout->addWidget(lastWidget);

/*2. TitleAndLives has title, warning, and a livesBar
 */
    QVBoxLayout* vertOnTitle = new QVBoxLayout(titleAndLives);
    QLabel* title = new QLabel("Get the Duck to Her Egg!!");
    QFont font = title->font();
    font.setPointSize(26);
    font.setBold(true);
    title->setFont(font);
    title->setAlignment(Qt::AlignCenter);

    warnings = new QLabel("Look! A Hawk! Don't get caught!");
    QFont warningsFont = warnings->font();
    warningsFont.setPointSize(8);
    warningsFont.setBold(true);
    warnings->setFont(warningsFont);
    warnings->setAlignment(Qt::AlignCenter);

/*3. livesBar is horizontally organized and have lives and text
 */
    QWidget* liveBar = new QWidget;
    QHBoxLayout* horizOnLiveBar = new QHBoxLayout(liveBar);
    QLabel* livesText = new QLabel("Lives: ");
    QFont livesFont = livesText->font();
    livesFont.setPointSize(10);
    livesFont.setBold(true);
    livesText->setFont(livesFont);
    horizOnLiveBar->addWidget(livesText);
    lives_remaining = 4;
    lives = new QLabel*[lives_remaining-1];
    for(size_t i=0;i<lives_remaining-1;i++) {
        lives[i] = new QLabel;
        lives[i]->setPixmap(*duck);
        lives[i]->setMinimumSize(40,40);
        lives[i]->setMaximumSize(40,40);
        lives[i]->setScaledContents(true);
        horizOnLiveBar->addWidget(lives[i]);
    }
    QSpacerItem* horizSpacer = new QSpacerItem(350,10);
    horizOnLiveBar->addSpacerItem(horizSpacer);
    QLabel* levelText = new QLabel("Level: ");
    QFont levelFont = levelText->font();
    levelFont.setPointSize(10);
    levelFont.setBold(true);
    levelText->setFont(levelFont);
    QLabel* levelValue = new QLabel(QString::number(currentLvl));
    levelValue->setFont(levelFont);
    horizOnLiveBar->addWidget(levelText);
    horizOnLiveBar->addWidget(levelValue);
    horizOnLiveBar->setAlignment(Qt::AlignCenter);

    vertOnTitle->addWidget(title,Qt::AlignCenter);
    vertOnTitle->addWidget(warnings);
    vertOnTitle->addWidget(liveBar);





 /*4. this is the grid set up, which is on gridContainer, which is on boardGrid widget
 */
    label = new QLabel*[boardSize*boardSize];
    QHBoxLayout* gridContainer = new QHBoxLayout(boardGrid);
    QWidget* gridWidget = new QWidget;
    gridContainer->addWidget(gridWidget,Qt::AlignCenter);
    QGridLayout* layout = new QGridLayout(gridWidget);
    layout->setGeometry(QRect());
    layout->setAlignment(Qt::AlignCenter);
    gridWidget->setFixedSize(boardSize*30,boardSize*30);

 /*5. initializing positions of objects and their locations
  */
    duckPosition = new QPoint(0,0);
    hawkPosition = new QPoint(boardSize-1,0);
    eggPosition = new QPoint(boardSize-1,boardSize-1);
    this->wallLocation();
    this->holeLocation();
    this->setGrid(layout);

/*6. A timer used to update hawk automatically
 */
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateHawk()));
    timer->start(500);

/*7. PushButton and connectors
 *      1).two buttons, one for replay, the other for quit to main menu
 *      2).connectors for buttons and connectors that process the endLost() and endWon() signals according to current level
 *          (1). if the duck reaches egg, jump to the next level
 *          (2). if hawk reaches duck, popUp window shows up and game ends, player can choose to replay or quit.
 */
    QVBoxLayout* lastLayout = new QVBoxLayout(lastWidget);
    QPushButton* tryAgain = new QPushButton("Try Agian");
    QPushButton* quitLevel = new QPushButton("Quit");

    if(currentLvl==1){
        connect(this, SIGNAL(gameWon()),parent,SLOT(medium_game_begin()));
        connect(tryAgain, SIGNAL(clicked()),parent,SLOT(easy_game_begin()));
    }
    else if(currentLvl==2){
        connect(this, SIGNAL(gameWon()),parent,SLOT(hard_game_begin()));
        connect(tryAgain, SIGNAL(clicked()),parent,SLOT(medium_game_begin()));
    }
    else{
        connect(tryAgain, SIGNAL(clicked()),parent,SLOT(hard_game_begin()));
    }
    connect(quitLevel, SIGNAL(clicked()),parent,SLOT(game_over()));
    connect(this, SIGNAL(gameLost()),this,SLOT(endLost()));



    lastLayout->addWidget(tryAgain);
    lastLayout->addWidget(quitLevel);

/*8. the popUp window set up
 */
    popUp = new QWidget;
    popUpLayout = new QVBoxLayout(popUp);
    popUpTextOver = new QLabel("GameOver!");
    QPushButton* quitGame = new QPushButton("Close");
    popUpLayout->addWidget(popUpTextOver);
    popUpLayout->addWidget(quitGame);
    connect(quitGame, SIGNAL(clicked()),popUp,SLOT(close()));



//    repaint();
//    QCoreApplication::processEvents();


}


GameBoard::~GameBoard()
{
    delete ui;
    delete[] label;
    delete[] wallPositions;
    delete[] holePositions;
}

/*SetGrid() sets up a 20 by 20 grid and its initial conditions(pixmaps)
 */
void GameBoard::setGrid(QGridLayout* layout){
    layout->setSpacing(0);
    for(size_t i=0;i<boardSize;i++){
        for(size_t j=0;j<boardSize;j++) {
            label[i*boardSize+j]=new QLabel;
            label[i*boardSize+j]->setMaximumSize(30,30);
            label[i*boardSize+j]->setMinimumSize(30,30);
            label[i*boardSize+j]->setAlignment(Qt::AlignCenter);

            if(i==0&&j==0){
                label[i*boardSize+j]->setStyleSheet("QLabel { background-color: white }");
                label[i*boardSize+j]->setPixmap(*duck);
                label[i*boardSize+j]->setScaledContents(true);
            }
            else if(i==boardSize-1&&j==boardSize-1){
                label[i*boardSize+j]->setStyleSheet("QLabel { background-color: white }");
                label[i*boardSize+j]->setPixmap(*egg);
                label[i*boardSize+j]->setScaledContents(true);
            }
            else if(i==0&&j==boardSize-1){
                label[i*boardSize+j]->setStyleSheet("QLabel { background-color: white }");
                label[i*boardSize+j]->setPixmap(*hawk);
                label[i*boardSize+j]->setScaledContents(true);
            }
            else if(inHole(i,j)==1||inHole(i,j)==2){
                label[i*boardSize+j]->setStyleSheet("QLabel { background-color: white }");
                label[i*boardSize+j]->setPixmap(*hole);
                label[i*boardSize+j]->setScaledContents(true);
            }
            else if(inWall(i,j)){
                label[i*boardSize+j]->setStyleSheet("QLabel { background-color: white }");
                label[i*boardSize+j]->setPixmap(*wall);
                label[i*boardSize+j]->setScaledContents(true);
            }
            else{
                label[i*boardSize+j]->setStyleSheet("QLabel { background-color: white }");
                label[i*boardSize+j]->setPixmap(*grass);
                label[i*boardSize+j]->setScaledContents(true);
            }
            layout -> addWidget(label[i*boardSize+j], i, j);
        }

    }
}

/*wallLocation() set up predetermined wall locations on grid according to each level
 */
void GameBoard::wallLocation(){
    wallPositions = new QPoint*[wallArraySize];
    if(!wallhash.isEmpty())
        wallhash.clear();
    QVector<int> vec0;QVector<int> vec1;QVector<int> vec2;QVector<int> vec3;QVector<int> vec4;
    QVector<int> vec5;QVector<int> vec6;QVector<int> vec7;QVector<int> vec8;QVector<int> vec9;
    QVector<int> vec10;QVector<int> vec11;QVector<int> vec12;QVector<int> vec13;QVector<int> vec14;
    QVector<int> vec15;QVector<int> vec16;QVector<int> vec17;QVector<int> vec18;QVector<int> vec19;
    QVector<QVector<int>> vec;
    if(currentLvl==1){
        vec0 << 1 << 5 << 9 << 13 << 17;
        vec1 << 1 << 5 << 9 << 13 << 17;
        vec2 << 3 << 7 << 11 << 15 << 19;
        vec3 << 3 << 7 << 11 << 15 << 19;
        vec4 << 5 << 1 << 9 << 13 << 17;
        vec5 << 5 << 1 << 9 << 13 << 17;
        vec6 << 7 << 3 << 11 << 15 << 19;
        vec7 << 7 << 3 << 11 << 15 << 19;
        vec8 << 9 << 5 << 1 << 13 << 17;
        vec9 << 9 << 5 << 1 << 13 << 17;
        vec10 << 11 << 7 << 3 << 15 << 19;
        vec11 << 11 << 7 << 3 << 15 << 19;
        vec12 << 13 << 9 << 5 << 1 << 17;
        vec13 << 13 << 9 << 5 << 1 << 17;
        vec14 << 15 << 11 << 7 << 3 << 19;
        vec15 << 15 << 11 << 7 << 3 << 19;
        vec16 << 17 << 13 << 9 << 5 << 1;
        vec17 << 17 << 13 << 9 << 5 << 1;
        vec18 << 15 << 11 << 7 << 3;
        vec19 << 15 << 11 << 7 << 3;
    }
    else if(currentLvl==2){
        vec0 << 1 << 9 << 17;
        vec1 << 1 << 9 << 17;
        vec2 << 1 << 5 << 9 << 13 << 17;
        vec3 << 1 << 5 << 9 << 13 << 17;
        vec4 << 1 << 5 << 9 << 13 << 17;
        vec5 << 1 << 5 << 9 << 13 << 17;
        vec6 << 1 << 5 << 9 << 13 << 17;
        vec7 << 1 << 5 << 9 << 13 << 17;
        vec8 << 1 << 5 << 9 << 13 << 17;
        vec9 << 1 << 5 << 9 << 13 << 17;
        vec10 << 1 << 5 << 9 << 13 << 17;
        vec11 << 1 << 5 << 9 << 13 << 17;
        vec12 << 1 << 5 << 9 << 13 << 17;
        vec13 << 1 << 5 << 9 << 13 << 17;
        vec14 << 1 << 5 << 9 << 13 << 17;
        vec15 << 1 << 5 << 9 << 13 << 17;
        vec16 << 1 << 5 << 9 << 13 << 17;
        vec17 << 1 << 5 << 9 << 13 << 17;
        vec18 << 5 << 13;
        vec19 << 5 << 13;
    }
    else{
        vec0 << 3 << 4
             << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12 << 13 << 14
             << 15 << 19;
        vec1 << 0 << 1 << 3 << 10 << 11 << 17 << 19;
        vec2 << 0 << 1 << 3 << 5 << 6 << 7 << 8 << 10 << 11 << 13 << 14 << 15 << 17 << 18 << 19;
        vec3 << 3 << 5 << 6 << 7 << 8 << 10 << 11 << 13 << 14 << 17 << 18 << 19;
        vec4 << 1 << 2 << 3 << 7 << 8 << 10 << 11 << 13 << 14 << 16 << 17 << 18 << 19;
        vec5 << 5 << 7 << 8 << 10 << 11 << 19;
        vec6 << 1 << 2 << 3 << 4 << 5 << 7 << 8 << 10 << 11 << 13 << 14 << 15 << 16 << 17 << 19;
        vec7 << 0 << 1 << 2 << 7 << 8 << 10 << 11 << 17 << 19;
        vec8 << 0 << 1 << 2 << 4 << 5 << 6 << 7 << 8 << 10 << 11 << 13 << 14 << 17 << 19;
        vec9 << 0 << 1 << 2 << 4 << 5 << 6 << 7 << 8 << 10 << 11 << 13 << 14 << 17 << 19;
        vec10 << 0 << 1 << 2 << 4 << 5 << 6 << 7 << 8 << 10 << 11 << 13 << 14 << 17 << 19;
        vec11 << 0 << 1 << 2 << 4 << 5 << 6 << 7 << 8 << 10 << 11 << 13 << 14 << 17 << 19;
        vec12 << 0 << 1 << 2 << 4 << 5 << 6 << 7 << 8 << 10 << 11 << 13 << 16 << 17 << 19;
        vec13 << 0 << 4 << 5 << 6 << 7 << 8 << 10 << 11 << 13 << 15 << 16 << 19;
        vec14 << 0 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 13 << 15 << 19;
        vec15 << 0 << 4 << 10 << 11 << 13,17,19;
        vec16 << 0 << 2 << 4 << 6 << 8 << 10 << 11 << 13 << 14 << 15 << 17;
        vec17 << 0 << 1 << 2 << 4 << 6 << 8 << 10 << 11 << 15 << 17 << 18;
        vec18 << 0 << 1 << 2 << 6 << 8 << 10 << 11 << 12 << 13 << 15;
        vec19 << 0 << 1 << 2 << 4 << 5 << 6 << 15 << 16 << 17 << 18;
    }
    vec << vec0 << vec1 << vec2 << vec3
        << vec4 << vec5 << vec6 << vec7 << vec8 << vec9 << vec10 << vec11 << vec12
        << vec13 << vec14 << vec15 << vec16 << vec17 << vec18 << vec19;
    for(size_t i=0;i<20;i++){
        wallhash.insert(i,vec[i]);
    }
}


/*holeLocation() set up predetermined hole locations on grid according to each level
 */
void GameBoard::holeLocation(){
    holePositions = new QPoint*[2];
    if(currentLvl==1){
        holePositions[0] = new QPoint(2,2);
        holePositions[1] = new QPoint(10,10);
    }
    else if(currentLvl==2){
        holePositions[0] = new QPoint(2,2);
        holePositions[1] = new QPoint(3,15);
    }
    else{
        holePositions[0] = new QPoint(13,9);
        holePositions[1] = new QPoint(1,18);
    }
}

/*Check if the coordinate is a wall
 */
bool GameBoard::inWall(int x, int y){
    return wallhash.value(x).contains(y);
}

/*Check if the coordinate is a hole
 */
int GameBoard::inHole(int x, int y){
    if(x == holePositions[0]->rx() && y == holePositions[0]->ry()){
        return 1;
    }
    else if(x == holePositions[1]->rx() && y == holePositions[1]->ry()){
        return 2;
    }
    else{
        return 0;
    }
}


/****
 * This part of the code is responsible for making the duck moves.
 *  It is possible that I will add an eagle that eats the duck.
 *  If the duck enters one portal, it will be transfered to the other portal.
 *  If it reaches egg, game is over.
 *  If it tries to hit the wall, the action will be denied.
 *  If the hawk reaches duck first, game over
*/
void GameBoard::keyPressEvent(QKeyEvent *event){

    int x = duckPosition->rx();
    int y = duckPosition->ry();
if(gameOn){
    switch (event->key()) {
    case Qt::Key_A:
        if(x != 0)
            updateDuck(x,y,x-1,y);

        break;
    case Qt::Key_D:
        if(x != boardSize-1)
            updateDuck(x,y,x+1,y);

        break;
    case Qt::Key_W:
        if(y != 0)
            updateDuck(x,y,x,y-1);

        break;
    case Qt::Key_S:
        if(y != boardSize-1)
            updateDuck(x,y,x,y+1);

        break;

    default:
        QWidget::keyPressEvent(event);
    }


    QCoreApplication::processEvents();
    repaint();
}


    return;
}


void GameBoard::paintEvent(QPaintEvent *e) {

    int dx = duckPosition->rx();
    int dy = duckPosition->ry();
    int hx = hawkPosition->rx();
    int hy = hawkPosition->ry();

    label[dy*boardSize+dx]->setPixmap(*duck);
    label[dy*boardSize+dx]->setScaledContents(true);
    label[hy*boardSize+hx]->setPixmap(*hawk);
    label[hy*boardSize+hx]->setScaledContents(true);
}


void GameBoard::showEvent(QShowEvent *e) {

    this->activateWindow();
    this->setFocus();
    QWidget::showEvent(e);
}

/*update new duck positions and refill old duck position with pixmap
 */
void GameBoard::updateDuck(int px, int py, int nx, int ny) {
    if(!inWall(ny,nx)&&inHole(ny,nx)==0&&!(nx==boardSize-1 && ny==boardSize-1)){
        duckPosition->setX(nx);
        duckPosition->setY(ny);
        if(holePassed){
            label[py*boardSize+px]->setPixmap(*hole);
            label[py*boardSize+px]->setScaledContents(true);
            holePassed = false;
        }
        else{
            label[py*boardSize+px]->setPixmap(*grass);
            label[py*boardSize+px]->setScaledContents(true);
        }
    }
    else if(inWall(ny,nx)){
        warnings->setText("A duck cannot go through walls!");
    }
    else if(inHole(ny,nx)==1){
        duckPosition->setX(holePositions[1]->ry());
        duckPosition->setY(holePositions[1]->rx());
        label[py*boardSize+px]->setPixmap(*grass);
        label[py*boardSize+px]->setScaledContents(true);
        holePassed = true;
    }
    else if(inHole(ny,nx)==2){
        duckPosition->setX(holePositions[0]->ry());
        duckPosition->setY(holePositions[0]->rx());
        label[py*boardSize+px]->setPixmap(*grass);
        label[py*boardSize+px]->setScaledContents(true);
        holePassed = true;
    }
    else if(nx==boardSize-1 && ny==boardSize-1){
        warnings->setText("You Won!");
        this->gameWon();
        gameOn = false;
    }
}

/*update hawk positions and refill old hawk position with grass or wall
 */
void GameBoard::updateHawk(){
    int dx = duckPosition->rx();
    int dy = duckPosition->ry();
    int hx = hawkPosition->rx();
    int hy = hawkPosition->ry();
if(gameOn){
    if(inWall(hy,hx)){
        label[hy*boardSize+hx]->setPixmap(*wall);
        label[hy*boardSize+hx]->setScaledContents(true);
    }
    else if(inHole(hy,hx)==1||inHole(hy,hx)==2){
        label[hy*boardSize+hx]->setPixmap(*hole);
        label[hy*boardSize+hx]->setScaledContents(true);
    }
    else{
        label[hy*boardSize+hx]->setPixmap(*grass);
        label[hy*boardSize+hx]->setScaledContents(true);
    }

    if(!(dx==hx&&dy==hy)){
        if(hawkStep == 1){
            if(dx<hx){
                hawkPosition->setX(hx-1);
                hawkStep = 2;
            }
            else if(dx>hx){
                hawkPosition->setX(hx+1);
                hawkStep = 2;
            }
            else{
                hawkStep = 2;
                this->updateHawk();
            }
        }
        else if(hawkStep == 2){
            if(dy<hy){
                hawkPosition->setY(hy-1);
                hawkStep = 1;
            }
            else if(dy>hy){
                hawkPosition->setY(hy+1);
                hawkStep = 1;
            }
            else{
                hawkStep = 1;
                this->updateHawk();
            }
        }
    }
    else this->gameLost();
}
}

/*slot for ending the game or reducing lives of duck
 */
void GameBoard::endLost(){
    if(bros == 0){
        popUp->show();
        gameOn = false;
    }
    else{
        lives[bros-1]->clear();
        this->updateDuck(duckPosition->rx(),duckPosition->ry(),0,0);
        repaint();
        QCoreApplication::processEvents();
        --bros;
    }
    return;

}
