#include "paintlabel.h"

#include <QPainter>
#include <QPoint>
#include <QDebug>
#include <QtWidgets/qframe.h>
#include <QWidget>
#include <sys/time.h>

PaintLabel::PaintLabel(QWidget *parent) : QWidget(parent)
{

}

void PaintLabel::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);}
