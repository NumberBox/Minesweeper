#include "mymovie.h"

enum nazvaniyagiv {mina=1};

MyMovie::MyMovie(int tupe, int horisontal, int vertical)
{
    if(tupe==mina){
        this->setFileName(":/new/prefix1/1222.gif");
        this->setScaledSize(QSize(horisontal,vertical));
        this->start();
    }
}
