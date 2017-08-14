#ifndef QFPUSHBUTTON_H
#define QFPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

class qfpushbutton : public QPushButton
{
public:
    explicit qfpushbutton(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private:
    bool midBtnPressed;
    QPoint m_press;
    QPoint m_move;
};

#endif // qfpushbutton_H
