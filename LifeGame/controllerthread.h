#ifndef CONTROLLERTHREAD_H
#define CONTROLLERTHREAD_H

#include <QObject>
#include "graphicsscene.h"

class ControllerThread : public QObject
{
    Q_OBJECT
public:
    explicit ControllerThread(int startrow, int endrow, int columns, GraphicsScene *scene, QVector<QVector<Grid *>> *grids, QObject *parent = nullptr);
    void setVector(QVector<QVector<Grid *>> *grids) {this->grids->clear(); this->grids = grids;}

private:
    int startrow, endrow, columns;
    GraphicsScene *scene;
    QVector<QVector<Grid *>> *grids;

signals:
    void sig_finish();

public slots:
    void slt_setNextState();
};

#endif // CONTROLLERTHREAD_H
