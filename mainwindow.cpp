#include "mainwindow.h"


int global_nastriki_min = 30;
bool global_nuli = 0;
int global_nastroiki_horisontal = 10;
int global_nastroiki_vertical = 16;
int globalColor = 3;
int globalColorBack = 1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QScreen* screen = QApplication::screens().at(0);
    QSize size = screen->availableSize();

    this->resize(/*size.width()*/640,/*size.height()*/960);//640 960
    //this->resize(size.width(),size.height());//640 960
    this->setStyleSheet("background-color: rgb(0, 0, 0);");
    this->setCentralWidget(a);
    a->setLayout(layout);
    layout->addWidget(view);
    view->resize(this->width()-30,this->height()-30);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setStyleSheet("background-color: rgb(0, 0, 0);"
                        "border: 2px solid #000000;");
    view->setScene(scene);
    scene->setSceneRect(view->x(),view->y(),view->width(),view->height());


                              /*database*/

    QFile file("mineswepperbd.db3");
    if((!file.exists())||(!file.open(QIODevice::ReadOnly))){
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
                file.close();
                db = QSqlDatabase::addDatabase("QSQLITE");
                db.setDatabaseName("mineswepperbd.db3");
                db.open();
                QSqlQuery a_query;
                QString str = "CREATE TABLE Records_AND_Settings ("
                                "win integer, "
                                "lose integer, "

                                "best_in_time_mines integer, "
                                "best_in_time_sec integer, "
                                "best_in_time_hor integer, "
                                "best_in_time_ver integer, "

                                "best_on_mines_mines integer, "
                                "best_on_mines_sec integer, "
                                "best_on_mines_hor integer, "
                                "best_on_mines_ver integer, "

                                "global_min integer, "
                                "global_zero integer, "
                                "global_hor integer, "
                                "global_ver integer, "
                                "global_color integer, "
                                "global_color_back integer "
                                   ");";
                a_query.exec(str);
                a_query.prepare("INSERT INTO Records_AND_Settings (win, lose, "
                                 "best_in_time_mines, best_in_time_sec, best_in_time_hor, best_in_time_ver, "
                                 "best_on_mines_mines, best_on_mines_sec, best_on_mines_hor, best_on_mines_ver, "
                                 "global_min, global_zero, global_hor, global_ver, global_color, global_color_back)"
                                "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
                a_query.addBindValue(0);
                a_query.addBindValue(0);
                a_query.addBindValue(0);
                a_query.addBindValue(1000000);
                a_query.addBindValue(0);
                a_query.addBindValue(0);
                a_query.addBindValue(0);
                a_query.addBindValue(0);
                a_query.addBindValue(0);
                a_query.addBindValue(0);
                a_query.addBindValue(30);
                a_query.addBindValue(0);
                a_query.addBindValue(10);
                a_query.addBindValue(16);
                a_query.addBindValue(3);
                a_query.addBindValue(1);
                a_query.exec();
        }
    }
    else{
          file.close();
          db = QSqlDatabase::addDatabase("QSQLITE");
          db.setDatabaseName("mineswepperbd.db3");
          db.open();
    }

    QSqlQuery query;
    query.exec("SELECT global_min, global_zero, global_hor, global_ver, global_color, global_color_back FROM Records_AND_Settings");
    while (query.next()){
        global_nastriki_min = query.value(0).toInt();
        global_nuli = query.value(1).toInt();
        global_nastroiki_horisontal = query.value(2).toInt();
        global_nastroiki_vertical = query.value(3).toInt();
        globalColor = query.value(4).toInt();
        globalColorBack = query.value(5).toInt();
    }
   // db.close();

                            /*first monitor*/

    srand(time(nullptr));

    fon = new ElementGraphics(1,view->width(),view->height());
    fon->setPos(0,0);
    fon->hide();
    scene->addItem(fon);

    lav = new Mylabel();
    lav->setAttribute(Qt::WA_NoSystemBackground);
    MyMovie *mo = new MyMovie(1,view->width()/2.5,view->width()/2.5);
    lav->setMovie(mo);
    lav->setGeometry(view->width()/3,view->height()/10,view->width()/2.5,view->width()/2.5);
    connect(lav,SIGNAL(exit_g()),this,SLOT(exit_game()));
    lav->hide();
    scene->addWidget(lav);

    button_new_game = new QPushButton();
    button_new_game->setText("New Game");
    button_new_game->setAttribute(Qt::WA_NoSystemBackground);
    button_new_game->setStyleSheet("QPushButton {"
                                     "border: 2px solid #000000;"
                                     "background-color: rgb(38, 190, 255);"
                                     "border-radius: 35px;"
                                      "}"
                                   "QPushButton:pressed {"
                                     "border: 2px  solid #000000; "
                                     "background-color: rgb(232, 246, 255); "
                                      "}");
    QFont font = button_new_game->font();
    font.setPixelSize(30);
    button_new_game->setFont(font);
    button_new_game->setGeometry(view->width()/2-view->width()/8,view->height()/8*3.7,view->width()/3.5,view->height()/13);
    connect(button_new_game, SIGNAL(clicked()), this, SLOT(newgame()));
    button_new_game->hide();
    scene->addWidget(button_new_game);

    button_record = new QPushButton();
    button_record->setText("Records");//
    button_record->setAttribute(Qt::WA_NoSystemBackground);
    button_record->setStyleSheet("QPushButton {"
                                     "border: 2px solid #000000;"
                                     "background-color: rgb(0, 138, 198);"
                                     "border-radius: 35px;"
                                      "}"
                                  "QPushButton:pressed {"
                                     "border: 2px  solid #000000; "
                                     "background-color: rgb(232, 246, 255); "
                                      "}");
    button_record->setFont(font);
    button_record->setGeometry(view->width()/2-view->width()/8,view->height()/8*4.8,view->width()/3.5,view->height()/13);
    connect(button_record, SIGNAL(clicked()), this, SLOT(records()));
    button_record->hide();
    scene->addWidget(button_record);

    button_nastroiki = new QPushButton();
    button_nastroiki->setText("Settings");
    button_nastroiki->setAttribute(Qt::WA_NoSystemBackground);
    button_nastroiki->setStyleSheet("QPushButton {"
                                     "border: 2px solid #000000;"
                                     "background-color: rgb(153, 217, 234);"
                                     "border-radius: 35px;"
                                      "}"
                                    "QPushButton:pressed {"
                                     "border: 2px  solid #000000; "
                                     "background-color: rgb(232, 246, 255); "
                                      "}");
    button_nastroiki->setFont(font);
    button_nastroiki->setGeometry(view->width()/2-view->width()/8,view->height()/8*5.9,view->width()/3.5,view->height()/13);
    connect(button_nastroiki, SIGNAL(clicked()), this, SLOT(nastroiki()));
    button_nastroiki->hide();
    scene->addWidget(button_nastroiki);


                                       /* nastroiki */

    button_nazad = new QPushButton();
    button_nazad->setText("Back");
    button_nazad->setAttribute(Qt::WA_NoSystemBackground);
    button_nazad->setStyleSheet("QPushButton {"
                                     "border: 2px solid #000000;"
                                     "background-color: rgb(153, 217, 234);"
                                     "border-radius: 35px;"
                                      "}"
                                    "QPushButton:pressed {"
                                     "border: 2px  solid #000000; "
                                     "background-color: rgb(232, 246, 255); "
                                      "}");
    button_nazad->setFont(font);
    button_nazad->setGeometry(view->width()/2-view->width()/8,view->height()/8*7,view->width()/3.5,view->height()/13);
    connect(button_nazad, SIGNAL(clicked()), this, SLOT(back()));
    button_nazad->hide();
    scene->addWidget(button_nazad);



    QPixmap pixcolor(view->height()/13,view->height()/13);
    QPainter *paint = new QPainter(&pixcolor);
    QPolygon pol;
    pol<<QPoint(0,0)<<QPoint(view->height()/13,0)<<QPoint(view->height()/13,view->height()/13)<<QPoint(0,view->height()/13);
    if(globalColor==0){
        paint->setBrush(QColor(0,0,0));
    }
    else if(globalColor==1){
        paint->setBrush(QColor(255,255,255));
    }
    else if(globalColor==2){
        paint->setBrush(QColor(150,150,150));
    }
    else if(globalColor==3){
        paint->setBrush(QColor(38,190,255));
    }
    else if(globalColor==4){
        paint->setBrush(QColor(63,72,255));
    }
    else if(globalColor==5){
        paint->setBrush(QColor(250,250,210));
    }
    else if(globalColor==6){
        paint->setBrush(QColor(177,254,189));
    }
    else if(globalColor==7){
        paint->setBrush(QColor(255,123,123));
    }
    else if(globalColor==8){
        paint->setBrush(QColor(202,142,215));
    }
    else if(globalColor==9){
        paint->setBrush(QColor(255,169,83));
    }
    paint->setPen(QPen(Qt::black,6,Qt::SolidLine));
    paint->drawPolygon(pol);
    delete paint;

    QPixmap pixcolorback(view->height()/13,view->height()/13);
    QPainter *paint2 = new QPainter(&pixcolorback);
    QPolygon pol2;
    pol2<<QPoint(0,0)<<QPoint(view->height()/13,0)<<QPoint(view->height()/13,view->height()/13)<<QPoint(0,view->height()/13);
    if(globalColorBack==0){
        paint2->setBrush(QColor(0,0,0));
    }
    else if(globalColorBack==1){
        paint2->setBrush(QColor(255,255,255));
    }
    else if(globalColorBack==2){
        paint2->setBrush(QColor(150,150,150));
    }
    else if(globalColorBack==3){
        paint2->setBrush(QColor(38,190,255));
    }
    else if(globalColorBack==4){
        paint2->setBrush(QColor(63,72,255));
    }
    else if(globalColorBack==5){
        paint2->setBrush(QColor(250,250,210));
    }
    else if(globalColorBack==6){
        paint2->setBrush(QColor(177,254,189));
    }
    else if(globalColorBack==7){
        paint2->setBrush(QColor(255,123,123));
    }
    else if(globalColorBack==8){
        paint2->setBrush(QColor(202,142,215));
    }
    else if(globalColorBack==9){
        paint2->setBrush(QColor(255,169,83));
    }
    paint2->setPen(QPen(Qt::black,6,Qt::SolidLine));
    paint2->drawPolygon(pol2);
    delete paint2;

    pixcolorbackscene= new pixmap();
    pixcolorbackscene->setPixmap(pixcolorback);
    pixcolorbackscene->setPos(view->width()/2-view->height()/13+10,view->height()/8*5.9+15);//638//7154
    scene->addItem(pixcolorbackscene);
    QString ran;
    ran.setNum(1+rand()%7);
    QPixmap pixmapa1 (":/new/prefix1/"+ran+".png");
    pixmapa1 = pixmapa1.scaled(view->height()/17,view->height()/17,Qt::KeepAspectRatio);
    item1 = new QGraphicsPixmapItem();
    item1->setPixmap(pixmapa1);
    if(ran == "8"||ran == "6"||ran == "3")
        item1->setPos(pixcolorbackscene->pos()+(QPointF(view->height()/13,view->height()/13)-QPointF(view->height()/15,view->height()/15))+QPointF(5,0));
    else
        item1->setPos(pixcolorbackscene->pos()+(QPointF(view->height()/13,view->height()/13)-QPointF(view->height()/15,view->height()/15)));
    connect(pixcolorbackscene,SIGNAL(_7()),this, SLOT(colorback()));
    pixcolorbackscene->hide();
    item1->hide();
    scene->addItem(item1);

    pixcolorscene= new pixmap();
    pixcolorscene->setPixmap(pixcolor);
    pixcolorscene->setPos(view->width()/2+20,view->height()/8*5.9+15);
    connect(pixcolorscene,SIGNAL(_7()),this, SLOT(color()));
    pixcolorscene->hide();
    scene->addItem(pixcolorscene);

    label_color = new QLabel();
    label_color->setStyleSheet("QLabel {"
                               "border-bottom: 6px solid #3e48cc;"
                               "border-right: 6px solid #3e48cc;"
                               "border-bottom-right-radius: 15px;"
                               "background-color: rgb(119,255,255);"
                                 "}");
    label_color->setGeometry(view->width()/2-view->width()/8-view->width()/22+view->height()/20/2-3,view->height()/8*3+view->height()/20/2-3,(view->width()/2-view->width()/8+view->height()/20-view->width()/22)-(view->width()/2-view->width()/8-view->width()/22+view->height()/20/2-3),(view->height()/8*3+view->height()/20)-(view->height()/8*3+view->height()/20/2-3));
    label_color->hide();
    scene->addWidget(label_color);

    barH = new QSlider();
    barH->setOrientation(Qt::Horizontal);
    barH->setAttribute(Qt::WA_NoSystemBackground);
    barH->setMinimum(5);
    barH->setMaximum(30);
    barH->setValue(global_nastroiki_horisontal);
    QString str;
    str.setNum(view->width()/20);
    QString str2;
    str2.setNum(view->height()/20/2-3);
    barH->setStyleSheet("QSlider::handle:horizontal {"
                            "border: 1px solid #000000;"
                            "border-radius: 6px;"
                            "background: rgb(38,190,255);"
                            "margin: -"+str2+"px 0;"
                            "width:" +str+"px;"
                             "}"
                       "QSlider::groove:horizontal {"
                            "background: rgb(63,72,204);"
                            "height: 6px;"
                             "}"
                       "QSlider::handle:horizontal:pressed {"
                            "background: rgb(232, 246, 255);"
                             "}");
    barH->setGeometry(view->width()/2-view->width()/8+view->height()/20-view->width()/22,view->height()/8*3,view->width()/3.5,view->height()/20);
    barH->hide();
    scene->addWidget(barH);

    barV = new QSlider();
    barV->setOrientation(Qt::Vertical);
    barV->setAttribute(Qt::WA_NoSystemBackground);
    barV->setMinimum(5);
    barV->setMaximum(30);
    barV->setValue(global_nastroiki_vertical);
    barV->setInvertedAppearance(true);
    barV->setStyleSheet("QSlider::handle:vertical {"
                            "border: 1px solid #000000;"
                            "border-radius: 6px;"
                            "background: rgb(38,190,255);"
                            "margin: 0 -"+str2+"px;"
                            "height:"+str+"px;"
                             "}"
                       "QSlider::groove:verical {"
                            "background: rgb(63,72,204);"
                            "width: 6px;"
                             "}"
                       "QSlider::handle:vertical:pressed {"
                            "background: rgb(232, 246, 255);"
                             "}");
    barV->setGeometry(view->width()/2-view->width()/8-view->width()/22,view->height()/8*3+view->height()/20,view->height()/20,view->width()/3.5);
    barV->hide();
    scene->addWidget(barV);

    label_h = new QLabel();
    label_h ->setNum(global_nastroiki_horisontal);
    label_h->setAlignment(Qt::AlignCenter);
    label_h->setAttribute(Qt::WA_NoSystemBackground);
    label_h->setStyleSheet("QLabel {"
                            "font-size: 20px;"
                            "background-color: rgb(119,255,255);"
                             "}");
    label_h->setGeometry(view->width()/2-view->width()/8+view->height()/20-view->width()/22+view->width()/3.5,view->height()/8*3,view->height()/20,view->height()/20);
    label_h->hide();
    scene->addWidget(label_h);

    label_v = new QLabel();
    label_v->setNum(global_nastroiki_vertical);
    label_v->setAlignment(Qt::AlignCenter);
    label_v->setAttribute(Qt::WA_NoSystemBackground);
    label_v->setStyleSheet("QLabel {"
                            "font-size: 20px;"
                            "background-color: rgb(119,255,255);"
                             "}");
    label_v->setGeometry(view->width()/2-view->width()/8-view->width()/22,view->height()/8*3+view->height()/20+view->width()/3.5,view->height()/20,view->height()/20-10);
    label_v->hide();
    scene->addWidget(label_v);

    connect(barH, SIGNAL(valueChanged(int)),label_h,SLOT(setNum(int)));
    connect(barV, SIGNAL(valueChanged(int)),label_v,SLOT(setNum(int)));
    connect(barH, SIGNAL(valueChanged(int)),this,SLOT(globHorizontal(int)));
    connect(barV, SIGNAL(valueChanged(int)),this,SLOT(globVertical(int)));

    label_nyli = new QLabel();
    label_nyli->setAttribute(Qt::WA_NoSystemBackground);
    label_nyli->setAlignment(Qt::AlignCenter);
    label_nyli->setText("To display the zeros");
    label_nyli->setStyleSheet("QLabel {"
                            "font-size: 20px;"
                             "}");
    label_nyli->setGeometry(view->width()/2-view->width()/8-view->width()/22,view->height()/8*5.4,view->width()/3,view->height()/20);
    label_nyli->hide();
    scene->addWidget(label_nyli);

    label_mines = new QLabel();
    label_mines->setAttribute(Qt::WA_NoSystemBackground);
    label_mines->setAlignment(Qt::AlignCenter);
    label_mines->setText("Mines");
    label_mines->setStyleSheet("QLabel {"
                            "font-size: 20px;"
                             "}");
    label_mines->setGeometry(view->width()/3+view->width()/3/2-10,view->height()/8*3+view->height()/20+view->width()/3.5/3+view->height()/15,view->height()/15*2,view->height()/20);
    label_mines->hide();
    scene->addWidget(label_mines);

    chek_box = new QCheckBox();
    chek_box->setChecked(global_nuli);
    QString str3;
    str3.setNum(view->height()/20/2);
    chek_box->setAttribute(Qt::WA_NoSystemBackground);
    chek_box->setStyleSheet("QCheckBox::indicator {"
                              "border: 2px solid #000000;"
                              "width:"+str3+"px;"
                              "height: "+str3+"px;"
                               "}"
                            "QCheckBox::indicator:unchecked {"
                              "background-color: rgb(119,255,255);"
                               "}"
                            "QCheckBox::indicator:checked {"
                              "background-color: rgb(0,0,0);"
                        "}");
    chek_box->setGeometry(view->width()/2-view->width()/8-view->width()/22+view->width()/3,label_nyli->y()+label_nyli->height()/4,view->height()/20/2,view->height()/20/2+5);
    scene->addWidget(chek_box);
    chek_box->hide();
    connect(chek_box,SIGNAL(clicked()),this,SLOT(globChekbox()));


    labelS = new Mylabel();
    QString strS;
    strS.setNum(global_nastriki_min/100);
    QPixmap pixmapS (":/new/prefix1/"+strS+".png");
    labelS->setAttribute(Qt::WA_NoSystemBackground);
    pixmapS = pixmapS.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    labelS->setPixmap(pixmapS);
    labelS->setGeometry(view->width()/3+view->width()/3/2-40,view->height()/8*3+view->height()/20+view->width()/3.5/3,view->height()/15,view->height()/15);
    scene->addWidget(labelS);
    labelS->hide();
    connect(labelS,SIGNAL(nastr_m()),this,SLOT(globS()));

    labelD = new Mylabel();
    QString strd;
    strd.setNum(global_nastriki_min%100/10);
    QPixmap pixmapD (":/new/prefix1/"+strd+".png");
    labelD->setAttribute(Qt::WA_NoSystemBackground);
    pixmapD = pixmapD.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    labelD->setPixmap(pixmapD);
    labelD->setGeometry(view->width()/3+view->width()/3/2+view->height()/15+5-40,view->height()/8*3+view->height()/20+view->width()/3.5/3,view->height()/15,view->height()/15);
    scene->addWidget(labelD);
    labelD->hide();
    connect(labelD,SIGNAL(nastr_m()),this,SLOT(globD()));

    labelE = new Mylabel();
    QString stre;
    stre.setNum(global_nastriki_min%10);
    QPixmap pixmapE (":/new/prefix1/"+stre+".png");
    labelE->setAttribute(Qt::WA_NoSystemBackground);
    pixmapE = pixmapE.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    labelE->setPixmap(pixmapE);
    labelE->setGeometry(view->width()/3+view->width()/3/2+2*view->height()/15+10-40,view->height()/8*3+view->height()/20+view->width()/3.5/3,view->height()/15,view->height()/15);
    scene->addWidget(labelE);
    labelE->hide();
    connect(labelE,SIGNAL(nastr_m()),this,SLOT(globE()));



                                    /* game */

    fongame = new ElementGraphics(4,view->width(),view->height());
    fongame->setPos(0,0);
    group_1->addToGroup(fongame);

    panel = new ElementGraphics(2,view->width(),view->height()/10);
    panel->setPos(0,view->height()/10*9+5);
    group_1->addToGroup(panel);
    group_1->hide();
    scene->addItem(group_1);

    QPixmap pixmapfalg (":/new/prefix1/f.png");
    pixmapfalg = pixmapfalg.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    label_flag = new QPushButton();
    label_flag->setAttribute(Qt::WA_NoSystemBackground);
    label_flag->setStyleSheet("QPushButton  {"
                              "border: 3px solid #000000;"
                              "background-color: rgb(197,234,255);"
                              "border-radius: 15px;"
                              "}");
    label_flag->setIcon(pixmapfalg);
    label_flag->setIconSize(QSize(view->height()/17,view->height()/17));
    label_flag->setGeometry(view->width()/2-(view->height()/13)-10,(view->height()/10*9)+(view->height()/10/8)+5,view->height()/13,view->height()/13);
    connect(label_flag,SIGNAL(pressed()),this,SLOT(flaginverse()));
    label_flag->hide();
    scene->addWidget(label_flag);

    QPixmap pixmapdot (":/new/prefix1/t.png");
    pixmapdot = pixmapdot.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    label_dot = new QPushButton();
    label_dot->setAttribute(Qt::WA_NoSystemBackground);
    label_dot->setStyleSheet("QPushButton {"
                         "border: 3px solid #000000;"
                         "background-color: rgb(0,220,220);"
                         "padding-left: 2px;"
                         "border-radius: 15px;"
                          "}");
    label_dot->setIcon(pixmapdot);
    label_dot->setIconSize(QSize(view->height()/17,view->height()/17));
    label_dot->setGeometry(view->width()/2+10,(view->height()/10*9)+(view->height()/10/8)+5,view->height()/13,view->height()/13);
    connect(label_dot,SIGNAL(pressed()),this,SLOT(dotinverse()));
    label_dot->hide();
    scene->addWidget(label_dot);

    timsek= new Mylabel();
    timsek->setNum(vremya_resord); //проверить 1000
    QString timstr;
    timstr.setNum(view->height()/15);
    timsek->setAlignment(Qt::AlignCenter);
    QFont font1;
    font1.setPixelSize(view->height()/15);
    timsek->setFont(font1);
    timsek->setStyleSheet("QLabel {"
                          "background-color: rgb(197,234,255);"
                         // "font: bold italic large \"Times New Roman\";"
                          "font-family: \"Times New Roman\";"
                     //     "font-size: "+timstr+"px;"
                          "font-style: italic;"
                          ""
                          "}");
    timsek->setGeometry((view->width()/2-(view->height()/13)-10)/4-25,(view->height()/10*9)+(view->height()/10/8)+5,(view->width()/2-(view->height()/13)-10)/4*3,view->height()/13);
    connect(timsek,SIGNAL(nastr_m()),this,SLOT(pause()));
    timsek->hide();
    scene->addWidget(timsek);

    chetmin= new QLabel();
    chetmin->setNum(global_nastriki_min);
    QString chrtminstr;
    chrtminstr.setNum(view->height()/15);
    chetmin->setAlignment(Qt::AlignCenter);
    chetmin->setStyleSheet("QLabel {"
                          "background-color: rgb(197,234,255);"
                          "border: 5px solid #000000;"
                          "border-radius: 15px;"
                          "border-color: rgb(0,220,220);"
                          "font-family: \"Times New Roman\";"
                          "font-size: "+chrtminstr+"px;"
                          "}");
    chetmin->setGeometry(view->width()/2+10+view->height()/13+(view->width()-(view->width()/2+10+view->height()/13))/6,(view->height()/10*9)+(view->height()/10/8)+4,((view->width()-(view->width()/2+10+view->height()/13))/6*4),view->height()/13);
    chetmin->hide();
    scene->addWidget(chetmin);


                                   /* record */

    box = new QGroupBox();
    QVBoxLayout *Vloyout = new QVBoxLayout();
    winrecord = new QLabel();
    winrecord->setText("WIN\n50");
    winrecord->setAlignment(Qt::AlignCenter);
    winrecord->setStyleSheet("QLabel {"
                             "color: rgb(40,208,5);"
                             "font-size: 25px;"
                             "border-bottom: 1px solid #000000;"
                              "}");
    loserecord = new QLabel();
    loserecord->setText("LOSE\n100");
    loserecord->setAlignment(Qt::AlignCenter);
    loserecord->setStyleSheet("QLabel {"
                              "color: rgb(255,45,50);"
                              "font-size: 25px;"
                              "border-top: 1px solid #000000;"
                               "}");
    bestoftime = new QLabel();
    bestoftime->setText("BEST IN TIME\n50m 200s 20h 10v");
    bestoftime->setAlignment(Qt::AlignCenter);
    bestoftime->setStyleSheet("QLabel {"
                             "color: rgb(205,205,3);"
                             "font-size: 25px;"
                              "border-top: 1px solid #000000;"
                              "}");
    bestofmine = new QLabel();
    bestofmine->setText("BEST ON MINES\n50m 2200s 20h 10v");
    bestofmine->setAlignment(Qt::AlignCenter);
    bestofmine->setStyleSheet("QLabel {"
                             "color: rgb(114,94,255);"
                             "font-size: 25px;"
                              "border-top: 1px solid #000000;"
                              "}");
    Vloyout->addWidget(winrecord);
    Vloyout->addWidget(loserecord);
    Vloyout->addWidget(bestoftime);
    Vloyout->addWidget(bestofmine);

    box->setLayout(Vloyout);

    box->setStyleSheet("QGroupBox {"
                       "border: 5px solid #000000;"
                       "border-radius: 30px;"
                       "background-color: rgb(119,255,255);"
                       "}");

    box->setGeometry(view->width()/2-view->width()/7,view->height()/8*3.7,view->width()/3.5,view->height()/3);
    box->hide();
    scene->addWidget(box);

    rec = new QLabel();
    rec->setText("RECORDS");
    rec->setAlignment(Qt::AlignCenter);
    rec->setStyleSheet("QLabel {"
                             "font-size: 40px;"
                             "background-color: rgb(119,255,255);"
                              "}");
    rec->setGeometry(view->width()/2-view->width()/7,view->height()/8*3.7-55,box->width(),40);
    rec->hide();
    scene->addWidget(rec);

    yaAdmin = new QLabel();
    yaAdmin->setText("Made by Moonshiner");
    yaAdmin->setAlignment(Qt::AlignCenter);
    yaAdmin->setStyleSheet("QLabel {"
                             "font-size: 20px;"
                             "background-color: rgb(119,255,255);"
                              "}");
    yaAdmin->hide();
    scene->addWidget(yaAdmin);

    button_nazad_record = new QPushButton();
    button_nazad_record->setText("Back");
    button_nazad_record->setAttribute(Qt::WA_NoSystemBackground);
    button_nazad_record->setStyleSheet("QPushButton {"
                                     "border: 2px solid #000000;"
                                     "background-color: rgb(153, 217, 234);"
                                     "border-radius: 35px;"
                                      "}"
                                    "QPushButton:pressed {"
                                     "border: 2px  solid #000000; "
                                     "background-color: rgb(232, 246, 255); "
                                      "}");
    button_nazad_record->setFont(font);
    button_nazad_record->setGeometry(view->width()/2-view->width()/8,view->height()/8*7,view->width()/3.5,view->height()/13);
    connect(button_nazad_record, SIGNAL(clicked()), this, SLOT(closerecord()));
    button_nazad_record->hide();
    scene->addWidget(button_nazad_record);


                                /* animation number */

    QPixmap pixmap7(":/new/prefix1/7.png");
    pixmap7 = pixmap7.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    pixmap* mypix7= new pixmap();
    mypix7->setPixmap(pixmap7);
    mypix7->setPos(10+rand()%view->width()/6,view->height()/4+rand()%2*view->height()/15);
    connect(mypix7,SIGNAL(_7()),this,SLOT(animatoin()));
    scene->addItem(mypix7);
    vec.push_back(mypix7);

    QPixmap pixmap1(":/new/prefix1/1.png");
    pixmap1 = pixmap1.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    pixmap* mypix1= new pixmap();
    mypix1->setPixmap(pixmap1);
    mypix1->setPos(10+rand()%view->width()/6,view->height()/4*2+rand()%2*view->height()/15);
    connect(mypix1,SIGNAL(_7()),this,SLOT(animatoin()));
    scene->addItem(mypix1);
    vec.push_back(mypix1);

    QPixmap pixmap2(":/new/prefix1/2.png");
    pixmap2 = pixmap2.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    pixmap* mypix2= new pixmap();
    mypix2->setPixmap(pixmap2);
    mypix2->setPos(10+rand()%view->width()/6,view->height()/4*3+rand()%2*view->height()/15);
    connect(mypix2,SIGNAL(_7()),this,SLOT(animatoin()));
    scene->addItem(mypix2);
    vec.push_back(mypix2);

    QPixmap pixmap4(":/new/prefix1/4.png");
    pixmap4 = pixmap4.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    pixmap* mypix4= new pixmap();
    mypix4->setPixmap(pixmap4);
    mypix4->setPos(10+rand()%view->width()/6,10+rand()%2*view->height()/15);
    connect(mypix4,SIGNAL(_7()),this,SLOT(animatoin()));
    scene->addItem(mypix4);
    vec.push_back(mypix4);

    QPixmap pixmap5(":/new/prefix1/5.png");
    pixmap5 = pixmap5.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    pixmap* mypix5= new pixmap();
    mypix5->setPixmap(pixmap5);
    mypix5->setPos(view->width()/6*5+rand()%view->width()/12,view->height()/4+rand()%2*view->height()/15);
    connect(mypix5,SIGNAL(_7()),this,SLOT(animatoin()));
    scene->addItem(mypix5);
    vec.push_back(mypix5);

    QPixmap pixmap6(":/new/prefix1/6.png");
    pixmap6 = pixmap6.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    pixmap* mypix6= new pixmap();
    mypix6->setPixmap(pixmap6);
    mypix6->setPos(view->width()/6*5+rand()%view->width()/12,view->height()/4*2+rand()%2*view->height()/15);
    connect(mypix6,SIGNAL(_7()),this,SLOT(animatoin()));
    scene->addItem(mypix6);
    vec.push_back(mypix6);

    QPixmap pixmap3(":/new/prefix1/3.png");
    pixmap3 = pixmap3.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    pixmap* mypix3= new pixmap();
    mypix3->setPixmap(pixmap3);
    mypix3->setPos(view->width()/6*5+rand()%view->width()/12,view->height()/4*3+rand()%2*view->height()/15);
    connect(mypix3,SIGNAL(_7()),this,SLOT(animatoin()));
    scene->addItem(mypix3);
    vec.push_back(mypix3);

    QPixmap pixmap8(":/new/prefix1/8.png");
    pixmap8 = pixmap8.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    pixmap* mypix8= new pixmap();
    mypix8->setPixmap(pixmap8);
    mypix8->setPos(view->width()/6*5+rand()%view->width()/12,10+rand()%2*view->height()/15);
    connect(mypix8,SIGNAL(_7()),this,SLOT(animatoin()));
    scene->addItem(mypix8);
    vec.push_back(mypix8);

    this->first_monitor();
}

