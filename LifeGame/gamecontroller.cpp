#include <QtGlobal>
#include "gamecontroller.h"

GameController::GameController(GraphicsScene *scene, QObject *parent)
    : QObject(parent), scene(scene)
{
    rows = columns = 200;
    t_count = 4;
    finishcount = 0;
    start = nullptr;
    end = nullptr;
    batchmode = false;
}

GameController::~GameController()
{
    clearThreads();
}

//void GameController::setNextState()
//{
//    //TODO
//    //计算所有格子的下一个状态，并使用grids[y][x].setNextState来设置它
//    //三个1为1  两个1不变  其他为0
////    int i, j;
////    int countAlive = 0;//统计格子周围活的
////    int countAlive_1 = 0;
////    //四个角
////    //00
////    countAlive = grids[0][1]->getCurState() + grids[1][1]->getCurState() + grids[1][0]->getCurState();
////    switch (countAlive) {
////    case 2:
////        grids[0][0]->setNextState(grids[0][0]->getCurState());
////        break;
////    case 3:
////        grids[0][0]->setNextState(1);
////        break;
////    default:grids[0][0]->setNextState(0);
////    }
////    //0 199
////    countAlive = 0;
////    countAlive = grids[0][columns - 2]->getCurState() + grids[1][columns - 2]->getCurState() + grids[1][columns - 1]->getCurState();
////    switch (countAlive) {
////    case 2:
////        grids[0][columns - 1]->setNextState(grids[0][columns - 1]->getCurState());
////        break;
////    case 3:
////        grids[0][columns - 1]->setNextState(1);
////        break;
////    default:grids[0][columns - 1]->setNextState(0);
////    }
////    //199 0
////    countAlive = 0;
////    countAlive = grids[rows - 2][0]->getCurState() + grids[rows - 1][1]->getCurState() + grids[rows - 2][1]->getCurState();
////    switch (countAlive) {
////    case 2:
////        grids[rows - 1][0]->setNextState(grids[rows - 1][0]->getCurState());
////        break;
////    case 3:
////        grids[rows - 1][0]->setNextState(1);
////        break;
////    default:grids[rows - 1][0]->setNextState(0);
////    }
////    //199 199
////    countAlive = 0;
////    countAlive = grids[rows - 1][columns - 2]->getCurState() + grids[rows - 2][columns - 1]->getCurState() + grids[rows - 2][columns - 2]->getCurState();
////    switch (countAlive) {
////    case 2:
////        grids[rows - 1][columns - 1]->setNextState(grids[rows - 1][columns - 1]->getCurState());
////        break;
////    case 3:
////        grids[rows - 1][columns - 1]->setNextState(1);
////        break;
////    default:grids[rows - 1][columns - 1]->setNextState(0);
////    }
////    //四条边
////    //上下横边
////    for (i = 1; i <= columns - 2; i++) {
////        countAlive = 0;
////        countAlive_1 = 0;
////        //上
////        countAlive = grids[0][i - 1]->getCurState() + grids[0][i + 1]->getCurState() + grids[1][i - 1]->getCurState() +
////            grids[1][i]->getCurState() + grids[1][i + 1]->getCurState();
////        switch (countAlive) {
////        case 2:
////            grids[0][i]->setNextState(grids[0][i]->getCurState());
////            break;
////        case 3:
////            grids[0][i]->setNextState(1);
////            break;
////        default:grids[0][i]->setNextState(0);
////        }
////        //下
////        countAlive_1 = grids[rows - 1][i - 1]->getCurState() + grids[rows - 1][i + 1]->getCurState() + grids[rows - 2][i - 1]->getCurState() +
////            grids[rows - 2][i]->getCurState() + grids[rows - 2][i + 1]->getCurState();
////        switch (countAlive_1) {
////        case 2:
////            grids[rows - 1][i]->setNextState(grids[rows - 1][i]->getCurState());
////            break;
////        case 3:
////            grids[rows - 1][i]->setNextState(1);
////            break;
////        default:grids[rows - 1][i]->setNextState(0);
////        }
////    }
////    //左右
////    for (i = 1; i <= rows - 2; i++) {
////        countAlive = 0;
////        countAlive_1 = 0;
////        //左
////        countAlive = grids[i - 1][0]->getCurState() + grids[i + 1][0]->getCurState() + grids[i - 1][1]->getCurState() +
////            grids[i][1]->getCurState() + grids[i + 1][1]->getCurState();
////        switch (countAlive) {
////        case 2:
////            grids[i][0]->setNextState(grids[i][0]->getCurState());
////            break;
////        case 3:
////            grids[i][0]->setNextState(1);
////            break;
////        default:grids[i][0]->setNextState(0);
////        }
////        //右
////        countAlive_1 = grids[i - 1][columns - 1]->getCurState() + grids[i + 1][columns - 1]->getCurState() + grids[i - 1][columns - 2]->getCurState() +
////            grids[i][columns - 2]->getCurState() + grids[i + 1][columns - 2]->getCurState();
////        switch (countAlive_1) {
////        case 2:
////            grids[i][columns - 1]->setNextState(grids[i][columns - 1]->getCurState());
////            break;
////        case 3:
////            grids[i][columns - 1]->setNextState(1);
////            break;
////        default:grids[i][columns - 1]->setNextState(0);
////        }
////    }

