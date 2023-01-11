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
    int status;
    int choice_y[4];
    int choice_x[4];
    int choicey;
    int choicex;
    int score;
    QTimer map_timer;
    QTimer tiptimer;
    QTimer ins_timer;
    QTimer p_timer;
    QTimer e_timer;
    QTimer ch_timer;
    QTimer eap_timer;
    QTimer ell_timer;
    QTimer item_timer;
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
    QSound* menu_bgm;
    QSound* game_bgm;
    QSound* choose_bgm;
    QSound* config_bgm;
    QSound* shoot_bgm;
    QSound* bomb_bgm;

    void initutil();
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent *event);
    void startgame();
    void recalc();
    void hidemenu();
    void instruction();
    void menu();
    void gamepause();
    void changeip();
    void isbomb();
    void isitem();
    void menubgm_ch();
    void gamebgm_ch();
    bool bingducollapse(QRect plane_rect, QRect bingdu_rect);

private slots:


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
