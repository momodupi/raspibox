#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>

class clockwidget : public QWidget
{
    Q_OBJECT
public:
    explicit clockwidget(QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CLOCKWIDGET_H
