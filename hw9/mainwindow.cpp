/*


    The following code creates a main menu (stage 1)
    that remains up. It also creates a faction menu
    (stage 2), race and class menu (stage 3), and finally
    the gameboard (stage 4).

    It also generates the game play. Collect the relics,which
    are the yellow boxes with R. Avoid death by minions. Keep collecting
    relics before the time runs out each round in order to advance and win.

    use arrow keys to move and space bar to collect the relics.

*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player_slots.h"
#include "relic_actions.h"
#include "lose_win_slots.h"
#include "minion_slots.h"
#include "key_paint_slots.h"
#include "fire_slots.h"
#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <QString>
#include <QPushButton>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QSpacerItem>
#include<QIcon>
#include <QGroupBox>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QTimeEdit>
#include <QKeyEvent>
#include <random>
#include <chrono>
#include <iostream>
#include <QDesktopWidget>
#include <QTextBlock>
#include <QTextEdit>
#include <QTextDocument>
#include <QSpacerItem>
#include <QScrollArea>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //start the main menu AND allocate memory by res,relic_loc,hero_loc,minion_loc, fire_ball, and fire_area.
    //STAGE 1
        //stage 1 layouts
        QVBoxLayout *v1_layout = new QVBoxLayout;
        QSpacerItem *top_space = new QSpacerItem(100,250);
        QSpacerItem *mid_space = new QSpacerItem(100,15);

        //stage 1 labels, buttons, images
        QLabel *first = new QLabel("Welcome to the Battle Against Hades!");
        QLabel *descrip1 = new QLabel;
        QLabel *descrip2 = new QLabel;
        Stage_1 = new QLabel;
        QString filename("/Users/stefsanchez/Documents/main_pic.jpg");
        QPushButton *start= new QPushButton("Begin!");
        QPixmap *WoW_pic = new QPixmap(filename);

        Stage_1->setPixmap(*WoW_pic);
        Stage_1->setScaledContents(true);

        first->setTextFormat(Qt::RichText);
        first->setStyleSheet("back-ground color:transparent;");

        descrip1->setTextFormat(Qt::RichText);
        descrip1->setStyleSheet("back-ground color:transparent;"
                                "font: bold 15pt \"Times New Roman\";");

        descrip1->setText("Hades is trying to take over mankind and Mount Olympus!");

        descrip2->setTextFormat(Qt::RichText);
        descrip2->setStyleSheet("back-ground color:transparent;"
                                "font: bold 15pt \"Times New Roman\";");


        descrip2->setText(  "Choose a god and hero to fight the battle against Hades!");



        start->setFixedSize(100,40);
        start->setStyleSheet("color:gold;"
                             "background-color: black;"
                             "font: bold 15pt \"Times New Roman\";");


        v1_layout->setAlignment(Qt::AlignTop);
        v1_layout->addSpacerItem(top_space);
        v1_layout->addWidget(first,0,Qt::AlignCenter);
        v1_layout->addSpacerItem(mid_space);
        v1_layout->addWidget(descrip1,0,Qt::AlignCenter);
        v1_layout->addWidget(descrip2,0,Qt::AlignCenter);
       // v1_layout->addSpacerItem(mid_space);
        v1_layout->addWidget(start,0,Qt::AlignCenter);

        Stage_1->setStyleSheet("color: gold;"
                             "font: bold 20pt \"Times New Roman\";");
        Stage_1->setWindowTitle("Main Menu");
        Stage_1->setLayout(v1_layout);
        Stage_1->setFixedSize(1000,600);

        Stage_1->show();
        allocate();

        QObject::connect(start,SIGNAL(clicked()),this,SLOT(STAGE_2()));


}



MainWindow::~MainWindow()
{
    delete ui;
    delete [] res;
    delete [] hero_loc;
    delete [] minion_loc;
    delete [] fire_ball;
    delete [] fire_area;
    delete [] relic_loc;
    delete [] boxes;
    delete [] grid;
    delete Game;
    delete RES;
    delete horde_pic;
    delete timerM;
    delete timer;
    delete timerF;
    delete time;
    delete relic;

}

/**
 * @brief MainWindow::allocate allocates the memory for
 * res,relic_loc,hero_loc,minion_loc, fire_ball, and fire_area.
 */
