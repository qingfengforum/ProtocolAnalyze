#include "qfpushbuttons.h"

#include <QMouseEvent>
#include <QDebug>
qfPushButtons::qfPushButtons(QWidget *parent) :
    QPushButton(parent)
{

}

/*****************************************************
 * reimplemented funcs (protected)
 * **************************************************/
void qfPushButtons::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MidButton) {
        midBtnPressed = true;
        m_press = event->globalPos();
        qDebug() << "middle button clicked";
    }
}
void qfPushButtons::mouseMoveEvent(QMouseEvent *event)
{
    if (midBtnPressed) {
        m_move = event->globalPos();
        this->move(this->pos() + m_move - m_press);
        m_press = m_move;
        qDebug() << "middle button move";
    }
}
void qfPushButtons::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MidButton) {
        midBtnPressed = false;
        qDebug() << "middle button release";
    }
}