MainWindow::~MainWindow()
{

}

void MainWindow::first_monitor()
{
    fon->show();
    lav->show();
    button_record->show();
    button_new_game->show();
    button_nastroiki->show();

}

void MainWindow::newgame()
{
    for (int i=0;i<8;i++) {
        vec.at(i)->hide();
    }
    button_new_game->hide();
    button_record->hide();
    button_nastroiki->hide();
    lav->hide();
    fon->hide();

    group_1->show();
    label_flag->show();
    label_dot->show();
    timsek->show();
    chetmin->setNum(global_nastriki_min);
    chetmin->show();

    int ostatokhor;
    int ostatokver;
    if((view->width()/global_nastroiki_horisontal)<=((view->height()/10*9)/global_nastroiki_vertical))
        hor_ver=view->width()/global_nastroiki_horisontal;
    else
        hor_ver=(view->height()/10*9)/global_nastroiki_vertical;

    ostatokhor= view->width()-(hor_ver*global_nastroiki_horisontal);
    ostatokver = (view->height()/10*9)-(hor_ver*global_nastroiki_vertical);

    for (int i = 0;i<global_nastroiki_vertical;i++) {
        for (int j = 0;j<global_nastroiki_horisontal;j++) {
            ElementGraphics *verx = new ElementGraphics(3,hor_ver,hor_ver);
            verx->setPos(ostatokhor/2+j*hor_ver,ostatokver/2+i*hor_ver);
            verx->xmi = i;
            verx->ymi = j;
            connect(verx,SIGNAL(signal_verx()),this,SLOT(deleteverxandflag()));
            scene->addItem(verx);
        }
    }
    scene->update();

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timetimer()));
    timer->start(1000);

}