void MainWindow::allocate(){



    num_res=3;
    res_left = 3;
    res = new QLabel*[num_res];
    RES = new QWidget;

    horde_pic = new QPixmap("/Users/stefsanchez/Documents/S2_pic_H.jpg");


    time = new QLabel;

    timerM = new QTimer(this); //timer for minions
    timer = new QTimer(this); //timer for relics
    timerF = new QTimer(this);//timer  for fire spots




    //generate the game board
    Game = new QWidget;

    game_size1 = 23;
    game_size2 = 9;
    boxes = new QLabel*[game_size1*game_size2];
    grid= new QGridLayout(Game);

    hero_loc = new QPoint(4,1);

   fire_ball_count = 2;
   fire_ball = new QPoint[fire_ball_count];


    total_fire_areas = 45;
    fire_area = new QPoint[total_fire_areas];
    check_fire=true; // add fire to board that should already be there




    //spawn fire areas

    num_relics = 5;
    relics_left=5;
    relic_loc = new QPoint[num_relics];

    relic = new QPixmap("/Users/stefsanchez/Documents/relic_pic.jpg");


      minions_count = 7;
      minion_loc = new QPoint[minions_count];

}



/**
 * @brief MainWindow::next brings up the game window and closes
 * the gods and heroes menu. It also displays a window for the
 * user to chose a god or hero if not chosen.
 */
void MainWindow::next(){



    if (WA->isChecked()==false && PL->isChecked()==false &&
        PR->isChecked()==false && HN->isChecked()==false &&
        BH->isChecked()==false && RO->isChecked()==false &&
        RO->isChecked()==false && SH->isChecked()==false &&
        SH->isChecked()==false ){

       choose_hero->show();

    }


   else if (HU->isChecked()==false && NE->isChecked()==false &&
       GN->isChecked()==false && DW->isChecked()==false ){


        choose_god->show();


   }

    else {


        STAGE_4();
        Stage_3->close();

    }

}

/**
 * @brief MainWindow::showTime displays the time remaining
 * the user has to collect relics.
 */
void MainWindow::showTime(){

TIME=TIME.addSecs(-1);
time->setText(TIME.toString("mm:ss"));

}



/**
 * @brief MainWindow::draw_game draws the board game only.
 * @param new_gray1 is the top boundary in which relics are bounded above.
 * @param new_gray2 is the bottom boundary in which relics are bounded below.
 */
void MainWindow::draw_game(int new_gray1, int new_gray2){



    for(int i=0;i<game_size1;i++){
        for(int j=0;j<game_size2;j++){


            if (i==0 && j==4)  boxes[i*game_size2+j]->setPixmap(*greek);
                               boxes[i*game_size2+j]->setScaledContents(true);

            if (i < new_gray1)  boxes[i*game_size2+j]->setStyleSheet("background- color:transparent;");



            if( i <=new_gray2 && i >= new_gray1) boxes[i*game_size2+j]->setStyleSheet("background-color: gray;");



            if(i > new_gray2 )  boxes[i*game_size2+j]->setStyleSheet("background-color: red;");


            if (i==22 && j==4)  boxes[i*game_size2+j]->setPixmap(QPixmap("/Users/stefsanchez/Documents/hades.jpg"));
                                boxes[i*game_size2+j]->setScaledContents(true);


       }//end inner for loop
    }//end control loop

}

/**
 * @brief MainWindow::moveHero moves the hero's position.
 * @param px is the current hero's x positon.
 * @param py is the current hero's y positon.
 * @param nx is the hero's new x position.
 * @param ny is the hero's new y position.
 */
void MainWindow::moveHero(int px, int py, int nx, int ny){


    boxes[py*game_size2+px]->clear();
    hero_loc->setX(nx);
    hero_loc->setY(ny);


}



/**
 * @brief MainWindow::check_time checks to see if the user has lost or won.
 * It also checks if the user has collected the relics in the given amount of time.
 * It also regresses the game if the user has not collected the relics in the time given.
 * It also spawns the fire balls and sets the explosion.
 */
