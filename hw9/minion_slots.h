#ifndef MINION_SLOTS_H
#define MINION_SLOTS_H

#include "mainwindow.h"
#include <random>
#include <chrono>


unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed);


//this place minions on the game, check the time for relics,
// and checks to see if the player has encountered a minion
/**
 * @brief MainWindow::minions places minions on the game without being
 * on relics. Checks time for the relics, checks if hero is on a fire area,
 * and checks if the hero has encountered a minion.
 */
void MainWindow::minions(){

    minion_encounter();
    check_time();
    check_hero_fire();

    int tempx[7];
    int tempy[7];

    //minions can't move onto relics, so hold all current minion positions
    for(size_t i = 0 ; i < minions_count;i++){

        tempx[i] =minion_loc[i].rx();
        tempy[i]  = minion_loc[i].ry();

    }


    std::uniform_real_distribution<double> p(0,1);
    std::uniform_int_distribution<int> x_or_y(0,1);
    std::uniform_int_distribution<int> increment(0,1);

    for(size_t i=0;i<minions_count;i++) {

        int px = minion_loc[i].rx();
        int py = minion_loc[i].ry();


        if(px>=0 && py >= 0 && py<game_size1 && px<game_size2) {
            boxes[py*game_size2+px]->clear();

        }

        int nx = px;
        int ny = py;


        if(p(generator) < 0.1) {

            if(x_or_y(generator) == 0) {
                nx = px + 2*increment(generator)-1;
                if(nx >= -1 && nx <= game_size2)
                    minion_loc[i].setX(nx);
            }
            else {
                ny = py + 2*increment(generator)-1;
                if(ny >= -1 && ny <= game_size1)
                    minion_loc[i].setY(ny);

            }

        }



    }


    //leave minions in current position if the new position is on a relic
    for(size_t i = 0; i < minions_count;i++){

        for(size_t j=0; j < num_relics;j++){

            if(relic_loc[j].rx()== minion_loc[i].rx() && relic_loc[j].ry() == minion_loc[i].ry()){

                minion_loc[i].setX(tempx[i]);
                minion_loc[i].setY(tempy[i]);

            }

        }//end inner for loop



    }//end control for loop


    QCoreApplication::processEvents();
    repaint();




}


/**
 * @brief MainWindow::minion_encounter removes a life from the hero
 * and when all lives have been lost it will call you_lose() to end
 * the game.
 */
void MainWindow::minion_encounter(){


        int hx = hero_loc->rx();
        int hy = hero_loc->ry();


    for (size_t i=0; i < minions_count;i++){


        if (hx == minion_loc[i].rx() && hy == minion_loc[i].ry() && res_left!=0){

            boxes[minion_loc[i].ry()*game_size2+minion_loc[i].rx()]->clear();
            boxes[minion_loc[i].ry()*game_size2+minion_loc[i].rx()]->setPixmap(*horde_pic);
            boxes[minion_loc[i].ry()*game_size2+minion_loc[i].rx()]->setScaledContents(true);
            res[res_left-1]->clear();
            res_left= res_left - 1;
            hero_loc->setX(4);
            hero_loc->setY(1);

        }//end if


    }//end for loop


    if (res_left==0){

        timerM->stop();
        timer->stop();
        timerF->stop();
        you_lose();
    }

    QCoreApplication::processEvents();
    repaint();
}

#endif // MINION_SLOTS_H
