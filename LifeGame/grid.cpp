#include "grid.h"

bool Grid::showBorder;

Grid::Grid(int x, int y)
    :x(x), y(y)
{
    isMarked = false;
	isBatchNode = false;
    curState = nextState = false;
    showBorder = false;
}

void Grid::switchBorder()
{
    showBorder = !showBorder;
}

QRectF Grid::boundingRect() const
{
    return QRectF(0, 0, 5, 5);
}

QPainterPath Grid::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, 5, 5);
    return path;
}

void Grid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QColor fillcolor;
    if (isBatchNode)
        fillcolor = Qt::red;
    else if (isMarked)
        fillcolor = Qt::gray;
    else if(curState)
        fillcolor = Qt::black;
    else if(!curState)
        fillcolor = Qt::white;

    QPen p = painter->pen();
    if(showBorder)
        painter->setPen(Qt::black);
    else
        painter->setPen(Qt::white);
    QBrush b = painter->brush();
    painter->setBrush(fillcolor);
    painter->drawRect(QRectF(0, 0, 5, 5));
    painter->setBrush(b);
    painter->setPen(p);
}

//void Grid::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    emit sig_marked(this);
//    QGraphicsItem::mouseReleaseEvent(event);
//}

void Grid::advance(int phase)
{
    if(!phase)
        return;
    curState = nextState;
}
