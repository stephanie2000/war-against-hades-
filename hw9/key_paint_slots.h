#ifndef KEY_PAINT_SLOTS_H
#define KEY_PAINT_SLOTS_H

#include "mainwindow.h"
#include <iostream>

/**
 * @brief MainWindow::keyPressEvent registers arrow key event (movement).
 * @param event: points to an event that is taking place, i.e. arrow keys.
 */
void MainWindow::keyPressEvent(QKeyEvent *event){

    int x = hero_loc->rx();
    int y = hero_loc->ry();



    switch (event->key()) {

    case Qt::Key_W:
        if(hero_loc->ry() != 0)
            moveHero(x,y,x,y-1);
        break;

    case Qt::Key_S:
        if(hero_loc->ry() != game_size1-1)
            moveHero(x,y,x,y+1);
        break;

    case Qt::Key_A:
        if(hero_loc->rx() != 0)
            moveHero(x,y,x-1,y);
        break;

    case Qt::Key_D:
        if(hero_loc->rx() != game_size2-1)
            moveHero(x,y,x+1,y);
        break;

    case Qt::Key_Return:
        grab_relics();
        break;

    default:
        QMainWindow::keyPressEvent(event);
    }
    QCoreApplication::processEvents();
    repaint();
    return;


}

/**
 * @brief MainWindow::paintEvent:paints everytime there is a game update.
 * @param e: points to what is to be painted.
 */
void MainWindow::paintEvent(QPaintEvent *e){

    //HERO
    int hx = hero_loc->rx();
    int hy = hero_loc->ry();

    boxes[hy*game_size2+hx]->setPixmap(*ally_pic);
    boxes[hy*game_size2+hx]->setScaledContents(true);

    //GOD
    boxes[0*game_size2+4]->setPixmap(*greek);
    boxes[0*game_size2+4]->setScaledContents(true);

    //HADES
    boxes[22*game_size2+4]->setPixmap(QPixmap("/Users/stefsanchez/Documents/hades.jpg"));
    boxes[22*game_size2+4]->setScaledContents(true);

    //FIRE BALL AND BALL EXPLOSION
  for (size_t i = 0; i < fire_ball_count; i++){

      int fx = fire_ball[i].rx();
      int fy = fire_ball[i].ry();

    //paint a fire ball
    if (exp==0 && fx>=0 && fy>=0 && fy < game_size1 && fx < game_size2){

    boxes[fy*game_size2+fx]->setPixmap(QPixmap("/Users/stefsanchez/Documents/fire_ball.jpg"));
    boxes[fy*game_size2+fx]->setScaledContents(true);

    //repaint fire areas back if a fire ball spawns on one
    for (size_t i =0;i<total_fire_areas;i++){

    if(fx == fire_area[i].rx() && fy == fire_area[i].ry()){

     boxes[fy*game_size2+fx]->setPixmap(QPixmap("/Users/stefsanchez/Documents/fire.gif"));
     boxes[fy*game_size2+fx]->setScaledContents(true);
    }//end if inside for loop
    }//end for loop


    }
    //paint the fire ball explosion
     if (exp==1 && fx>=0 && fy>=0 && fy < game_size1 && fx < game_size2){

         boxes[fy*game_size2+fx]->setPixmap(QPixmap("/Users/stefsanchez/Documents/fire_exp.jpg"));
         boxes[fy*game_size2+fx]->setScaledContents(true);
    }
    //remove fire after it has exploded

     if(exp==2 && fx>=0 && fy>=0 && fy < game_size1 && fx < game_size2 ){
         boxes[fy*game_size2+fx]->clear();


                //repaint fire areas back if a fire ball exploded over one
         for (size_t i =0;i<total_fire_areas;i++){

             if(fx == fire_area[i].rx() && fy == fire_area[i].ry()){

                 boxes[fy*game_size2+fx]->setPixmap(QPixmap("/Users/stefsanchez/Documents/fire.gif"));
                 boxes[fy*game_size2+fx]->setScaledContents(true);
            }//end if inside for loop
         }//end for loop

    }

  }//end fire_ball for loop

  //MINIONS
    for(size_t i=0;i<minions_count;i++) {
        int mx = minion_loc[i].rx();
        int my = minion_loc[i].ry();

        if(mx >= 0 && my >= 0 && my < game_size1 && mx < game_size2) {
            boxes[my*game_size2+mx]->setPixmap(*horde_pic);
            boxes[my*game_size2+mx]->setScaledContents(true);


            for (size_t i =0;i<total_fire_areas;i++){

                if(mx == fire_area[i].rx() && my == fire_area[i].ry()){

                    boxes[my*game_size2+mx]->setPixmap(QPixmap("/Users/stefsanchez/Documents/fire.gif"));
                    boxes[my*game_size2+mx]->setScaledContents(true);
               }//end if inside for loop
            }//end for loop

        }
    }


    //FIRE AREAS
    for(size_t i=0;i<total_fire_areas;i++) {
        int fx = fire_area[i].rx();
        int fy = fire_area[i].ry();

        //paint fire according to the advancement or regression of the game
        if(fx != 0 && fy != 0 && fy >= gray1 && check_fire==true) {
            boxes[fy*game_size2+fx]->setPixmap(QPixmap("/Users/stefsanchez/Documents/fire.gif"));
            boxes[fy*game_size2+fx]->setScaledContents(true);

        }
        else{
            if(fy < gray1)
            boxes[fy*game_size2+fx]->clear();

        }
    }//end for loop

    //RELICS
    for(size_t i=0;i<num_relics;i++) {
        int rx = relic_loc[i].rx();
        int ry = relic_loc[i].ry();


            //paint hero over the relics when hero is on a relic
            if(rx==0 && ry==0 ){

                boxes[ry*game_size2+rx]->clear();
            }

          else{

                if( hx != rx && hy!=ry){
                 boxes[ry*game_size2+rx]->setPixmap(*relic);
                boxes[ry*game_size2+rx]->setScaledContents(true);
                }
                if (hx == rx && hy == ry){

                    boxes[ry*game_size2+rx]->clear();
                    boxes[ry*game_size2+rx]->setStyleSheet("color:black;"
                                                      "background-color:gold;"
                                                       "font: bold 15pt \"Times New Roman\";");
                    boxes[ry*game_size2+rx]->setPixmap(*ally_pic);
                    boxes[ry*game_size2+rx]->setScaledContents(true);


                }//end if's
            }//end if else



}//end for loop

}

#endif // KEY_PAINT_SLOTS_H