void MainWindow::deleteverxandflag()
{
    if(!flagdot){
            if(convert_massiv){

                srand(time(nullptr));

                ElementGraphics *l = (ElementGraphics*) sender();
                game_massiv = new int* [global_nastroiki_vertical];
                for(int i = 0;i<global_nastroiki_vertical;i++)
                    game_massiv[i] = new int [global_nastroiki_horisontal];

                for (int i = 0;i<global_nastroiki_vertical;i++) {
                    for (int j = 0;j<global_nastroiki_horisontal;j++) {
                        game_massiv[i][j] = 0;
                    }
                }

                QList<QPoint> list;
                for (int i = 0;i<global_nastroiki_vertical;i++) {
                    for (int j = 0;j<global_nastroiki_horisontal;j++) {
                        if((l->xmi==i)&&(l->ymi==j))
                            continue;
                        if((i==l->xmi-1)&&(j==l->ymi-1))
                            continue;
                        if((i==l->xmi-1)&&(j==l->ymi))
                            continue;
                        if((i==l->xmi-1)&&(j==l->ymi+1))
                            continue;
                        if((i==l->xmi)&&(j==l->ymi-1))
                            continue;
                        if((i==l->xmi)&&(j==l->ymi+1))
                            continue;
                        if((i==l->xmi+1)&&(j==l->ymi-1))
                            continue;
                        if((i==l->xmi+1)&&(j==l->ymi))
                            continue;
                        if((i==l->xmi+1)&&(j==l->ymi+1))
                            continue;

                        QPoint point;
                        point.setX(i);
                        point.setY(j);
                        list<<point;
                    }
                }

                for (int i=0;i<global_nastriki_min;i++) {
                    int random = rand()%list.size();
                    QPoint pon = list.takeAt(random);
                    game_massiv [pon.x()][pon.y()] = 100;
                }

                for (int i = 0;i<global_nastroiki_vertical;i++) {
                    for (int j = 0;j<global_nastroiki_horisontal;j++) {
                        if (game_massiv[i][j]==0){
                            if((i==0)&&(j==0)){
                                int chet = 0;
                                if(game_massiv[i][j+1]==100)
                                    chet++;
                                if(game_massiv[i+1][j+1]==100)
                                    chet++;
                                if(game_massiv[i+1][j]==100)
                                    chet++;
                                game_massiv[i][j]=chet;
                            }
                            else if((i==global_nastroiki_vertical-1)&&(j==0)){
                                int chet = 0;
                                if(game_massiv[i][j+1]==100)
                                    chet++;
                                if(game_massiv[i-1][j+1]==100)
                                    chet++;
                                if(game_massiv[i-1][j]==100)
                                    chet++;
                                game_massiv[i][j]=chet;
                            }
                            else if((i==global_nastroiki_vertical-1)&&(j==global_nastroiki_horisontal-1)){
                                int chet = 0;
                                if(game_massiv[i][j-1]==100)
                                    chet++;
                                if(game_massiv[i-1][j-1]==100)
                                    chet++;
                                if(game_massiv[i-1][j]==100)
                                    chet++;
                                game_massiv[i][j]=chet;
                            }
                            else if((i==0)&&(j==global_nastroiki_horisontal-1)){
                                int chet = 0;
                                if(game_massiv[i][j-1]==100)
                                    chet++;
                                if(game_massiv[i+1][j-1]==100)
                                    chet++;
                                if(game_massiv[i+1][j]==100)
                                    chet++;
                                game_massiv[i][j]=chet;
                            }
                            else if(i==0){
                                int chet = 0;
                                if(game_massiv[i][j-1]==100)
                                    chet++;
                                if(game_massiv[i+1][j-1]==100)
                                    chet++;
                                if(game_massiv[i+1][j+1]==100)
                                    chet++;
                                if(game_massiv[i+1][j]==100)
                                    chet++;
                                if(game_massiv[i][j+1]==100)
                                    chet++;
                                game_massiv[i][j]=chet;
                            }
                            else if(i==global_nastroiki_vertical-1){
                                int chet = 0;
                                if(game_massiv[i][j-1]==100)
                                    chet++;
                                if(game_massiv[i-1][j-1]==100)
                                    chet++;
                                if(game_massiv[i-1][j+1]==100)
                                    chet++;
                                if(game_massiv[i-1][j]==100)
                                    chet++;
                                if(game_massiv[i][j+1]==100)
                                    chet++;
                                game_massiv[i][j]=chet;
                            }
                            else if(j==0){
                                int chet = 0;
                                if(game_massiv[i-1][j]==100)
                                    chet++;
                                if(game_massiv[i-1][j+1]==100)
                                    chet++;
                                if(game_massiv[i][j+1]==100)
                                    chet++;
                                if(game_massiv[i+1][j]==100)
                                    chet++;
                                if(game_massiv[i+1][j+1]==100)
                                    chet++;
                                game_massiv[i][j]=chet;
                            }
                            else if(j==global_nastroiki_horisontal-1){
                                int chet = 0;
                                if(game_massiv[i-1][j]==100)
                                    chet++;
                                if(game_massiv[i-1][j-1]==100)
                                    chet++;
                                if(game_massiv[i][j-1]==100)
                                    chet++;
                                if(game_massiv[i+1][j]==100)
                                    chet++;
                                if(game_massiv[i+1][j-1]==100)
                                    chet++;
                                game_massiv[i][j]=chet;
                            }
                            else {
                                int chet = 0;
                                if(game_massiv[i-1][j-1]==100)
                                    chet++;
                                if(game_massiv[i-1][j]==100)
                                    chet++;
                                if(game_massiv[i-1][j+1]==100)
                                    chet++;
                                if(game_massiv[i][j-1]==100)
                                    chet++;
                                if(game_massiv[i][j+1]==100)
                                    chet++;
                                if(game_massiv[i+1][j-1]==100)
                                    chet++;
                                if(game_massiv[i+1][j]==100)
                                    chet++;
                                if(game_massiv[i+1][j+1]==100)
                                    chet++;
                                game_massiv[i][j]=chet;
                            }
                        }

                    }
                }
                convert_massiv=false;
            }

        ElementGraphics *l = (ElementGraphics*) sender();

        ElementGraphics *niz = new ElementGraphics(5,hor_ver,hor_ver);
        niz->setPos(l->pos());
        scene->addItem(niz);

        if(game_massiv[l->xmi][l->ymi]==100){
            timer->stop();
            QPixmap map(":/new/prefix1/133.png");
            map = map.scaled(hor_ver/1.2,hor_ver/1.2,Qt::KeepAspectRatio);
            QGraphicsPixmapItem *it_map1 = new QGraphicsPixmapItem();
            it_map1->setPixmap(map);
            it_map1->setPos(l->pos()+QPointF(hor_ver/7-1,hor_ver/7));
            scene->addItem(it_map1);           
            this->lose();
            return;
        }

        if(!((game_massiv[l->xmi][l->ymi]==0)&&(global_nuli==false))){
            QString stry;
            stry.setNum(game_massiv[l->xmi][l->ymi]);
            QPixmap map(":/new/prefix1/"+stry+".png");
            map = map.scaled(hor_ver/1.5,hor_ver/1.5,Qt::KeepAspectRatio);
            QGraphicsPixmapItem *it_map = new QGraphicsPixmapItem();
            it_map->setPixmap(map);
            it_map->setPos(l->pos()+QPointF(hor_ver/6+1,hor_ver/6));
            scene->addItem(it_map);
        }

        if(game_over==((global_nastroiki_vertical*global_nastroiki_horisontal)-global_nastriki_min)){
            timer->stop();
            this->win();
            return;
        }
        else
            game_over++;

        delete l;
        scene->update();
    }
    else{
        ElementGraphics *ly = (ElementGraphics*) sender();
        Mylabel *myflag = new Mylabel();
        QPixmap map(":/new/prefix1/f.png");
        map = map.scaled(hor_ver/1.5,hor_ver/1.5,Qt::KeepAspectRatio);
        myflag->setPixmap(map);
        myflag->setAttribute(Qt::WA_NoSystemBackground);
        QString sr;
        sr.setNum(hor_ver/5);
        myflag->setStyleSheet("QLabel {"
                              "padding-left:"+sr+"px;"
                              "}");
        myflag->setGeometry(ly->x(),ly->y(),hor_ver,hor_ver);
        connect(myflag,SIGNAL(nastr_m()),this,SLOT(deleteflag()));

        QString str = chetmin->text();
        int convert_labelmin = str.toInt();
        chetmin->setNum(--convert_labelmin);
        scene->addWidget(myflag);
    }
}

