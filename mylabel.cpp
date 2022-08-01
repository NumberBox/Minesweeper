#include "mylabel.h"

Mylabel::Mylabel(QWidget *parent) : QLabel(parent)
{

}

void Mylabel::mousePressEvent(QMouseEvent *event)
{
    emit exit_g();
    emit nastr_m();
}

