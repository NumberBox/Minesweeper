#ifndef ELEMENTGRAPHICS_H
#define ELEMENTGRAPHICS_H

#include <QObject>
#include <QGraphicsItem>

class ElementGraphics : public QObject, public QGraphicsItem
{
      Q_OBJECT
public:
    explicit ElementGraphics (int tupe, int horison, int wertic, QObject *parent = 0);
    ~ElementGraphics();

    int vertical;
    int horisontal;
    int what_this;

    int xmi;
    int ymi;

signals:
    void signal_verx();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // ELEMENTGRAPHICS_H