void MainWindow::deleteflag()
{
    if(flagdot){
        Mylabel *law = (Mylabel*) sender();
        QString str = chetmin->text();
        int convert_labelmin = str.toInt();
        chetmin->setNum(++convert_labelmin);
        law->deleteLater();
    }
}

void MainWindow::pause()
{
    timer->stop();
    timsek->setText("PAUSE");

    QString timstr;
    timstr.setNum(view->height()/20);
    QFont font;
    font.setPixelSize(view->height()/25);
    timsek->setFont(font);
//    timsek->setStyleSheet("QLabel {"
//                           "background-color: rgb(197,234,255);"
//                           "font-family: \"Times New Roman\";"
//                           "font-size: "+timstr+"px;"
//                           "font-style: italic;"
//                            "}");

    Mylabel *endPause = new Mylabel();
    endPause->setStyleSheet("QLabel {"
                              "background-color: rgb(0,0,0);"
                               "}");
    endPause->setGeometry(0,0,view->width(),view->height());
    connect(endPause,SIGNAL(nastr_m()),this,SLOT(endpause()));
    scene->addWidget(endPause);

    QPropertyAnimation *animationlabel = new QPropertyAnimation();
    animationlabel->setTargetObject(endPause);
    animationlabel->setPropertyName("windowOpacity");//rotaate scale
    animationlabel->setDuration(200);
    animationlabel->setStartValue(0.001);
    animationlabel->setEndValue(0.5);
    animationlabel->start();

}

