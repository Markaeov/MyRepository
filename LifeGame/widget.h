#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include "gridview.h"
#include "gamecontroller.h"
#include "controllerthread.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    GameController *gc;
    GridView *gridView;
    GraphicsScene *scene;
    QThread *subthread;
    QTimer *timer;
    bool paused;
    int rows, columns;
    QVector<QVector<Grid *>> grids;
    QList<Grid *> del_list;

    void initScene();

signals:
    void sig_reset(int rows, int columns);
    void sig_setVector(int row, QVariant v);

private slots:
    void slt_switch();
    void slt_setInterval(int i);
    void slt_clearScene(int rows, int columns);
};

#endif // WIDGET_H


