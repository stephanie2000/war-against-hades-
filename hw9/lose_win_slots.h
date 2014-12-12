#ifndef LOSE_WIN_SLOTS_H
#define LOSE_WIN_SLOTS_H


#include "mainwindow.h"

/**
 * @brief MainWindow::you_lose displays a window showing the player has lost.
 */
void MainWindow::you_lose(){

    QLabel *lose = new QLabel("You have lost the battle against Hades!");

    lose->setStyleSheet("color:gold;"
                        "background-color: black;"
                         "font: bold 15pt \"Times New Roman\";");

    lose->setFixedSize(350,100);
    lose->show();


}

/**
 * @brief MainWindow::you_win displays a window showing the player has won.
 */
void MainWindow::you_win(){


    QLabel *win = new QLabel("You have won the battle against Hades!");

    win->setStyleSheet("color:gold;"
                        "background-color: black;"
                         "font: bold 15pt \"Times New Roman\";");

    win->setFixedSize(350,100);
    win->show();




}


#endif // LOSE_WIN_SLOTS_H

