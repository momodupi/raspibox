#include "clockwidget.h"

#include <QPainter>
#include <QPoint>
#include <QTime>
#include <QTimer>
#include <QGraphicsDropShadowEffect>

clockwidget::clockwidget(QWidget *parent) : QWidget(parent)
{
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);
}


void clockwidget::paintEvent(QPaintEvent *event)
{
    event = event;
    static const QPoint hourHand[4] = {
        QPoint(5, 0),
        QPoint(-5, 0),
        QPoint(-2, -49),
        QPoint(2, -49)
    };
    static const QPoint minuteHand[4] = {
        QPoint(3, 0),
        QPoint(-3, 0),
        QPoint(-1, -80),
        QPoint(1, -80)
    };

    QColor hourminuteColor("#d4d4d4");
    QColor secondColor("#00b0bf");

    int side = qMin(width(), height());

    QTime time = QTime::currentTime();

    //The QPainter class performs low-level painting on widgets and other paint devices.
    QPainter painter(this);

    //Sets the given render hint on the painter if on is true; otherwise clears the render hint
    //Renderhints are used to specify flags to QPainter that may or may not be respected by any given engine.
    painter.setRenderHint(QPainter::Antialiasing);

    //Translates the coordinate system by the given offset
    painter.translate(width()/2, height()/2);

    //Scales the coordinate system by (sx, sy).
    painter.scale(side/200.0, side/200.0);

    //Sets the painter's pen to be the given pen.
    //The pen defines how to draw lines and outlines, and it also defines the text color.
    painter.setPen(Qt::NoPen);

    //sets the painter's brush to the given brush.
    //The painter's brush defines how shapes are filled.
    painter.setBrush(hourminuteColor);

    //Saves the current painter state (pushes the state onto a stack).
    //A save() must be followed by a corresponding restore(); the end() function unwinds the stack.
    painter.save();

    //Rotates the coordinate system the given angle clockwise.
    painter.rotate(30.0*((time.hour()+time.minute()/60.0)));

    //Draws the convex polygon defined by the first pointCount points in the array points using the current pen.
    //The first point is implicitly connected to the last point, and the polygon is filled with the current brush().
    painter.drawConvexPolygon(hourHand, 4);

    //Restores the current painter state (pops a saved state off the stack).
    painter.restore();

    painter.setPen(hourminuteColor);

    //lines of hours
    for (int cnt = 0; cnt < 12; cnt++)
    {
        //Draws a line from (x1, y1) to (x2, y2) and sets the current pen position to (x2, y2).
        painter.drawLine(90, 0, 95, 0);
        painter.rotate(30.0);
    }

    //lines of minutes
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourminuteColor);
    painter.save();
    painter.rotate(6.0*(time.minute()+time.second()/60.0));
    painter.drawConvexPolygon(minuteHand, 4);
    painter.restore();
    painter.setPen(hourminuteColor);
    for (int cnt = 0; cnt < 60; cnt++)
    {
        if((cnt % 5) != 0)
        {
            painter.drawLine(93, 0, 95, 0);
        }
        painter.rotate(6.0);
    }

    painter.setPen(QPen(QColor("#d4d4d4"), 1));
    painter.setBrush(QColor("#01579b"));
    painter.drawEllipse(-15, -15, 30, 30);

    //point of second
    painter.setPen(Qt::NoPen);
    painter.setBrush(secondColor);
    painter.save();
    painter.rotate(6.0*(time.second()));
    painter.drawEllipse(5, -98, 10, 10);
    painter.restore();
    painter.setPen(hourminuteColor);
}
