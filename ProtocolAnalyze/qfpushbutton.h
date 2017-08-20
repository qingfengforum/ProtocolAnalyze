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

private slots:
    void show_rightClickedMenu(const QPoint& point);

    void dialogBtnRename();
    void on_btnRename_okBtn_pushed();

    void on_btnEditCmd_action_triggered();
    void on_btnEditCmd_okBtn_pushed();

public:
    QVector<uchar> stringToHex(QString str_cmdHex);

    void setCmdHex(QVector<uchar> &cmdHex);
    QVector<uchar> getCmdHex();

    void setBtnIdx(uint btnIdx);
    uint getBtnIdx();

private:
    QVector<uchar> _cmd_hex;
    uint _btnIdx;

    bool midBtnPressed;
    QPoint m_press;
    QPoint m_move;



    QLineEdit* LineEdt_btnRename;
    QLineEdit* LineEdt_btnEditCmd;

    bool ctlKeyPressed;


};

#endif // qfpushbutton_H
