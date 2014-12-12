/*


    The following code creates a main menu (stage 1)
    that remains up. It also creates a faction menu
    (stage 2), race and class menu (stage 3), and finally
    the gameboard (stage 4).

    It also generates the game play. Collect the relics,which
    are the yellow boxes with R. Avoid death by minions. Keep collecting
    relics before the time runs out each round in order to advance and win.

    Use arrow keys to move and space bar to collect relics.

*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
#include <QGridLayout>
#include <QGroupBox>
#include<QTimer>
#include <QTime>
#include <QPoint>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimeLine>
#include <QPropertyAnimation>
#include <QGraphicsItemAnimation>
#include <random>
#include <chrono>
#include <QPixmap>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *e);
    void moveHero(int px, int py, int nx, int ny);
    void grab_relics();
    void clear_relics();

    void draw_game(int new_gray1, int new_gray2);
    void advance_game(int new_gray1,int new_gray2);
    void minion_encounter();
    void you_win();
    void you_lose();



public slots:
    void allocate();
    void STAGE_2();
    void STAGE_3();
    void STAGE_4();
    void next();
    void showTime();
    void minions();
    void relics(int num_relics);
    void check_time();
    void fire_spot();
    void fire_clear();
    void fire_exp();
    void fire_countdown();
    void draw_fire_areas(int g1);
    void check_hero_fire();
     void spawn_relics();


    void check_WA();
    void check_HN();
    void check_BH();
    void check_RO();
    void check_SH();
    void check_PL();
    void check_PR();
    void check_NE();
    void check_DW();
    void check_HU();
    void check_GN();


private:
    Ui::MainWindow *ui;
    QLabel *Stage_1;
    QLabel* Stage_2;
    QLabel* Stage_3;
    QLabel* Stage_4;
    QWidget *Game;
    QLabel** boxes;
    QGridLayout *grid;
    QPushButton *A;
    QPushButton* H;
    int game_size1;
    int game_size2;
    int num_res;
    int res_left;
    int num_relics;
    int relics_left;
    int flags_cap;
    int gray1;
    int gray2;
    int exp; //check status of fire_ball, i.e. 0=fire ball, 1 = ball explode, 2 = fire disappears
    int fire_ball_count;
    int total_fire_areas;
    QLabel** res;

    QWidget *RES;
    QLabel *time;
    QTimer *timerM ;//timer for minions
    QTimer *timer; //timer for relics
    QTimer *timerF; // timer for fire spot
    QTime timeF; //time for fire spot
    QTime TIME;
    QPixmap *relic;
    QPoint *hero_loc;
    QPoint *minion_loc;
    QPoint *fire_ball;
    QPoint *fire_area;
    size_t minions_count;
    QPixmap *ally_pic;
    QPixmap *horde_pic;
    QPixmap *greek;
    QLabel *choose_hero;
    QLabel *choose_god;

    QPoint *relic_loc;

    QPushButton *NE ;
    QPushButton*HU ;
    QPushButton *DW ;
    QPushButton*GN ;


    QPushButton *WA ;
    QPushButton *BH ;
    QPushButton *PL ;
    QPushButton *PR ;
    QPushButton *HN ;
    QPushButton *RO ;
    QPushButton *SH ;
    bool NE_check;
    bool HU_check;
    bool DW_check;
    bool GN_check;
    bool WA_check;
    bool BH_check;
    bool PL_check;
    bool PR_check;
    bool HN_check;
    bool RO_check;
    bool SH_check;
    bool check_once;
    bool check_fire;




};

#endif // MAINWINDOW_H