void MainWindow::endpause()
{

    Mylabel * lapause = (Mylabel*) sender();
    QPropertyAnimation *animationlabel = new QPropertyAnimation();
    animationlabel->setTargetObject(lapause);
    animationlabel->setPropertyName("windowOpacity");//rotaate scale
    animationlabel->setDuration(200);
    animationlabel->setStartValue(0.5);
    animationlabel->setEndValue(0.001);
    animationlabel->start();
    connect(animationlabel,SIGNAL(finished()),lapause,SLOT(deleteLater()));

    timer->start();
    timsek->setNum(vremya_resord);
    QString timstr;
    timstr.setNum(view->height()/15);
    QFont font;
    font.setPixelSize(view->height()/15);
    timsek->setFont(font);
//    timsek->setStyleSheet("QLabel {"
//                           "background-color: rgb(197,234,255);"
//                           "font-family: \"Times New Roman\";"
//                           "font-size: "+timstr+"px;"
//                           "font-style: italic;"
//                            "}");
 //   timsek->setGeometry((view->width()/2-(view->height()/13)-10)/4-25,(view->height()/10*9)+(view->height()/10/8)+5,(view->width()/2-(view->height()/13)-10)/4*3,view->height()/13);

}

void MainWindow::win()
{
    QPixmap fonend(view->width(),view->height());
    QPainter *paint = new QPainter(&fonend);
    QPolygon pol;
    pol<<QPoint(0,0)<<QPoint(view->width(),0)<<QPoint(view->width(),view->height())<<QPoint(0,view->height());
    paint->setBrush(QColor(0,0,0));
    paint->setPen(QPen(Qt::black,6,Qt::SolidLine));
    paint->drawPolygon(pol);
    delete paint;

    pixmap* fonendend= new pixmap();
    fonendend->setPixmap(fonend);
    fonendend->setPos(0,0);
    scene->addItem(fonendend);

    QPushButton *button_nazadend = new QPushButton();
    button_nazadend->setText("Back");
    button_nazadend->setAttribute(Qt::WA_NoSystemBackground);
    button_nazadend->setStyleSheet("QPushButton {"
                                     "border: 2px solid #000000;"
                                     "background-color: rgb(153, 217, 234);"
                                     "border-radius: 35px;"
                                      "}"
                                    "QPushButton:pressed {"
                                     "border: 2px  solid #000000; "
                                     "background-color: rgb(232, 246, 255); "
                                      "}");
    QFont font = button_nazadend->font();
    font.setPixelSize(30);
    button_nazadend->setFont(font);
    button_nazadend->setGeometry(view->width()/2-view->width()/8,view->height()/8*5,view->width()/3.5,view->height()/13);
    connect(button_nazadend,SIGNAL(clicked()),this,SLOT(endgame()));
    scene->addWidget(button_nazadend);

    QPixmap lose(":/new/prefix1/w.png");
    lose = lose.scaled(view->width()/1.5,view->height()/4,Qt::KeepAspectRatio);

    pixmap* fonendendlose= new pixmap();
    fonendendlose->setPixmap(lose);
    fonendendlose->setPos(view->width()/4.5,view->height()/8*2);//4
    scene->addItem(fonendendlose);

    QParallelAnimationGroup *groupend = new QParallelAnimationGroup();
    QPropertyAnimation *animationendlose = new QPropertyAnimation();
    animationendlose->setTargetObject(fonendendlose);
    animationendlose->setPropertyName("opacity");//rotaate scale
    animationendlose->setDuration(1500);
    animationendlose->setStartValue(0);
    animationendlose->setEndValue(1);
    QPropertyAnimation *animationendbutton = new QPropertyAnimation();
    animationendbutton->setTargetObject(button_nazadend);
    animationendbutton->setPropertyName("windowOpacity");//rotaate scale
    animationendbutton->setDuration(1500);
    animationendbutton->setStartValue(0);
    animationendbutton->setEndValue(1);
    QPropertyAnimation *animationendfon = new QPropertyAnimation();
    animationendfon->setTargetObject(fonendend);
    animationendfon->setPropertyName("opacity");//rotaate scale
    animationendfon->setDuration(1500);
    animationendfon->setStartValue(0.001);
    animationendfon->setEndValue(0.7);

    groupend->addAnimation(animationendfon);
    groupend->addAnimation(animationendbutton);
    groupend->addAnimation(animationendlose);

    groupend->start();

    QSqlQuery query;  //(QSqlDatabase::database("connectionName"));
    query.exec("UPDATE Records_AND_Settings SET win=win+1");

    int sce = 0;
    int mi = 0;
    QSqlQuery queryone;
    queryone.exec("SELECT best_in_time_sec, best_on_mines_mines FROM Records_AND_Settings");
    while (queryone.next()){
        sce = queryone.value(0).toInt();
        mi = queryone.value(1).toInt();
    }
    if (sce>=vremya_resord){
        QSqlQuery query1;
        QString str;
        str.setNum(vremya_resord);
        query1.exec("UPDATE Records_AND_Settings SET best_in_time_sec="+str);
        str.setNum(global_nastriki_min);
        query1.exec("UPDATE Records_AND_Settings SET best_in_time_mines="+str);
        str.setNum(global_nastroiki_horisontal);
        query1.exec("UPDATE Records_AND_Settings SET best_in_time_hor="+str);
        str.setNum(global_nastroiki_vertical);
        query1.exec("UPDATE Records_AND_Settings SET best_in_time_ver="+str);
    }
    if(mi<=global_nastriki_min){
        QSqlQuery query2;
        QString str;
        str.setNum(vremya_resord);
        query2.exec("UPDATE Records_AND_Settings SET best_on_mines_sec="+str);
        str.setNum(global_nastriki_min);
        query2.exec("UPDATE Records_AND_Settings SET best_on_mines_mines="+str);
        str.setNum(global_nastroiki_horisontal);
        query2.exec("UPDATE Records_AND_Settings SET best_on_mines_hor="+str);
        str.setNum(global_nastroiki_vertical);
        query2.exec("UPDATE Records_AND_Settings SET best_on_mines_ver="+str);
    }
}

