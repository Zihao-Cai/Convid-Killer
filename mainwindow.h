#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "config.h"
#include <QTimer>
#include "map.h"
#include "ui_mainwindow.h"
#include "plane.h"
#include "bullet.h"
#include "enemy.h"
#include "bombcartoon.h"
#include <QSound>
#include "plusitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector <QPushButton*> menu_btn;
    QVector <QTimer*> game_timers;
    int status;
    int choice_y[4];
    int choice_x[4];
    int choicey;
    int choicex;
    int score;
    QTimer* map_timer = new QTimer;
    QTimer tiptimer;
    QTimer ins_timer;
    QTimer* p_timer = new QTimer;
    QTimer* e_timer = new QTimer;
    QTimer ch_timer;
    QTimer* eap_timer = new QTimer;
    QTimer* ell_timer = new QTimer;
    QTimer* item_timer = new QTimer;
    QTimer* itemflash_timer = new QTimer;
    QTimer* radi_timer = new QTimer;
    Map* map;
    QPixmap myplanes[5];
    Plane* myplane;
    QVector<Enemy> enemys;
    QVector<Bombcartoon> cartoons;
    QVector<Plusitem> items;
    bool tipflag = true;
    bool insflag = true;
    bool chflag = true;
    bool ellflag = true;
    bool itemflash = true;
    bool pause = false;
    bool r_flag = true;
    QSound* menu_bgm;
    QSound* game_bgm;
    QSound* choose_bgm;
    QSound* config_bgm;
    QSound* shoot_bgm;
    QSound* bomb_bgm;
    QSound* getitem_bgm;
    QSound* radi_bgm;
    QDateTime pause_time;
    QDateTime recov_time;

    void initutil();
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent *event);
    void startgame();
    void recalc();
    void hidemenu();
    void instruction();
    void menu();
    void gamepause();
    void gamerecov();
    void changeip();
    void isbomb();
    void isitem();
    void menubgm_ch();
    void gamebgm_ch();
    bool bingdu_collapse(QRect plane_rect, QRect bingdu_rect);

private slots:


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