void MainWindow::check_time(){


    //check if player has lost the game
    if(gray1==0 && TIME.toString("mm:ss")=="00:00" && relics_left!=0){

        timerM->stop();
        timer->stop();
        you_lose();

    }

    //check if player has won the game
    if(gray2==22 && TIME.toString("mm:ss")!="00:00" && relics_left==0){

        timerM->stop();
        timer->stop();

        you_win();
    }


    //check to see if time has run out to grab relics
    if(TIME.toString("mm:ss")=="00:00" && relics_left!=0 && gray1 != 0){

        timer->stop();
        TIME.setHMS(0,0,15);
        timer->start(1000);
        gray1 = gray1 - 3;
        gray2 = gray2 - 3;
        clear_relics();
        relics_left = num_relics; //reset relics to collect

        //if player ran out of time, the game regresses

         //spawn new relics
        spawn_relics();

        draw_game(gray1,gray2);

        relics(num_relics); //place relics on game
        draw_fire_areas(gray1);
        check_fire=true; // add fire to the board when hades advances



    }//end if from (TIME..)



    //set fire spot every 3 sec ie set the fire ball
    if((timeF.toString("mm:ss")=="00:02") )  {

        if (check_once==true) disconnect(timerF,SIGNAL(timeout()),this,SLOT(fire_spot()));
        if (check_once == false) fire_spot();

    }

    //fire ball explodes after 3 secs
     if((timeF.toString("mm:ss")=="00:00")){

         fire_exp();
         timerF->stop();


     }




}



/**
 * @brief MainWindow::advance_game updates/advances the game if player is winning.
 * @param new_gray1 is the new top boundary in which relics are spawned.
 * @param new_gray2 is the new bottom boundary in which relics are spawned.
 */
void MainWindow::advance_game(int new_gray1, int new_gray2){

    timer->stop();
    TIME.setHMS(0,0,15);
    timer->start(1000);

    std::uniform_int_distribution<int> relic_y_distribution(new_gray1, new_gray2);
    std::uniform_int_distribution<int> relic_x_distribution(1, game_size2);


    relics_left=num_relics; //reset relics left to collect

    //spawn new relics
   spawn_relics();

        draw_game(new_gray1,new_gray2);//update the game

        relics(num_relics); // put relics on game

        check_fire = false; // remove fire from the board when player advances


}


/**
 * @brief MainWindow::Stage_2 shows the instructions of the game.
 */

void MainWindow::STAGE_2(){

      Stage_1->close();
    //STAGE 2

      //stage 2 layouts & spacer items
      QVBoxLayout *v2_layout = new QVBoxLayout;
      QSpacerItem *v2_space1 = new QSpacerItem(0,-100);
      QSpacerItem * v2_space2 = new QSpacerItem(0,1200);
       QSpacerItem * v2_space3 = new QSpacerItem(0,-70);

      Stage_2 = new QLabel;
      Stage_2->setPixmap(QPixmap("/Users/stefsanchez/Documents/stage_2_pic.jpg"));
      Stage_2->setScaledContents(true);
      QLabel *obj = new QLabel("Objective");
      QLabel *instructions = new QLabel("Instructions");
      QLabel *txt = new QLabel;
      QLabel *txtINT = new QLabel;
      QPushButton *next2 = new QPushButton("Next");


      next2->setFixedSize(100,40);
      next2->setStyleSheet("color:gold;"
                           "background-color: black;"
                           "font: bold 15pt \"Times New Roman\";");

      obj->setFixedSize(200,40);
      obj->setStyleSheet("color:gold;"
                          "background-color:transparent;"
                           "font: bold 20pt \"Times New Roman\";");

      instructions->setFixedSize(200,40);
      instructions->setStyleSheet("color:gold;"
                          "background-color:transparent;"
                           "font: bold 20pt \"Times New Roman\";");

    txt->setFixedSize(550,500);
    txtINT->setFixedSize(550,200);

      txt->setWordWrap(true);
      txt->setText(" You're hero starts atop the field, in order to win the battle against Hades you must collect "
                   "relics that spawn in the gray battle zone in a given amount of time(time shown top right). "
                   "Each time you collect all the relics in the time given you advance, otherwise, "
                   "Hades advances. If you advance to the end of the battle field you win. If "
                   "Hades advances all the way to the top of the battle field you have lost.\n"
                  "   Beware of Hades minions! If you encounter a minion you lose one of three lives.\n "
                   "  Also watch out for fire areas that are on the battle field or else you lose "
                   "a life! Hades will also spawn at most 2 fire balls around you as you move "
                   "through the battle field. After two seconds the balls of fire explode. "
                   "If you are on the fire balls when they explode you lose a life!\n "
                    "   Once all lives are lost you have lost the battle. All lives are shown "
                   "at the bottom of the field and once you die you start back atop of the field. \n"
                   "BEWARE: minions, fire balls, and fire areas can be ontop of each! "
                   "(i.e. a minion can go onto a fire area and be hidden) if you land on one "
                   "of these cases you can lose two-three(all) of your lives! So keep a fast eye open! ");

      txtINT->setWordWrap(true);
      txtINT->setText("   Use the following keys: W, A, S, and D, to move your hero  up,left, down, and right, respectively.\n"
                      "   Hit the return (enter) button once your hero is on a relic in order to collect the relic. ");



        v2_layout->addWidget(obj,0,Qt::AlignLeft);
        v2_layout->addSpacerItem(v2_space1);
        v2_layout->addWidget(txt, 0, (Qt::AlignLeft));
        v2_layout->addSpacerItem(v2_space2);
        v2_layout->addWidget(instructions,0,(Qt::AlignLeft));
        v2_layout->addSpacerItem(v2_space3);
        v2_layout->addWidget(txtINT,0,Qt::AlignLeft);
        v2_layout->addWidget(next2,0,(Qt::AlignBottom | Qt::AlignRight));

        Stage_2->setLayout(v2_layout);

        Stage_2->setStyleSheet("color: white;"
                             "font: bold 13pt \"Times New Roman\";");
        Stage_2->setWindowTitle("Objective and Instructions");
       Stage_2->setFixedSize(1000,600);




        QObject::connect(next2, SIGNAL(clicked()), this, SLOT(STAGE_3()));

        Stage_2->show();


}



