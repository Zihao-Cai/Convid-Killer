#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtMultimedia/QMediaPlayer>
#include <QMainWindow>
#include "config.h"
#include <QTimer>
#include "map.h"
#include "ui_mainwindow.h"
#include "plane.h"
#include "bullet.h"
#include "enemy.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Bulpool* pool;
    QVector <QPushButton*> menu_btn;
    int status;
    int choice_y[4];
    int choice_x[4];
    int choicey;
    int choicex;
    QTimer map_timer;
    QTimer tiptimer;
    QTimer ins_timer;
    QTimer p_timer;
    QTimer e_timer;
    QTimer ch_timer;
    QTimer eap_timer;
    Map map;
    QPixmap myplanes[5];
    Plane* myplane;
    QVector<Enemy> enemys;
    bool tipflag = true;
    bool insflag = true;
    bool chflag = true;

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

private slots:


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
