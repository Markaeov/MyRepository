#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QWidget>
#include "grid.h"

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QWidget *parent = nullptr) : QGraphicsScene(parent){}

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void sig_select(int, int);
};

#endif // GRAPHICSSCENE_H
