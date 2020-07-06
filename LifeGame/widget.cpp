#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    gridView = new GridView(this);
    scene = new GraphicsScene(this);
    gridView->view()->setScene(scene);

    //多线程，逻辑控制在子线程完成，而界面更新必须在主线程完成
    gc = new GameController(scene); //因为scene是界面更新相关的变量，所以只能在主线程中定义声明，再通过参数将指针传递到子线程对象进行处理
    subthread = new QThread(this);
    gc->moveToThread(subthread);
    subthread->start();

    paused = false;
    timer = new QTimer(this);
    timer->setInterval(100);
    slt_switch();

    connect(gridView->btn_switch, &QPushButton::clicked, this, &Widget::slt_switch);
    connect(gridView->btn_clear, &QPushButton::clicked, gc, &GameController::slt_clear);
    connect(gridView->btn_random, &QPushButton::clicked, gc, &GameController::slt_random);
    connect(gridView->btn_doChange, &QPushButton::clicked, gc, &GameController::slt_doChange);
    connect(gridView->cb_batch, &QCheckBox::stateChanged, gc, &GameController::slt_batch);
    connect(gridView->spb_timer, QOverload<int>::of(&QSpinBox::valueChanged), this, &Widget::slt_setInterval);
    connect(gc, &GameController::sig_update, gridView, &GridView::slt_update);
    connect(timer, &QTimer::timeout, gc, &GameController::slt_advance);
    connect(gridView, &GridView::sig_reset, this, &Widget::slt_clearScene);
    connect(this, &Widget::sig_reset, gc, &GameController::slt_reset);
    connect(this, &Widget::sig_setVector, gc, &GameController::slt_setVector);

    slt_clearScene(200, 200);
    gridView->show();
    setFixedSize(gridView->size());
    timer->start();
}

void Widget::slt_clearScene(int rows, int columns)
{
    timer->blockSignals(true);
    this->rows = rows;
    this->columns = columns;
    foreach (Grid *g, del_list)
        g->deleteLater();
    del_list.clear();
    scene->clear();
    grids.clear();
    emit sig_reset(rows, columns);
    initScene();
    timer->blockSignals(paused);
}

void Widget::initScene()
{
    disconnect(scene, &GraphicsScene::sig_select, gc, &GameController::slt_select);
    grids.resize(rows + 2);
    QVariant v;
    grids[0].resize(columns + 2);
    grids[rows + 1].resize(columns + 2);
    for(int x = 0; x < columns + 2; x++)
    {
        grids[0][x] = new Grid(x, 0);
        del_list.append(grids[0][x]);
        grids[rows + 1][x] = new Grid(x, rows + 1);
        del_list.append(grids[rows + 1][x]);
    }
    v.setValue(grids[0]);
    emit sig_setVector(0, v);
    v.setValue(grids[rows + 1]);
    emit sig_setVector(rows + 1, v);

    for(int y = 1; y < rows + 1; y++)
    {
        grids[y].resize(columns + 2);
        grids[y][0] = new Grid(0, y);
        del_list.append(grids[y][0]);
        for(int x = 1; x < columns + 1; x++)
        {
            grids[y][x] = new Grid(x, y);
            grids[y][x]->setPos(x * 5.0, y * 5.0);
            scene->addItem(grids[y][x]);
        }
        grids[y][columns + 1] = new Grid(columns + 1, y);
        del_list.append(grids[y][columns + 1]);
        v.setValue(grids[y]);
        emit sig_setVector(y, v);
    }
    connect(scene, &GraphicsScene::sig_select, gc, &GameController::slt_select);
}

void Widget::slt_setInterval(int i)
{
    timer->setInterval(i);
}

void Widget::slt_switch()   //暂停与继续，注意并没有停止计时器，只是阻塞信号的发送
{
    paused = !paused;
    timer->blockSignals(paused);
}

Widget::~Widget()
{
    //结束子线程
    subthread->quit();
    subthread->wait();
    foreach(Grid *g, del_list)
        g->deleteLater();
}