//    //内部
//    for (int i = 1; i < rows + 1; i++) {
//        for (int j = 1; j < columns + 1; j++) {
//            int countAlive = 0;
//            countAlive = grids[i - 1][j - 1]->getCurState() + grids[i - 1][j]->getCurState() + grids[i - 1][j + 1]->getCurState()
//                + grids[i][j - 1]->getCurState() + grids[i][j + 1]->getCurState()
//                + grids[i + 1][j - 1]->getCurState() + grids[i + 1][j]->getCurState() + grids[i + 1][j + 1]->getCurState();
//            switch (countAlive) {
//            case 2:
//                grids[i][j]->setNextState(grids[i][j]->getCurState());
//                break;
//            case 3:
//                grids[i][j]->setNextState(1);
//                break;
//            default:grids[i][j]->setNextState(0);
//            }
//        }
//    }
//}

void GameController::setThreads()
{
    clearThreads();
    int rowcount = rows/t_count + (rows % t_count > 0);
    for(int i = 0; i < t_count; i++)
    {
        int startrow = i * rowcount + 1;
        int endrow = (i + 1) * rowcount;
        if(endrow > rows)
            endrow = rows;
        QThread *subthread = new QThread(this);
        ControllerThread *ct = new ControllerThread(startrow, endrow, columns, scene, &grids);
        ct->moveToThread(subthread);
        subthread->start();
        subthreads.append(subthread);
        connect(this, &GameController::sig_setNextState, ct, &ControllerThread::slt_setNextState);
        connect(ct, &ControllerThread::sig_finish, this, &GameController::slt_finish);
    }
}

void GameController::clearThreads()
{
    foreach (QThread *t, subthreads) {
        t->quit();
        t->wait();
    }
}

void GameController::slt_random()   //所有格子随机
{
    for(int y = 1; y < rows + 1; y++)
    {
        for(int x = 1; x < columns + 1; x++)
        {
            bool state = qrand() % 2 ? true: false;
            grids[y][x]->setNextState(state);
        }
    }
    slt_advance();
}

void GameController::slt_clear()    //所有格子置为死
{
    for(int y = 1; y < rows + 1; y++)
    {
        for(int x = 1; x < columns + 1; x++)
        {
            grids[y][x]->setNextState(false);

        }
    }
    slt_advance();
    if(nullptr != start)
    {
        start->setBatchNode(false);
        start = nullptr;
    }
    foreach(Grid *g, selected)
    {
        g->setUnmarked();
    }
    selected.clear();
}

void GameController::slt_doChange()
{
    //TODO
    //将所有选中的格子状态置反
    foreach(Grid *g, selected)
    {
        g->setNextState(!g->getCurState());
        g->setUnmarked();
        g->advance(1);
    }
    emit sig_setNextState();
    selected.clear();
//    emit sig_update();
}

void GameController::slt_select(int x, int y)
{
	int start_x, start_y;
	int end_y, end_x;
    Grid *grid = grids[y][x];
    if(!batchmode)
    {
        if(grid->switchMark())
            selected.append(grid);
        else
            selected.removeOne(grid);
    }
	else
	{
        if(!grid->batchNode())
        {
            if(nullptr == start)
            {
                start = grid;
                grid->setBatchNode(true);
            }
            else
            {
                end = grid;
                start_x = start->posX() < end->posX() ? start->posX() : end->posX();
                end_x = start->posX() > end->posX() ? start->posX() : end->posX();
                start_y = start->posY() < end->posY() ? start->posY() : end->posY();
                end_y = start->posY() > end->posY() ? start->posY() : end->posY();
                for(int y = start_y; y <= end_y; y++)
                {
                    for(int x = start_x; x <= end_x; x++)
                    {
                        if(grids[y][x]->switchMark())
                            selected.append(grids[y][x]);
                        else
                            selected.removeOne(grids[y][x]);
                    }
                }
                start->setBatchNode(false);
                end = start = nullptr;
            }
        }
        else
        {
            start = nullptr;
            grid->setBatchNode(false);

        }
    }
    emit sig_update();
}

void GameController::slt_batch(int i)   //批量选择模式
{
    batchmode = i ? true : false;
    if(nullptr != start)
    {
        start->setBatchNode(false);
        start = nullptr;
    }
}

void GameController::slt_reset(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
    grids.clear();
    grids.resize(rows + 2);
    setThreads();
}

void GameController::slt_setVector(int row, QVariant v)
{
    grids[row].resize(columns + 2);
    grids[row] = v.value<QVector<Grid *>>();
}

void GameController::slt_finish()
{
    finishcount++;
    if(finishcount >= t_count)
    {
        finishcount = 0;
//        blockSignals(false);
    }
}


void GameController::slt_advance()  //先将所有格子设为下一状态，再重新计算下一状态，以保证每次计时结束时立刻刷新
{
    scene->advance();
    emit sig_update();
    emit sig_setNextState();
//    blockSignals(true);
//    setNextState();
}