/**
 * @brief MainWindow::STAGE_3 creates the gods and heroes menu.
 */
void MainWindow::STAGE_3(){

   Stage_2->close();

    //STAGE 3

        //stage 3 layouts
        QVBoxLayout *vR3_layout = new QVBoxLayout; //vertical layout for gods
        QVBoxLayout *vC3_layout = new QVBoxLayout; //vertical layout for heroes
        QHBoxLayout *h3_layout = new QHBoxLayout;

        Stage_3 = new QLabel;
        QGroupBox *RG = new QGroupBox;
        QGroupBox *CG = new QGroupBox;
        QPushButton *next = new QPushButton("Enter the Battle!");


        next->setFixedSize(200,40);
        next->setStyleSheet("color:gold;"
                            "background-color:black;"
                             "font: bold 15pt \"Times New Roman\";");


        QString filename_all("/Users/stefsanchez/Documents/S3_pic.jpg");
        QPixmap *all_pic = new QPixmap(filename_all);
        QLabel *R_text = new QLabel("Choose your God!");
        QLabel *C_text = new QLabel("Choose your Hero!");
        NE = new QPushButton("Zues");
        HU = new QPushButton("Poseidon");
        DW = new QPushButton("Aris");
        GN = new QPushButton("Apollo");


        WA = new QPushButton("Achilles");
        BH = new QPushButton("Ajax");
        PL = new QPushButton("Hercules");
        PR = new QPushButton("Jason");
        HN = new QPushButton("Odysseus");
        RO = new QPushButton("Perseus");
        SH = new QPushButton("Theseus");

        QPixmap pix_poseidon("/Users/stefsanchez/Documents/poseidon.jpg");
        QIcon icon_poseidon(pix_poseidon.scaled(QSize(88,88)));
        QPixmap pix_zues("/Users/stefsanchez/Documents/zues.jpg");
        QIcon icon_zues(pix_zues.scaled(QSize(88,88)));
        QPixmap pix_aris("/Users/stefsanchez/Documents/aris.jpg");
        QIcon icon_aris(pix_aris.scaled(QSize(88,88)));
        QPixmap pix_apollo("/Users/stefsanchez/Documents/apollo.jpg");
        QIcon icon_apollo(pix_apollo.scaled(QSize(88,88)));


        QPixmap pix_achilles("/Users/stefsanchez/Documents/achilles.jpg");
        QIcon icon_achilles(pix_achilles.scaled(QSize(88,88)));
        QPixmap pix_hercules("/Users/stefsanchez/Documents/hercules.jpg");
        QIcon icon_hercules(pix_hercules.scaled(QSize(88,88)));
        QPixmap pix_jason("/Users/stefsanchez/Documents/jason.jpg");
        QIcon icon_jason(pix_jason.scaled(QSize(88,88)));
        QPixmap pix_theseus("/Users/stefsanchez/Documents/theseus.jpg");
        QIcon icon_theseus(pix_theseus.scaled(QSize(88,88)));
        QPixmap pix_ajax("/Users/stefsanchez/Documents/ajax.jpg");
        QIcon icon_ajax(pix_ajax.scaled(QSize(88,88)));
        QPixmap pix_perseus("/Users/stefsanchez/Documents/perseus.jpg");
        QIcon icon_perseus(pix_perseus.scaled(QSize(88,88)));
        QPixmap pix_odysseus("/Users/stefsanchez/Documents/odysseus.jpg");
        QIcon icon_odysseus(pix_odysseus.scaled(QSize(88,88)));



        NE->setIcon(icon_zues);
        NE->setFlat(true);
        NE->setIconSize(QSize(60, 80));
        HU->setIcon(icon_poseidon);
        HU->setFlat(true);
        HU->setIconSize(QSize(60, 80));
        DW->setIcon(icon_aris);
        DW->setFlat(true);
        DW->setIconSize(QSize(60, 80));
        GN->setIcon(icon_apollo);
        GN->setFlat(true);
        GN->setIconSize(QSize(60, 80));

        WA->setIcon(icon_achilles);
        WA->setFlat(true);
        WA->setIconSize(QSize(60, 80));
        BH->setIcon(icon_ajax);
        BH->setFlat(true);
        BH->setIconSize(QSize(60, 80));
        PL->setIcon(icon_hercules);
        PL->setFlat(true);
        PL->setIconSize(QSize(60, 80));
        PR->setIcon(icon_jason);
        PR->setFlat(true);
        PR->setIconSize(QSize(60, 80));
        HN->setIcon(icon_odysseus);
        HN->setFlat(true);
        HN->setIconSize(QSize(60, 80));
        RO->setIcon(icon_perseus);
        RO->setFlat(true);
        RO->setIconSize(QSize(60, 80));
        SH->setIcon(icon_theseus);
        SH->setFlat(true);
        SH->setIconSize(QSize(60, 80));


        //advance to game from choosing a god and hero
        QObject::connect(next, SIGNAL(clicked()), this, SLOT(next()));

        //group race radio buttons together
        vR3_layout->setAlignment(Qt::AlignTop);
        vR3_layout->addWidget(R_text);
        vR3_layout->addWidget(DW,0,Qt::AlignLeft);
        vR3_layout->addWidget(GN,0,Qt::AlignLeft);
        vR3_layout->addWidget(HU,0,Qt::AlignLeft);
        vR3_layout->addWidget(NE, 0,Qt::AlignLeft);



        RG->setLayout(vR3_layout);

        //group class radio buttons together
        vC3_layout->setAlignment(Qt::AlignTop);
        vC3_layout->addWidget(C_text);
        vC3_layout->addWidget(HN,0,Qt::AlignLeft);
        vC3_layout->addWidget(BH,0,Qt::AlignLeft);
        vC3_layout->addWidget(PL,0,Qt::AlignLeft);
        vC3_layout->addWidget(PR,0,Qt::AlignLeft);
        vC3_layout->addWidget(RO,0,Qt::AlignLeft);
        vC3_layout->addWidget(SH,0,Qt::AlignLeft);
        vC3_layout->addWidget(WA,0,Qt::AlignLeft);
        vC3_layout->addWidget(next,3,Qt::AlignBottom | Qt::AlignRight);

        CG->setLayout(vC3_layout);

        //add both radio group buttons to horizontal layout
        h3_layout->addWidget(RG);
        h3_layout->addWidget(CG);

        //set the text and radio buttons to a main vertical layout


        Stage_3->setLayout(h3_layout);
        Stage_3->setStyleSheet("color:gold;"
                                "font: bold 15pt \"Times New Roman\";");


        Stage_3->setPixmap(*all_pic);
        Stage_3->setScaledContents(true);
        Stage_3->setWindowTitle("Gods and Hereos");
        Stage_3->setFixedSize(1000,600);
        Stage_3->show();


      //make gods and heroes selectable and place
      //corresponding images with the ones chosen
      WA->setCheckable(true);
      PL->setCheckable(true);
      PR->setCheckable(true);
      HN->setCheckable(true);
      BH->setCheckable(true);
      RO->setCheckable(true);
      SH->setCheckable(true);

      HU->setCheckable(true);
      NE->setCheckable(true);
      GN->setCheckable(true);
      DW->setCheckable(true);

      QObject::connect(WA, SIGNAL(clicked()), this, SLOT(check_WA()));
      QObject::connect(PL, SIGNAL(clicked()), this, SLOT(check_PL()));
      QObject::connect(PR, SIGNAL(clicked()), this, SLOT(check_PR()));
      QObject::connect(SH, SIGNAL(clicked()), this, SLOT(check_SH()));
      QObject::connect(BH, SIGNAL(clicked()), this, SLOT(check_BH()));
      QObject::connect(RO, SIGNAL(clicked()), this, SLOT(check_RO()));
      QObject::connect(HN, SIGNAL(clicked()), this, SLOT(check_HN()));

       QObject::connect(NE, SIGNAL(clicked()), this, SLOT(check_NE()));
       QObject::connect(HU, SIGNAL(clicked()), this, SLOT(check_HU()));
       QObject::connect(GN, SIGNAL(clicked()), this, SLOT(check_GN()));
       QObject::connect(DW, SIGNAL(clicked()), this, SLOT(check_DW()));

       choose_hero = new QLabel("You must choose a hero!");
       choose_god=new QLabel("You must choose a God!");

       choose_hero->setStyleSheet("color:gold;"
                           "background-color: black;"
                            "qproperty-alignment: AlignCenter;"
                            "font: bold 15pt \"Times New Roman\";");


       choose_hero->setFixedSize(350,100);

       choose_god->setStyleSheet("color:gold;"
                           "background-color: black;"
                            "qproperty-alignment: AlignCenter;"
                            "font: bold 15pt \"Times New Roman\";");

       choose_god->setFixedSize(350,100);



}



