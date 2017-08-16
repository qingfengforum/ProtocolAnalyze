#ifndef QFPUSHBUTTON_H
#define QFPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>

class qfPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit qfPushButton(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void show_rightClickedMenu(const QPoint& point);

private slots:
    void dialogBtnRename();

private:
    bool midBtnPressed;
    QPoint m_press;
    QPoint m_move;

    QVector<uchar> cmd_hex;
};

#endif // qfpushbutton_H