void MainWindow::lose()
{
    QPixmap fonend(view->width(),view->height());
    QPainter *paint = new QPainter(&fonend);
    QPolygon pol;
    pol<<QPoint(0,0)<<QPoint(view->width(),0)<<QPoint(view->width(),view->height())<<QPoint(0,view->height());
    paint->setBrush(QColor(0,0,0));
    paint->setPen(QPen(Qt::black,6,Qt::SolidLine));
    paint->drawPolygon(pol);
    delete paint;

    pixmap* fonendend= new pixmap();
    fonendend->setPixmap(fonend);
    fonendend->setPos(0,0);
    scene->addItem(fonendend);

    QPushButton *button_nazadend = new QPushButton();
    button_nazadend->setText("Back");
    button_nazadend->setAttribute(Qt::WA_NoSystemBackground);
    button_nazadend->setStyleSheet("QPushButton {"
                                     "border: 2px solid #000000;"
                                     "background-color: rgb(153, 217, 234);"
                                     "border-radius: 35px;"
                                      "}"
                                    "QPushButton:pressed {"
                                     "border: 2px  solid #000000; "
                                     "background-color: rgb(232, 246, 255); "
                                      "}");
    QFont font = button_nazadend->font();
    font.setPixelSize(30);
    button_nazadend->setFont(font);
    button_nazadend->setGeometry(view->width()/2-view->width()/8,view->height()/8*5,view->width()/3.5,view->height()/13);
    connect(button_nazadend,SIGNAL(clicked()),this,SLOT(endgame()));
    scene->addWidget(button_nazadend);

    QPixmap lose(":/new/prefix1/l.png");
    lose = lose.scaled(view->width()/1.5,view->height()/4,Qt::KeepAspectRatio);

    pixmap* fonendendlose= new pixmap();
    fonendendlose->setPixmap(lose);
    fonendendlose->setPos(view->width()/6,view->height()/8*2);//4
    scene->addItem(fonendendlose);

    QParallelAnimationGroup *groupend = new QParallelAnimationGroup();
    QPropertyAnimation *animationendlose = new QPropertyAnimation();
    animationendlose->setTargetObject(fonendendlose);
    animationendlose->setPropertyName("opacity");//rotaate scale
    animationendlose->setDuration(1500);
    animationendlose->setStartValue(0);
    animationendlose->setEndValue(1);
    QPropertyAnimation *animationendbutton = new QPropertyAnimation();
    animationendbutton->setTargetObject(button_nazadend);
    animationendbutton->setPropertyName("windowOpacity");//rotaate scale
    animationendbutton->setDuration(1500);
    animationendbutton->setStartValue(0);
    animationendbutton->setEndValue(1);
    QPropertyAnimation *animationendfon = new QPropertyAnimation();
    animationendfon->setTargetObject(fonendend);
    animationendfon->setPropertyName("opacity");//rotaate scale
    animationendfon->setDuration(1500);
    animationendfon->setStartValue(0.001);
    animationendfon->setEndValue(0.7);

    groupend->addAnimation(animationendfon);
    groupend->addAnimation(animationendbutton);
    groupend->addAnimation(animationendlose);

    groupend->start();

    QSqlQuery query;    //(QSqlDatabase::database("connectionName"));
    query.exec("UPDATE Records_AND_Settings SET lose=lose+1");

}

