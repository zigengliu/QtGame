/*Zigeng Liu
 * 504188798
 * Summury:This is the implementation of mainwindow class: constructor, three void methods for each game level,
 * and a destructor.
 */
#include "mainwindow.h"
#include "gameboard.h"
#include "ui_mainwindow.h"

/*This is the definition of mainwindow class members
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(680,1000);
    this->instructs();
    ui->setupUi(this);    
}

void MainWindow::easy_game_begin() {
    board = new GameBoard(this,20,1);
    this->setCentralWidget(board);
}

void MainWindow::medium_game_begin() {
    board = new GameBoard(this,20,2);
    this->setCentralWidget(board);
}

void MainWindow::hard_game_begin() {
    board = new GameBoard(this,20,3);
    this->setCentralWidget(board);
}

void MainWindow::instructs(){
    insW = new QWidget();
    insW->setFixedSize(600,300);
    v = new QVBoxLayout(insW);
    QString lines = "Instruction for the Duck Runner!\n\n";
    lines = lines + "    Hi player, my name is Runner, I am a duck. I have been traveling for a while and\n";
    lines = lines + "I am worried about my egg. Please help me get to my egg.\n\n";
    lines = lines + "Control: W, A , S, D for four directional movement.\n";
    lines = lines + "Goal: get to the egg but don't let eagle catch me!\n";
    lines = lines + "Rule: I am meat so I cannot go through walls. However, I can sneak into a hole for\n";
    lines = lines + "fast transportation. I have three brothers, if I die, they will continue with\n";
    lines = lines + "my mission, our mission. Protect our egg!\n";
    lines = lines + "To quit, click quit at the bottom of gameplay, and close the window.\n";
//    QFile file("instr.txt");

    instext = new QLabel(lines);
    v->addWidget(instext);

//    file.close();

}

void MainWindow::game_over() {

    // Take the current board game out of the central widget of MainWindow
    QWidget* wid = this->centralWidget();
    wid->setParent(nullptr);
    // Line above will delete the widget gracefully (no memory errors)

    // Display something which says that you lost, maybe display high score.

    // Reset the MainWindow with the initial startup screen
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_insB_clicked()
{
    insW->show();
    return;
}
