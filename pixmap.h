#ifndef PIXMAP_H
#define PIXMAP_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QDebug>

class pixmap : public QObject, public QGraphicsPixmapItem {

    Q_OBJECT
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)


public:
    pixmap();

signals:
    void _7();

protected:
     void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PIXMAP_H
