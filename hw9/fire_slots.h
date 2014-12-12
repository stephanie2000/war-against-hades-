#ifndef FIRE_SLOTS_H
#define FIRE_SLOTS_H

#include "mainwindow.h"

unsigned seedF= std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generatorF (seedF);

/**
 * @brief MainWindow::draw_fire_areas calls paint to paint fire areas on the board that are under
 * the top boundary in which relics are spawned.
 * @param g1 is the top boundary in which relics are spawned.
 */
void MainWindow::draw_fire_areas(int g1){

    QCoreApplication::processEvents();
    repaint();


}

/**
 * @brief MainWindow::check_hero_fire checks to see if the hero is on a
 * fire area and removes a life if this is indeed the case.
 */
void MainWindow :: check_hero_fire(){


    int hx = hero_loc->rx();
    int hy = hero_loc->ry();


for (size_t i=0; i < total_fire_areas;i++){


    if (hx == fire_area[i].rx() && hy == fire_area[i].ry() && fire_area[i].ry() >= gray1 && res_left!=0){

        boxes[fire_area[i].ry()*game_size2+fire_area[i].rx()]->clear();
        boxes[fire_area[i].ry()*game_size2+fire_area[i].rx()]->setPixmap(QPixmap("/Users/stefsanchez/Documents/fire.gif"));
        boxes[fire_area[i].ry()*game_size2+fire_area[i].rx()]->setScaledContents(true);
        res[res_left-1]->clear();
        res_left= res_left - 1;
        hero_loc->setX(4);
        hero_loc->setY(1);

    }//end if


}//end for loop


if (res_left==0){

    timerM->stop();
    timer->stop();
    you_lose();
}

QCoreApplication::processEvents();
repaint();


}

/**
 * @brief MainWindow::fire_countdown takes time away in order fors
 * the fire balls will explode.
 */
void MainWindow::fire_countdown(){

    //also take away fire time
    timeF = timeF.addSecs(-1);

}


/**
 * @brief MainWindow::fire_spot randomly spawns a fire ball around the hero's
 * current position and two fire balls CAN be on the same spot.
 */
void MainWindow::fire_spot(){

    std::uniform_int_distribution<int> distribution(0, 3);
     std::uniform_int_distribution<int> distribution_origin(1, 3);

  exp=0;
  check_once = true;



 int hx = hero_loc->rx();
 int hy = hero_loc->ry();

 int pos[4] = {0,1,2,3};

int new_pos = 0;



for(size_t i=0;i<fire_ball_count;i++){
    new_pos = pos[distribution(generatorF)];

    if (hx==4 && hy==1) {

         new_pos = pos[distribution_origin(generatorF)];

    }

   if(new_pos==0){
           fire_ball[i].setY(hy-1 % game_size1);
            fire_ball[i].setX(hx%game_size2); //TRY &game_size1
   }
   else if (new_pos==1){

            fire_ball[i].setY(hy % game_size1);
            fire_ball[i].setX(hx-1 % game_size1);

   }
   else if (new_pos==2){


             fire_ball[i].setY(hy+1 % game_size1);
             fire_ball[i].setX(hx % game_size2);
  }
   else {

             fire_ball[i].setY(hy & game_size1);
             fire_ball[i].setX(hx+1 % game_size1);
   }

}//end for loop

    QCoreApplication::processEvents();
   repaint();

}


/**
 * @brief MainWindow::fire_exp makes the fire balls explode.
 */
void MainWindow::fire_exp(){


    int hx = hero_loc->rx();
    int hy = hero_loc->ry();


for (size_t i=0; i < fire_ball_count;i++){


    if (hx == fire_ball[i].rx() && hy == fire_ball[i].ry() && res_left!=0){


        boxes[fire_ball[i].ry()*game_size2+fire_ball[i].rx()]->clear();
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



    exp = 1; //set to 1 in order to repaint with EXPLODED fire ball


     QTimer::singleShot(1000, this, SLOT(fire_clear()));


    QCoreApplication::processEvents();
    repaint();




}

/**
 * @brief MainWindow::fire_clear clears away the fire explosion.
 */
void MainWindow::fire_clear(){



     exp=2; //set to 2 in order to repaint with fire gone

     QCoreApplication::processEvents();
     repaint();


     timeF.setHMS(0,0,2);
     timerF->start(1000);
      check_once = false;

}

#endif // FIRE_SLOTS_H
