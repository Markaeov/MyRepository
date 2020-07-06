#include "graphicsscene.h"

#include <QGraphicsSceneMouseEvent>

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF p = event->scenePos();
    QTransform t;
    Grid *g = static_cast<Grid*>(itemAt(p, t));
    emit sig_select(g->posX(), g->posY());
    QGraphicsScene::mousePressEvent(event);
}