/**
 * @brief MainWindow::STAGE_4 creates the board game, adds the hero, god,
 * hades, relics, minions, and fire areas to the board.
 */
void MainWindow::STAGE_4(){



    //STAGE 4

    //stage 4 layouts and spacing
   QVBoxLayout* v4_layout = new QVBoxLayout;
    QHBoxLayout *hR4_layout = new QHBoxLayout;
    QSpacerItem *v4_space = new QSpacerItem(10,0);
    QHBoxLayout *flag_layout = new QHBoxLayout;
    QSpacerItem *h4_space = new QSpacerItem(550,0);


    //stage 4 setups
    QString filename1("/Users/stefsanchez/Documents/res_pic.jpg");
    QPixmap *res_pic = new QPixmap(filename1);

    Stage_4 = new QLabel;
    Stage_4->setFixedSize(500,800);
    QPixmap *BR = new QPixmap("/Users/stefsanchez/Documents/back_pic.jpg");
    Stage_4->setPixmap(*BR);
    Stage_4->setScaledContents(true);
    QWidget *FLAGS = new QWidget;


    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    connect(timerM, SIGNAL(timeout()), this, SLOT(minions()));
    connect(timerF,SIGNAL(timeout()),this,SLOT(fire_countdown()));

    timerM->start(100);
    timer->start(1000);
    timerF->start(1000);

    timeF = QTime(0,0,2); //time until fire balls explode
    TIME = QTime(0,0,15); // time constraint to get relics

    check_once = false;


    time->setStyleSheet("color:gold;"
                          "font: bold 20pt \"Times New Roman\";");


    flag_layout->addSpacerItem(h4_space);

    flag_layout->addWidget(time,0,Qt::AlignLeft);

    FLAGS->setLayout(flag_layout);


    //generate resurrections
    for (int i=0; i<num_res; i++){

        res[i] = new QLabel;
        res[i]->setPixmap(*res_pic);
        res[i]->setMinimumSize(40,40);
        res[i]->setMaximumSize(40,40);
        res[i]->setScaledContents(true);


        hR4_layout->addWidget(res[i]);
        hR4_layout->setSpacing(0);

       }//end for loop

    RES->setLayout(hR4_layout);

    //round 1 gray boundaries
    gray1 = 9;
    gray2=13;

    grid->setGeometry(QRect());
    grid->setSpacing(0);



   //draw the game
    for(int i=0;i<game_size1;i++){
        for(int j=0;j<game_size2;j++){

            boxes[i*game_size2+j] = new QLabel;
            boxes[i*game_size2+j]->setFixedSize(40,30);
            boxes[i*game_size2+j]->setFrameStyle(1);
            boxes[i*game_size2+j]->setFrameShadow(QFrame::Sunken);

           if (i==0 && j==4)  boxes[i*game_size2+j]->setPixmap(*greek);
                              boxes[i*game_size2+j]->setScaledContents(true);

            if (i < gray1 && i!=0)  boxes[i*game_size2+j]->clear();


            if( i <=gray2 && i >= gray1) boxes[i*game_size2+j]->setStyleSheet("background-color: gray;");


            if(i > gray2 && i!=22)  boxes[i*game_size2+j]->setStyleSheet("background-color: red;");

            if (i==22 && j==4)  boxes[i*game_size2+j]->setPixmap(QPixmap("/Users/stefsanchez/Documents/hades.jpg"));
                                boxes[i*game_size2+j]->setScaledContents(true);



            grid->addWidget(boxes[i*game_size2+j] ,i,j);

       }//end inner for loop
    }//end control loop


    boxes[13]->setPixmap(*ally_pic);
    boxes[13]->setScaledContents(true);


    //spawn fire areas

    std::uniform_int_distribution<int> fire_y(1, game_size1);
    std::uniform_int_distribution<int> fire_x(1, game_size2);
    int fx;
    int fy;

    for (size_t i=0; i < total_fire_areas;i++){

         fx = fire_x(generator)%game_size2;
         fy = fire_y(generator)%game_size1;


       fire_area[i].setX(fx%game_size2);
       fire_area[i].setY(fy%game_size1);

    }//end control for loop


    //spawn relics
    spawn_relics();

    for(size_t i=0;i<num_relics;i++) {
        int rx = relic_loc[i].rx();
        int ry = relic_loc[i].ry();



       boxes[ry*game_size2+rx]->setPixmap(*relic);
       boxes[ry*game_size2+rx]->setScaledContents(true);


    }//end for loop






    minion_loc[5].setY(14);
    minion_loc[5].setX(1);
     boxes[127]->setPixmap(*horde_pic);
     boxes[127]->setScaledContents(true);


    minion_loc[0].setX(2);
    minion_loc[0].setY(14);
    boxes[128]->setPixmap(*horde_pic);
    boxes[128]->setScaledContents(true);

    minion_loc[1].setX(3);
    minion_loc[1].setY(14);
     boxes[129]->setPixmap(*horde_pic);
     boxes[129]->setScaledContents(true);

    minion_loc[2].setY(14);
    minion_loc[2].setX(4);
     boxes[130]->setPixmap(*horde_pic);
     boxes[130]->setScaledContents(true);

    minion_loc[3].setY(14);
    minion_loc[3].setX(5);
     boxes[131]->setPixmap(*horde_pic);
     boxes[131]->setScaledContents(true);

    minion_loc[4].setY(14);
    minion_loc[4].setX(6);
     boxes[132]->setPixmap(*horde_pic);
     boxes[132]->setScaledContents(true);

     minion_loc[6].setY(14);
     minion_loc[6].setX(7);
      boxes[133]->setPixmap(*horde_pic);
      boxes[133]->setScaledContents(true);


    Game->setLayout(grid);


    v4_layout->setSpacing(0);
    v4_layout->addWidget(FLAGS,0,Qt::AlignTop);
    v4_layout->addSpacerItem(v4_space);
    v4_layout->addWidget(Game,0,Qt::AlignCenter);
    v4_layout->addWidget(RES,0);



    Stage_4->setLayout(v4_layout);
    setCentralWidget(Stage_4);
    adjustSize();
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    this->show();


}


