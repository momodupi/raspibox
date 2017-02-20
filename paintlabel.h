#ifndef PAINTLABEL_H
#define PAINTLABEL_H

#include <QWidget>

class PaintLabel : public QWidget
{
    Q_OBJECT
public:
    explicit PaintLabel(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);

signals:

public slots:
};

#endif // PAINTLABEL_H
