#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtMultimedia/QMediaPlayer>
#include <QMainWindow>
#include "config.h"
#include <QTimer>
#include "map.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initutil();
    QVector <QPushButton*> menu_btn;
    int status;
    int choice_y[4];
    int choice;
    QTimer timer;
    QTimer tiptimer;
    QTimer ins_timer;
    QMediaPlayer player;
    Map map;
    bool tipflag = true;
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent *event);
    void startgame();
    void recalc();
    void hidemenu();
    void instruction();
    void menu();

private slots:


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