void MainWindow::endgame()
{
    group_1->hide();  //группа есть доп айтем

    foreach(QGraphicsItem *item, scene->items()){
        if(item->isWidget()){
            item->hide();
        }
        else {
            if(item->isVisible()){
               delete item;
            }
        }
    }

    for (int i = 0;i<global_nastroiki_vertical;i++) {
        delete [] game_massiv[i];
    }
    delete [] game_massiv;
    flagdot = false;
    convert_massiv = true;
    game_over = 1;
    vremya_resord = 1;
    timsek->setNum(1);
    for (int i=0;i<8;i++) {
        vec.at(i)->show();
    }

    this->first_monitor();
}

void MainWindow::timetimer()
{
    vremya_resord++;
    if(vremya_resord<1000)
        timsek->setNum(vremya_resord);
}



void MainWindow::flaginverse()
{   
    label_flag->setStyleSheet("QPushButton {"
                         "border: 3px solid #000000;"
                         "background-color: rgb(0,220,220);"
                         "border-radius: 15px;"
                          "}");
    label_dot->setStyleSheet("QPushButton  {"
                         "border: 3px solid #000000;"
                         "background-color: rgb(197,234,255);"
                         "padding-left: 2px;"
                         "border-radius: 15px;"
                          "}");
    flagdot=true;
}

void MainWindow::dotinverse()
{
    label_dot->setStyleSheet("QPushButton {"
                         "border: 3px solid #000000;"
                         "background-color: rgb(0,220,220);"
                         "padding-left: 2px;"
                         "border-radius: 15px;"
                          "}");
    label_flag->setStyleSheet("QPushButton  {"
                         "border: 3px solid #000000;"
                         "background-color: rgb(197,234,255);"
                         "border-radius: 15px;"
                              "}");
    flagdot=false;
}

void MainWindow::animatoin()
{
    srand(time(nullptr));
    pixmap *l = (pixmap*) sender();
    l->setEnabled(false);

    QParallelAnimationGroup *group = new QParallelAnimationGroup();
    QPropertyAnimation *animation = new QPropertyAnimation();
    animation->setTargetObject(l);
    animation->setPropertyName("pos");//rotaate scale
    animation->setDuration(1000);
    QPointF pas = l->pos();
    animation->setStartValue(pas);
    animation->setKeyValueAt(0.5f,QPoint(rand()%view->width(),rand()%view->height()));
    animation->setEndValue(pas);

    QPropertyAnimation *animation2 = new QPropertyAnimation();
    animation2->setTargetObject(l);
    animation2->setPropertyName("scale");//rotation scale
    animation2->setDuration(1000);
    animation2->setStartValue(1);
    animation2->setKeyValueAt(0.5f,0.5+rand()%2);
    animation2->setEndValue(1);

    QPropertyAnimation *animation1 = new QPropertyAnimation();
    animation1->setTargetObject(l);
    animation1->setPropertyName("rotation");//rotation scale
    animation1->setDuration(1000);
    animation1->setStartValue(0);
    animation1->setKeyValueAt(0.5f,-rand()%361);
    animation1->setEndValue(360);

    group->addAnimation(animation);
    group->addAnimation(animation1);
    group->addAnimation(animation2);

   // animation->setEasingCurve(QEasingCurve::Linear);
    group->start();

    connect(group,SIGNAL(finished()),this,SLOT(statamimation()));
}

void MainWindow::statamimation()
{
    for (int i = 0;i<8;i++) {
        pixmap *p = vec.at(i);
       p->setEnabled(true);
    }

}

void MainWindow::exit_game()
{
    QPixmap map(":/new/prefix1/133.png");
    map = map.scaled(view->width()/2.5,view->width()/2.5,Qt::KeepAspectRatio);
    pixmap *n= new pixmap();
    n->setPixmap(map);
    n->setPos(view->width()/3,view->height()/10);
    scene->addItem(n);

    QParallelAnimationGroup *group = new QParallelAnimationGroup();
    QPropertyAnimation * animation2 = new QPropertyAnimation();
    animation2->setTargetObject(n);
    animation2->setPropertyName("scale");//rotation scale
    animation2->setDuration(500);
    animation2->setStartValue(1);
    animation2->setEndValue(7);

    QPropertyAnimation * animation23 = new QPropertyAnimation();
    animation23->setTargetObject(n);
    animation23->setPropertyName("pos");//rotation scale
    animation23->setDuration(500);
    animation23->setStartValue(n->pos());
    animation23->setEndValue(QPointF(view->width()/3-(view->width()/3*3),view->height()/10-(view->height()/10*3)));

    group->addAnimation(animation2);
    group->addAnimation(animation23);
    group->start();
    connect(group,SIGNAL(finished()),this,SLOT(EG()));

}

void MainWindow::EG()
{
     QApplication::quit();
}

void MainWindow::nastroiki()
{
    button_new_game->hide();
    button_record->hide();
    button_nastroiki->hide();

    button_nazad->show();
    barH->show();
    barV->show();
    label_color->show();
    label_h->show();
    label_v->show();
    labelD->show();
    labelE->show();
    labelS->show();
    label_nyli->show();
    label_mines->show();
    chek_box->show();
    pixcolorscene->show();
    pixcolorbackscene->show();
    item1->show();
}

void MainWindow::globD()
{
    if(global_nastriki_min%100>=90)
        global_nastriki_min =global_nastriki_min-90;
    else
        global_nastriki_min = global_nastriki_min+10;

    if(global_nastriki_min>global_nastroiki_vertical*global_nastroiki_horisontal-10){
        global_nastriki_min = global_nastriki_min-((global_nastriki_min%100)/10)*10;
    }

    QString str;
    str.setNum((global_nastriki_min%100)/10);
    QPixmap pixmapd (":/new/prefix1/"+str+".png");
    pixmapd = pixmapd.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    labelD->setPixmap(pixmapd);
}

void MainWindow::globE()
{
    if(global_nastriki_min%10==9)
        global_nastriki_min = global_nastriki_min-9;
    else
        global_nastriki_min = global_nastriki_min+1;

    if(global_nastriki_min>global_nastroiki_vertical*global_nastroiki_horisontal-10){
        global_nastriki_min = global_nastriki_min-(global_nastriki_min%10);
    }


    QString str2;
    str2.setNum(global_nastriki_min%10);
    QPixmap pixmape (":/new/prefix1/"+str2+".png");
    pixmape = pixmape.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    labelE->setPixmap(pixmape);
}

void MainWindow::globS()
{
    if(global_nastriki_min>=900)
        global_nastriki_min =global_nastriki_min-900;
    else
        global_nastriki_min = global_nastriki_min+100;

    if(global_nastriki_min>global_nastroiki_vertical*global_nastroiki_horisontal-10){
        global_nastriki_min = global_nastriki_min-(global_nastriki_min/100)*100;
    }

    QString str;
    str.setNum(global_nastriki_min/100);
    QPixmap pixmapd (":/new/prefix1/"+str+".png");
    pixmapd = pixmapd.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
    labelS->setPixmap(pixmapd);
}

