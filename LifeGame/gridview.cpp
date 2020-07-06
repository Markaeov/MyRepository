#include <QVBoxLayout>
#include <QHBoxLayout>
#include "gridview.h"

GridView::GridView(QWidget *parent)
    :QFrame(parent)
{
    paused = true;
    gview = new QGraphicsView(this);

    QVBoxLayout *vlayout = new QVBoxLayout();
    btn_switch = new QPushButton("start", this);
    btn_clear = new QPushButton("clear", this);
    btn_random = new QPushButton("random", this);
    btn_doChange = new QPushButton("do change", this);
    cb_batch = new QCheckBox("batch", this);
    cb_border = new QCheckBox("show border", this);
    sl_zoom = new QSlider(this);
    sl_zoom->setMinimum(1);
    sl_zoom->setMaximum(5);
    sl_zoom->setValue(1);
    sl_zoom->setTickPosition(QSlider::TicksBothSides);
    sl_zoom->setTickInterval(1);
    sl_zoom->setSingleStep(1);
    sl_zoom->setPageStep(1);
    QLabel *lb_zoom = new QLabel("zoom", this);
    QLabel *lb_interval = new QLabel("timer interval", this);
    spb_timer = new QSpinBox(this);
    spb_timer->setRange(20, 1000);
    spb_timer->setValue(100);
    QLabel *lb_rows = new QLabel("rows", this);
    le_rows = new QLineEdit("200", this);
    QLabel *lb_columns = new QLabel("columns", this);
    le_columns = new QLineEdit("200", this);
    btn_reset = new QPushButton("reset", this);

    vlayout->addWidget(btn_switch);
    vlayout->addWidget(btn_clear);
    vlayout->addWidget(btn_random);
    vlayout->addWidget(btn_doChange);
    vlayout->addWidget(cb_batch);
    vlayout->addWidget(cb_border);
    vlayout->addWidget(sl_zoom);
    vlayout->addWidget(lb_zoom);
    vlayout->addWidget(lb_interval);
    vlayout->addWidget(spb_timer);
    vlayout->addWidget(lb_rows);
    vlayout->addWidget(le_rows);
    vlayout->addWidget(lb_columns);
    vlayout->addWidget(le_columns);
    vlayout->addWidget(btn_reset);
    vlayout->addStretch();

    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->addWidget(gview);
    hlayout->addLayout(vlayout);

    connect(btn_switch, &QPushButton::clicked, this, &GridView::slt_changeText);
    connect(cb_border, &QCheckBox::stateChanged, this, &GridView::slt_showBorder);
    connect(sl_zoom, &QSlider::valueChanged, this, &GridView::slt_zoom);
    connect(btn_reset, &QPushButton::clicked, this, &GridView::slt_reset);
}

QGraphicsView *GridView::view() const
{
    return gview;
}

void GridView::slt_showBorder()
{
    Grid::switchBorder();
    slt_update();
}

void GridView::slt_changeText()
{
    paused = !paused;
    if(paused)
        btn_switch->setText("start");
    else
        btn_switch->setText("pause");
}

void GridView::slt_zoom()
{
    qreal scale = sl_zoom->value();
    QMatrix m;
    m.scale(scale, scale);
    gview->setMatrix(m);
}

void GridView::slt_reset()
{
    emit sig_reset(le_rows->text().toInt(), le_columns->text().toInt());
}

void GridView::slt_update()
{
    gview->viewport()->update();
}
