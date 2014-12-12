#ifndef PLAYER_SLOTS_H
#define PLAYER_SLOTS_H

#include "mainwindow.h"

/**
 * @brief MainWindow::check_WA sets the chosem hero and god corresponding images.
 */
void MainWindow::check_WA(){

     ally_pic = new QPixmap(QPixmap("/Users/stefsanchez/Documents/achilles.jpg"));
}

void MainWindow::check_PL(){
     ally_pic = new QPixmap(QPixmap("/Users/stefsanchez/Documents/hercules.jpg"));
}

void MainWindow::check_BH(){
     ally_pic = new QPixmap(QPixmap("/Users/stefsanchez/Documents/ajax.jpg"));
}

void MainWindow::check_SH(){
     ally_pic = new QPixmap(QPixmap("/Users/stefsanchez/Documents/theseus.jpg"));
}

void MainWindow::check_RO(){
     ally_pic = new QPixmap(QPixmap("/Users/stefsanchez/Documents/perseus.jpg"));
}

void MainWindow::check_HN(){
     ally_pic = new QPixmap(QPixmap("/Users/stefsanchez/Documents/odysseus.jpg"));
}

void MainWindow::check_PR(){
     ally_pic = new QPixmap(QPixmap("/Users/stefsanchez/Documents/jason.jpg"));
}

void MainWindow::check_DW(){
     greek = new QPixmap(QPixmap("/Users/stefsanchez/Documents/aris.jpg"));
}

void MainWindow::check_GN(){
     greek = new QPixmap(QPixmap("/Users/stefsanchez/Documents/apollo.jpg"));
}

void MainWindow::check_NE(){
     greek = new QPixmap(QPixmap("/Users/stefsanchez/Documents/zues.jpg"));
}

void MainWindow::check_HU(){
     greek = new QPixmap(QPixmap("/Users/stefsanchez/Documents/poseidon.jpg"));
}






#endif // PLAYER_SLOTS_H
