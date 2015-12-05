/*Zigeng Liu
 * 504188798
 * Summury:This is the mainwindow class that in charge of bridging the three methods for game levels to the ui.
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameboard.h"
#include <QPainter>
#include <QTextStream>
#include <QException>
#include <QVBoxLayout>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void easy_game_begin();
    void medium_game_begin();
    void hard_game_begin();
    void on_insB_clicked();


    void game_over();


public:
    explicit MainWindow(QWidget *parent = 0);
    void instructs();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameBoard* board;
    QWidget* insW;
    QVBoxLayout* v;
    QLabel* instext;
};

#endif // MAINWINDOW_H
