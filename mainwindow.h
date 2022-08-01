#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QVector>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QScreen>
#include <QFont>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSlider>
#include <QString>
#include <QCheckBox>
#include <QGraphicsOpacityEffect>
#include <QPolygon>
#include <QPainter>
#include <QTimer>
#include <QList>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFile>

#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "pixmap.h"
#include "elementgraphics.h"
#include "mylabel.h"
#include "mymovie.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QWidget *a = new QWidget();
    QGridLayout *layout = new QGridLayout();
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsItemGroup  *group_1 = new QGraphicsItemGroup();

    QSqlDatabase db;

    QVector<pixmap *> vec;

    ElementGraphics *fon;
    Mylabel *lav;
    QPushButton *button_new_game;
    QPushButton *button_record;
    QPushButton *button_nastroiki;

    QPushButton *button_nazad;
    pixmap *pixcolorbackscene;
    pixmap *pixcolorscene;
    QLabel *label_color;
    QSlider * barH;
    QSlider * barV;
    QLabel *label_h;
    QLabel *label_v;
    QLabel *label_nyli;
    QLabel *label_mines;
    QCheckBox *chek_box;
    QGraphicsPixmapItem *item1;//цифра на настройках бекграунда
    Mylabel *labelD;
    Mylabel *labelE;
    Mylabel *labelS;

    ElementGraphics *fongame;
    ElementGraphics *panel;
    int hor_ver;
    bool flagdot=false;
    bool convert_massiv = true;
        int **game_massiv;
    int game_over=1;

    QTimer *timer;
    QPushButton *label_flag;
    QPushButton *label_dot;
    Mylabel *timsek;
    QLabel *chetmin;

    int vremya_resord=1;
    QGroupBox *box;
        QLabel *winrecord;
        QLabel *loserecord;
        QLabel *bestoftime;
        QLabel *bestofmine;
    QLabel *rec;
    QLabel *yaAdmin;
    QPushButton *button_nazad_record;

private slots:

    void first_monitor();
    void nastroiki();
    void newgame();
        void flaginverse();
        void dotinverse();
        void timetimer();
    void deleteverxandflag();
        void deleteflag();

    void pause();
        void endpause();

    void win();
    void lose();
        void endgame();

    void animatoin();
        void statamimation();

    void globD();
    void globE();
    void globS();
    void globChekbox();
    void globHorizontal(int);
    void globVertical(int);
    void color();
    void colorback();

    void back();

    void records();
        void closerecord();

    void exit_game();
        void EG();

};
#endif // MAINWINDOW_H
