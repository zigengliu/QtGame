/*Zigeng Liu
 * 504188798
 * Summury:this is the GameBoard class that provides methods for the object in the game to interact with
 *  each other.
 */

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QPainter>
#include <iostream>
#include <QVector>
#include <QList>
#include <QHash>


namespace Ui {
class GameBoard;
}

class GameBoard : public QWidget
{
    Q_OBJECT

public slots:
    /**
     * @brief updateHawk() updates the hawk's new position with its pixmap and
     *      fills up the old position with wall or grass
     */
    void updateHawk();
    /**
     * @brief endLost() is the slot for ending the game or reducing lives of duck
     */
    void endLost();

signals:
    /**
     * @brief gameLost is the signal that triggers end of game slot endLost()
     */
    void gameLost();
    /**
     * @brief gameLost is the signal that triggers next game level
     */
    void gameWon();

public:
    /**
     * @brief GameBoard is constructor that build the game board and initialize its parameters
     * @param parent is the parent widget
     * @param boardSize is the dimension of the square gridLayout
     * @param level is the default level
     */
    explicit GameBoard(QWidget *parent = 0, size_t boardSize = 20, unsigned int level = 1);
    ~GameBoard();

    /**
     * @brief setGrid sets the QGridLayout with pixmaps
     * @param layout is the QGridLayout being setting up
     */
    void setGrid(QGridLayout* layout);
    /**
     * @brief wallLocation defines the locations of walls at each level
     */
    void wallLocation();
    /**
     * @brief holeLocation defines the locations of holw at each level
     */
    void holeLocation();
    /**
     * @brief inWall check if the next position of duck is a wall
     * @param x is the x-coord of the next location
     * @param y is the y-coord of the next location
     * @return
     */
    bool inWall(int x, int y);
    /**
     * @brief inWall check if the next position of duck is a hole
     * @param x is the x-coord of the next location
     * @param y is the y-coord of the next location
     * @return
     */
    int inHole(int x, int y);

    /**
     * @brief keyPressEvent is the event listener that checks the event of key pressing that controls the duck movement
     *      w,a,s,d for four directions of duck movement
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);
    /**
     * @brief updateDuck() updates the duck's new position with its pixmap and
     *      fills up the old position with grass
     * @param px past x-coord
     * @param py past y-coord
     * @param nx new x-coord
     * @param ny new y-coord
     */
    void updateDuck(int px, int py, int nx, int ny);
    void paintEvent(QPaintEvent *e);
    void showEvent(QShowEvent *e);


private:
    Ui::GameBoard *ui;
    size_t boardSize;
    size_t wallArraySize;
    bool gameOn;
    unsigned int currentLvl;
    unsigned int lives_remaining;
    bool holePassed;
    unsigned int hawkStep;
    QLabel* warnings;
    QLabel** lives;
    unsigned int bros;

    QPixmap* duck;
    QPixmap* wall;
    QPixmap* egg;
    QPixmap* hole;
    QPixmap* grass;
    QPixmap* hawk;

    QPoint* duckPosition;
    QPoint* eggPosition;
    QPoint* hawkPosition;
    QPoint** wallPositions;
    QHash<int,QVector<int>> wallhash;
    QPoint** holePositions;
    QLabel** label;

    QWidget* popUp;
    QVBoxLayout* popUpLayout;
    QLabel* popUpTextOver;
    QLabel* popUpTextWon;
};

#endif // GAMEBOARD_H

