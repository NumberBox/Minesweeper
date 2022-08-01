#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>


class Mylabel : public QLabel
{
     Q_OBJECT
public:
    explicit Mylabel(QWidget *parent = nullptr);

signals:
    void exit_g();
    void nastr_m();

protected:
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // MYLABEL_H
