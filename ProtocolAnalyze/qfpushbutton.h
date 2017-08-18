#ifndef QFPUSHBUTTON_H
#define QFPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>

class qfPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit qfPushButton(QWidget *parent = 0);

protected:
    /* use middle mouse button to move button */
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    /* for use ctrl+wheel to resize button */
    void wheelEvent(QWheelEvent * event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

public slots:
    void show_rightClickedMenu(const QPoint& point);

private slots:
    void dialogBtnRename();
    void on_btnRename_okBtn_pushed();
    void on_btnResize_action_triggered();

private:
    bool midBtnPressed;
    QPoint m_press;
    QPoint m_move;

    QVector<uchar> cmd_hex;

    QLineEdit* LineEdt_btnRename;

    bool ctlKeyPressed;


};

#endif // qfpushbutton_H
