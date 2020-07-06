#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <QFrame>
#include <QGraphicsView>
#include <QPushButton>
#include <QCheckBox>
#include "grid.h"

class GridView : public QFrame
{
    Q_OBJECT
public:
    GridView(QWidget *parent = nullptr);
    QGraphicsView *view() const;

private:
    bool paused;
    QGraphicsView *gview;
    QLineEdit *le_rows, *le_columns;
    QPushButton *btn_switch, *btn_clear, *btn_random, *btn_doChange, *btn_reset;
    QCheckBox *cb_batch, *cb_border;
    QSlider *sl_zoom;
    QSpinBox *spb_timer;

    friend class Widget;

signals:
    void sig_reset(int rows, int columns);

private slots:
    void slt_showBorder();
    void slt_changeText();
    void slt_zoom();
    void slt_reset();

public slots:
    void slt_update();
};

#endif // GRIDVIEW_H
