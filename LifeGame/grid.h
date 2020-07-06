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
    int getCurState(){return curState;} //���������Ч��
    void setNextState(bool state){nextState = state;}
    bool switchMark(){isMarked = !isMarked; return isMarked;}
    void setUnmarked(){isMarked = false;}
    void setBatchNode(bool state) {isBatchNode = state;}
    bool batchNode() {return isBatchNode;}
    int posX(){return x;}
    int posY(){return y;}
    static void switchBorder();
    //override��д����ĺ���
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void advance(int phase) override;

private:
    int curState, nextState;   //1Ϊ����0Ϊ��������bool��Ϊ�˼�����Χ�����ʱ����ʡȥ�����ж�
    bool isMarked;  //�Ƿ񱻱�ǣ������ֶ�����״̬��ѡ�е�δӦ�ø���ʱ��ʾΪ��ɫ
	bool isBatchNode; //�Ƿ�������ѡ���
    static bool showBorder; //�Ƿ���ʾ���ӱ߽�
    int x, y;   //������

//signals:
//    void sig_marked(Grid *);
};

#endif // GRID_H
