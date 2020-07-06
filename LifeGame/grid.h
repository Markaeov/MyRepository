#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QtWidgets>
#include <QGraphicsItem>
#include <QColor>

class Grid : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Grid(int x, int y);
    int getCurState(){return curState;} //内联以提高效率
    void setNextState(bool state){nextState = state;}
    bool switchMark(){isMarked = !isMarked; return isMarked;}
    void setUnmarked(){isMarked = false;}
    void setBatchNode(bool state) {isBatchNode = state;}
    bool batchNode() {return isBatchNode;}
    int posX(){return x;}
    int posY(){return y;}
    static void switchBorder();
    //override重写父类的函数
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void advance(int phase) override;

private:
    int curState, nextState;   //1为生，0为死，不用bool是为了计算周围存活数时可以省去条件判断
    bool isMarked;  //是否被标记，用于手动设置状态，选中但未应用更改时显示为灰色
	bool isBatchNode; //是否是批量选择点
    static bool showBorder; //是否显示格子边界
    int x, y;   //列与行

//signals:
//    void sig_marked(Grid *);
};

#endif // GRID_H