void MainWindow::globChekbox()
{
    global_nuli = !global_nuli;
}

void MainWindow::globHorizontal(int value)
{
    global_nastroiki_horisontal = value;
    if(global_nastroiki_horisontal*global_nastroiki_vertical-9<global_nastriki_min){
        global_nastriki_min = global_nastroiki_horisontal*global_nastroiki_vertical-10;

        QString str;
        str.setNum(global_nastriki_min/100);
        QPixmap pixmapS (":/new/prefix1/"+str+".png");
        pixmapS = pixmapS.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
        labelS->setPixmap(pixmapS);

        QString str2;
        str2.setNum((global_nastriki_min%100)/10);
        QPixmap pixmapd (":/new/prefix1/"+str2+".png");
        pixmapd = pixmapd.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
        labelD->setPixmap(pixmapd);

        QString str3;
        str3.setNum(global_nastriki_min%10);
        QPixmap pixmape (":/new/prefix1/"+str3+".png");
        pixmape = pixmape.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
        labelE->setPixmap(pixmape);
    }
}

void MainWindow::globVertical(int value)
{
    global_nastroiki_vertical = value;
    if(global_nastroiki_horisontal*global_nastroiki_vertical-9<global_nastriki_min){
        global_nastriki_min = global_nastroiki_horisontal*global_nastroiki_vertical-10;

        QString str;
        str.setNum(global_nastriki_min/100);
        QPixmap pixmapS (":/new/prefix1/"+str+".png");
        pixmapS = pixmapS.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
        labelS->setPixmap(pixmapS);

        QString str2;
        str2.setNum((global_nastriki_min%100)/10);
        QPixmap pixmapd (":/new/prefix1/"+str2+".png");
        pixmapd = pixmapd.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
        labelD->setPixmap(pixmapd);

        QString str3;
        str3.setNum(global_nastriki_min%10);
        QPixmap pixmape (":/new/prefix1/"+str3+".png");
        pixmape = pixmape.scaled(view->height()/15,view->height()/15,Qt::KeepAspectRatio);
        labelE->setPixmap(pixmape);
    }
}

void MainWindow::color()
{
    QPixmap pixcolor(view->height()/13,view->height()/13);
    QPainter *paint = new QPainter(&pixcolor);
    QPolygon pol;
    pol<<QPoint(0,0)<<QPoint(view->height()/13,0)<<QPoint(view->height()/13,view->height()/13)<<QPoint(0,view->height()/13);
    if(globalColor==0){
        paint->setBrush(QColor(255,255,255));
        globalColor++;
    }
    else if(globalColor==1){
        paint->setBrush(QColor(150,150,150));
        globalColor++;
    }
    else if(globalColor==2){
        paint->setBrush(QColor(38,190,255));
        globalColor++;
    }
    else if(globalColor==3){
        paint->setBrush(QColor(63,72,255));
        globalColor++;
    }
    else if(globalColor==4){
        paint->setBrush(QColor(250,250,210));
        globalColor++;
    }
    else if(globalColor==5){
        paint->setBrush(QColor(177,254,189));
        globalColor++;
    }
    else if(globalColor==6){
        paint->setBrush(QColor(255,123,123));
        globalColor++;
    }
    else if(globalColor==7){
        paint->setBrush(QColor(202,142,215));
        globalColor++;
    }
    else if(globalColor==8){
        paint->setBrush(QColor(255,169,83));
        globalColor++;
    }
    else if(globalColor==9){
        paint->setBrush(QColor(0,0,0));
        globalColor = 0;
    }
    paint->setPen(QPen(Qt::black,6,Qt::SolidLine));
    paint->drawPolygon(pol);
    delete paint;

    pixmap *a = (pixmap*) sender();
    a->setPixmap(pixcolor);
}

void MainWindow::colorback()
{
    QPixmap pixcolorback(view->height()/13,view->height()/13);
    QPainter *paint2 = new QPainter(&pixcolorback);
    QPolygon pol2;
    pol2<<QPoint(0,0)<<QPoint(view->height()/13,0)<<QPoint(view->height()/13,view->height()/13)<<QPoint(0,view->height()/13);
    if(globalColorBack==0){
        paint2->setBrush(QColor(255,255,255));
        globalColorBack++;
    }
    else if(globalColorBack==1){
        paint2->setBrush(QColor(150,150,150));
        globalColorBack++;
    }
    else if(globalColorBack==2){
        paint2->setBrush(QColor(38,190,255));
        globalColorBack++;
    }
    else if(globalColorBack==3){
        paint2->setBrush(QColor(63,72,255));
        globalColorBack++;
    }
    else if(globalColorBack==4){
        paint2->setBrush(QColor(250,250,210));
        globalColorBack++;
    }
    else if(globalColorBack==5){
        paint2->setBrush(QColor(177,254,189));
        globalColorBack++;
    }
    else if(globalColorBack==6){
        paint2->setBrush(QColor(255,123,123));
        globalColorBack++;
    }
    else if(globalColorBack==7){
        paint2->setBrush(QColor(202,142,215));
        globalColorBack++;
    }
    else if(globalColorBack==8){
        paint2->setBrush(QColor(255,169,83));
        globalColorBack++;
    }
    else if(globalColorBack==9){
        paint2->setBrush(QColor(0,0,0));
        globalColorBack = 0;
    }
    paint2->setPen(QPen(Qt::black,6,Qt::SolidLine));
    paint2->drawPolygon(pol2);
    delete paint2;

    pixmap *a = (pixmap*) sender();
    a->setPixmap(pixcolorback);
}

void MainWindow::back()
{
    button_nazad->hide();
    barH->hide();
    barV->hide();
    label_color->hide();
    label_h->hide();
    label_v->hide();
    labelD->hide();
    labelE->hide();
    labelS->hide();
    label_nyli->hide();
    label_mines->hide();
    chek_box->hide();
    pixcolorscene->hide();
    pixcolorbackscene->hide();
    item1->hide();

    this->first_monitor();

    // db.open();
    QSqlQuery query;  //(QSqlDatabase::database("connectionName"));
    QString str;
    str.setNum(global_nastriki_min);
    query.exec("UPDATE Records_AND_Settings SET global_min="+str);
    str.setNum(global_nuli);
    query.exec("UPDATE Records_AND_Settings SET global_zero="+str);
    str.setNum(global_nastroiki_horisontal);
    query.exec("UPDATE Records_AND_Settings SET global_hor="+str);
    str.setNum(global_nastroiki_vertical);
    query.exec("UPDATE Records_AND_Settings SET global_ver="+str);
    str.setNum(globalColor);
    query.exec("UPDATE Records_AND_Settings SET global_color="+str);
    str.setNum(globalColorBack);
    query.exec("UPDATE Records_AND_Settings SET global_color_back="+str);
    //db.close();
}

void MainWindow::records()
{
    button_record->hide();
    button_new_game->hide();
    button_nastroiki->hide();

    QSqlQuery query;
    query.exec("SELECT win, lose, best_in_time_mines, best_in_time_sec, best_in_time_hor, best_in_time_ver, "
               "best_on_mines_mines, best_on_mines_sec, best_on_mines_hor, best_on_mines_ver FROM Records_AND_Settings");
    while (query.next()){
        QString str = query.value(0).toString();
        winrecord->setText("WIN\n"+str);

        QString str2 = query.value(1).toString();
        loserecord->setText("LOSE\n"+str2);

        QString str3m = query.value(2).toString();
        QString str3s = query.value(3).toString();
        int s = query.value(3).toInt();
        if(s==1000000)
            str3s = "0";
        QString str3h = query.value(4).toString();
        QString str3v = query.value(5).toString();
        bestoftime->setText("BEST IN TIME\n"+str3s+"s "+str3h+"h "+str3v+"v "+str3m+"m");

        QString str4m = query.value(6).toString();
        QString str4s = query.value(7).toString();
        QString str4h = query.value(8).toString();
        QString str4v = query.value(9).toString();
        bestofmine->setText("BEST ON MINES\n"+str4s+"s "+str4h+"h "+str4v+"v "+str4m+"m");
    }

    button_nazad_record->show();
    box->show();
    rec->show();
    rec->setGeometry(view->width()/2-view->width()/7,view->height()/8*3.7-55,box->width(),40);
    yaAdmin->show();
    yaAdmin->setGeometry(view->width()/2-view->width()/7,box->y()+box->height(),box->width(),30);
}

void MainWindow::closerecord()
{
    button_nazad_record->hide();
    box->hide();
    rec->hide();
    yaAdmin->hide();

    button_record->show();
    button_new_game->show();
    button_nastroiki->show();
}

