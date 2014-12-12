#ifndef RELIC_ACTIONS_H
#define RELIC_ACTIONS_H


#include "mainwindow.h"
#include <iostream>

unsigned SEED = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine GENERATOR (SEED);


/**
 * @brief MainWindow::spawn_relics generates new relic positions without
 * relics being generated in the same position and without being placed
 * in fire areas.
 */
void MainWindow::spawn_relics(){

    std::uniform_int_distribution<int> relic_y_distribution(gray1, gray2);
    std::uniform_int_distribution<int> relic_x_distribution(1, game_size2);

    int h = 0;
    int k = 0;
    relic_loc[h].setX(relic_x_distribution(GENERATOR)%game_size2);
     relic_loc[k].setY(relic_y_distribution(GENERATOR)%game_size1);
     h=1;
     k=1;
     int rx = relic_x_distribution(GENERATOR)%game_size2;
     int ry = relic_y_distribution(GENERATOR)%game_size1;
    bool checkx;
    bool checky;

     //relics can't spawn in same place
    while ( h < num_relics) {

          rx = relic_x_distribution(GENERATOR)%game_size2;


      for ( size_t j = 0; j < h; j++ ) {


             if ( relic_loc[j].rx() == rx ){

                     checkx = false;
                        break;

             }
             if(relic_loc[j].rx() != rx ){


                  checkx = true;

             }



    }//end for loop

      if(checkx) {

           relic_loc[h].setX(rx);
            h = h+1;
      }


   }//end while loop


    //relics can't spawn in same place
   while ( k < num_relics) {

         ry = relic_y_distribution(GENERATOR)%game_size1;


     for ( size_t j = 0; j < k; j++ ) {


            if ( relic_loc[j].ry() == ry ){

                    checky = false;
                       break;

            }
            if(relic_loc[j].ry() != ry ){


                 checky = true;

            }



   }//end for loop

     if(checky) {

          relic_loc[k].setY(ry);
           k = k+1;
     }


  }//end while loop


    //relics cant spawn in fire-get rid of fire
    for (size_t i=0; i < num_relics;i++){


        for (size_t j = 0 ; j < total_fire_areas ; j++){
            int fx = fire_area[j].rx();
            int fy = fire_area[j].ry();



            if(relic_loc[i].rx() == fx && relic_loc[i].ry() == fy){

                      boxes[fy*game_size2+fx]->clear();
                      fire_area[j].setX(0);
                      fire_area[j].setY(0);
            }
        }//end inner for loop

    }//end control for loop

}


/**
 * @brief MainWindow::relics places  relics on the game.
 * @param num_relics is the new total number of relics that
 * need to be collected.
 */
void MainWindow::relics(int num_relics){



    for(size_t i=0;i<num_relics;i++) {

        int px = relic_loc[i].rx();
        int py = relic_loc[i].ry();



        if(px>=0 && py >= 0 && py<game_size1 && px<game_size2) {
            boxes[py*game_size2+px]->setPixmap(*relic);
            boxes[py*game_size2+px]->setScaledContents(true);
        }




    }


    QCoreApplication::processEvents();
    repaint();




}


/**
 * @brief MainWindow::grab_relics registers when a hero picks up a relic.
 * Each time a relic is grabbed, relics remaining decreases.
 */
void MainWindow::grab_relics(){



    int hx = hero_loc->rx();
    int hy = hero_loc->ry();

    for (size_t i=0; i < num_relics;i++){

        if(hx==relic_loc[i].rx() && hy==relic_loc[i].ry()){


           boxes[relic_loc[i].ry()*game_size2 + relic_loc[i].rx()]->setPixmap(*ally_pic);
           boxes[relic_loc[i].ry()*game_size2 + relic_loc[i].rx()]->clear();
           boxes[relic_loc[i].ry()*game_size2 + relic_loc[i].rx()]->setStyleSheet("background-color:gray;");
           relic_loc[i].setX(0);
            relic_loc[i].setY(0);
            if(relics_left!=0) relics_left=relics_left-1;

            break;
        }


    }//end for loop


    if(relics_left==0 && TIME.toString("mm:ss")!="00:00" && gray2!=22){

        gray1 = gray1 + 3;
        gray2 =gray2 + 3;
        advance_game(gray1, gray2);
        draw_fire_areas(gray1);

   }


    QCoreApplication::processEvents();
    repaint();


}


/**
 * @brief MainWindow::clear_relics removes relics from the board
 * if time to collect the relics has run out.
 */
void MainWindow::clear_relics(){

    for(size_t i=0;i<num_relics;i++) {

        int rx = relic_loc[i].rx();
        int ry = relic_loc[i].ry();
        QPointF check_origin;
        check_origin.setX(rx);
        check_origin.setY(ry);

        if (check_origin!=QPointF(0,0)){
            boxes[ry*game_size2+rx]->clear();
            boxes[ry*game_size2+rx]->setStyleSheet("background-color:gray");
            }

      }


}


#endif // RELIC_ACTIONS_H

