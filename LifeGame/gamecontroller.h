#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include "graphicsscene.h"
#include "controllerthread.h"

Q_DECLARE_METATYPE(QVector<Grid *>)

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(GraphicsScene *scene, QObject *parent = nullptr);
    ~GameController();

private:
    QList<Grid *> selected;
    Grid *start, *end;
    GraphicsScene *scene;
    bool batchmode;
    int rows, columns, t_count, finishcount;
    QList<QThread*> subthreads;
    QVector<QVector<Grid *> > grids;

//    void setNextState();
    void setThreads();
    void clearThreads();

signals:
    void sig_update();
    void sig_setNextState();

public slots:
    void slt_advance();
    void slt_random();
    void slt_clear();
    void slt_doChange();
    void slt_select(int x, int y);
    void slt_batch(int i);
    void slt_reset(int row, int columns);
    void slt_setVector(int row, QVariant v);
    void slt_finish();
};

#endif // GAMECONTROLLER_H
