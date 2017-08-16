#include "qfpushbutton.h"

#include <QMouseEvent>
#include <QDebug>
#include <QMenu>
#include <QDialog>
#include <QGridLayout>
#include <QLineEdit>

qfPushButton::qfPushButton(QWidget *parent) :
    QPushButton(parent)
{

}

/*****************************************************
 * reimplemented funcs (protected)
 * **************************************************/
void qfPushButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MidButton) {
        midBtnPressed = true;
        m_press = event->globalPos();
        qDebug() << "middle button clicked";
    }
}
void qfPushButton::mouseMoveEvent(QMouseEvent *event)
{
    if (midBtnPressed) {
        m_move = event->globalPos();
        this->move(this->pos() + m_move - m_press);
        m_press = m_move;
        qDebug() << "middle button move";
    }
}
void qfPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MidButton) {
        midBtnPressed = false;
        qDebug() << "middle button release";
    }
}

/***********************************************
 * private slots
 * *********************************************/
void qfPushButton::dialogBtnRename()
{
    QDialog* dialogRename = new QDialog();

    /* set title */
    dialogRename->setWindowTitle("Rename");

    /* lay out */
    QGridLayout* lay = new QGridLayout(dialogRename);
    lay->setColumnMinimumWidth(0, 200);

    /* add items */
    QLineEdit*  lineEdit = new QLineEdit(dialogRename);
    LineEdt_btnRename = lineEdit;
    QPushButton* btn = new QPushButton(dialogRename);

    lay->addWidget(lineEdit, 0, 0);
    lay->addWidget(btn, 0, 1);

    btn->setText("OK");
    connect(btn, SIGNAL(clicked()), this, SLOT(on_btnRename_okBtn_pushed()));

    /* show dialog*/
    dialogRename->show();
    qDebug() << "qf button dialog";
}

void qfPushButton::on_btnRename_okBtn_pushed()
{

    if (LineEdt_btnRename != nullptr) {
        this->setText(LineEdt_btnRename->text());
        qDebug() << "qf rename";
    }
}

/************************************************
 * public slot
 ************************************************/
/*
 * show right clicked menu
 */
void qfPushButton::show_rightClickedMenu(const QPoint& point)
{
    QMenu* q_menu = new QMenu(this);
    q_menu->addAction("rename", this, SLOT(dialogBtnRename()));
    q_menu->addAction(new QAction(tr("resize")));
    q_menu->exec(QCursor::pos());
    qDebug() << "qf button right clicked button";
}


