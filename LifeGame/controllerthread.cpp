#include "controllerthread.h"

ControllerThread::ControllerThread(int startrow, int endrow, int columns, GraphicsScene *scene, QVector<QVector<Grid *>> *grids, QObject *parent)
  : QObject(parent), startrow(startrow), endrow(endrow), columns(columns), scene(scene), grids(grids)
{

}

void ControllerThread::slt_setNextState()
{
    for (int i = startrow; i < endrow + 1; i++)
    {
        for (int j = 1; j < columns + 1; j++)
        {
            int countAlive = 0;
            countAlive = (*grids)[i - 1][j - 1]->getCurState() + (*grids)[i - 1][j]->getCurState() + (*grids)[i - 1][j + 1]->getCurState()
                + (*grids)[i][j - 1]->getCurState() + (*grids)[i][j + 1]->getCurState()
                + (*grids)[i + 1][j - 1]->getCurState() + (*grids)[i + 1][j]->getCurState() + (*grids)[i + 1][j + 1]->getCurState();
            switch (countAlive) {
            case 2:
                (*grids)[i][j]->setNextState((*grids)[i][j]->getCurState());
                break;
            case 3:
                (*grids)[i][j]->setNextState(1);
                break;
            default:(*grids)[i][j]->setNextState(0);
            }
        }
    }
    emit sig_finish();
}
