#ifndef QFPUSHBUTTONS_H
#define QFPUSHBUTTONS_H

#include <QWidget>
#include <QPushButton>

class qfPushButtons : public QPushButton
{
public:
    explicit qfPushButtons(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private:
    bool midBtnPressed;
    QPoint m_press;
    QPoint m_move;
};

#endif // QFPUSHBUTTONS_H
