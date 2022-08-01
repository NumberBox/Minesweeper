#include "elementgraphics.h"

#include <QPolygon>
#include <QPainter>

extern int globalColor;
extern int globalColorBack;

enum nazvaniya {fon=1,panell=2,verx=3,fongame=4, niz=5};

ElementGraphics::ElementGraphics(int tupe,int horison, int wertic, QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    this->what_this = tupe;
    this->horisontal = horison;
    this->vertical = wertic;
}

ElementGraphics::~ElementGraphics()
{

}

QRectF ElementGraphics::boundingRect() const
{
    if (what_this==fon){
        return QRectF(0,0,horisontal,vertical);
    }
    if (what_this==panell){
        return QRectF(0,0,horisontal,vertical);
    }
    if (what_this==verx){
        return QRectF(0,0,horisontal,vertical);
    }
    if (what_this==fongame){
        return QRectF(0,0,horisontal,vertical);
    }
    if (what_this==niz){
        return QRectF(0,0,horisontal,vertical);
    }

}

void ElementGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if (what_this==fon){
        QPolygon pol;
        pol<<QPoint(0,0)<<QPoint(horisontal,0)<<QPoint(horisontal,vertical)<<QPoint(0,vertical);
        painter->setBrush(QColor(119,255,255));
        //painter->setPen(QPen(Qt::black,6,Qt::SolidLine));
        painter->drawPolygon(pol);
    }
    if (what_this==fongame){
        QPolygon pol;
        pol<<QPoint(0,0)<<QPoint(horisontal,0)<<QPoint(horisontal,vertical)<<QPoint(0,vertical);
        painter->setBrush(QColor(0,0,0));
        //painter->setPen(QPen(Qt::black,6,Qt::SolidLine));
        painter->drawPolygon(pol);
    }
    if (what_this==panell){
        QPolygon pol;
        pol<<QPoint(0,0)<<QPoint(horisontal,0)<<QPoint(horisontal,vertical)<<QPoint(0,vertical);
        painter->setBrush(QColor(197,234,255));
        painter->setPen(QPen(Qt::black,6,Qt::SolidLine));
        painter->drawPolygon(pol);
    }
    if (what_this==verx){
        QPolygon pol;
        pol<<QPoint(0,0)<<QPoint(horisontal,0)<<QPoint(horisontal,vertical)<<QPoint(0,vertical);
        if(globalColor==0){
            painter->setBrush(QColor(0,0,0));
        }
        else if(globalColor==1){
            painter->setBrush(QColor(255,255,255));
        }
        else if(globalColor==2){
            painter->setBrush(QColor(150,150,150));
        }
        else if(globalColor==3){
            painter->setBrush(QColor(38,190,255));
        }
        else if(globalColor==4){
            painter->setBrush(QColor(63,72,255));
        }
        else if(globalColor==5){
            painter->setBrush(QColor(250,250,210));
        }
        else if(globalColor==6){
            painter->setBrush(QColor(177,254,189));
        }
        else if(globalColor==7){
            painter->setBrush(QColor(255,123,123));
        }
        else if(globalColor==8){
            painter->setBrush(QColor(202,142,215));
        }
        else if(globalColor==9){
            painter->setBrush(QColor(255,169,83));
        }
        painter->setPen(QPen(Qt::black,6,Qt::SolidLine));
        painter->drawPolygon(pol);
    }
    if (what_this==niz){
        QPolygon pol;
        pol<<QPoint(0,0)<<QPoint(horisontal,0)<<QPoint(horisontal,vertical)<<QPoint(0,vertical);
        if(globalColorBack==0){
            painter->setBrush(QColor(0,0,0));
        }
        else if(globalColorBack==1){
            painter->setBrush(QColor(255,255,255));
        }
        else if(globalColorBack==2){
            painter->setBrush(QColor(150,150,150));
        }
        else if(globalColorBack==3){
            painter->setBrush(QColor(38,190,255));
        }
        else if(globalColorBack==4){
            painter->setBrush(QColor(63,72,255));
        }
        else if(globalColorBack==5){
            painter->setBrush(QColor(250,250,210));
        }
        else if(globalColorBack==6){
            painter->setBrush(QColor(177,254,189));
        }
        else if(globalColorBack==7){
            painter->setBrush(QColor(255,123,123));
        }
        else if(globalColorBack==8){
            painter->setBrush(QColor(202,142,215));
        }
        else if(globalColorBack==9){
            painter->setBrush(QColor(255,169,83));
        }
        painter->setPen(QPen(Qt::black,6,Qt::SolidLine));
        painter->drawPolygon(pol);
    }
        Q_UNUSED(option)
        Q_UNUSED(widget)
}

void ElementGraphics::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signal_verx();
}
