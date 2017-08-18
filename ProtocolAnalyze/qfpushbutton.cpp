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

void qfPushButton::wheelEvent(QWheelEvent * event)
{
    if (ctlKeyPressed) {
        QPoint numStep = event->angleDelta() / 8 /15;
        QSize size = this->size();
        size.setWidth(size.width() + numStep.ry()*3);
        this->resize(size);
    }
    qDebug() << "qingfeng qwheel event";
}

void qfPushButton::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control) {
        ctlKeyPressed = true;
    }
    qDebug() << "key pressed";
}

void qfPushButton::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control) {
        ctlKeyPressed = false;
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
        ((QDialog*)LineEdt_btnRename->parent())->close();
    }
}

 void qfPushButton::on_btnEditCmd_action_triggered()
 {
    qDebug() << "qf edit cmd";

    QDialog* dialogEditCmd = new QDialog();

    /* set title */
    dialogEditCmd->setWindowTitle("Edit Cmd（hex）");

    /* lay out */
    QGridLayout* lay = new QGridLayout(dialogEditCmd);
    lay->setColumnMinimumWidth(0, 200);

    /* add items */
    QLineEdit*  lineEdit = new QLineEdit(dialogEditCmd);
    LineEdt_btnEditCmd = lineEdit;
    QPushButton* btn = new QPushButton(dialogEditCmd);

    lay->addWidget(lineEdit, 0, 0);
    lay->addWidget(btn, 0, 1);

    btn->setText("set");
    connect(btn, SIGNAL(clicked()), this, SLOT(on_btnEditCmd_okBtn_pushed()));

    /* show dialog*/
    dialogEditCmd->show();
 }

void qfPushButton::on_btnEditCmd_okBtn_pushed()
{
    if (LineEdt_btnEditCmd != nullptr) {
        //this->setText(LineEdt_btnRename->text());
        cmd_hex = stringToHex(LineEdt_btnEditCmd->text());
        qDebug() << "qf edit cmd set";
        ((QDialog*)LineEdt_btnEditCmd->parent())->close();

        qDebug() << hex << cmd_hex;
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
    q_menu->addAction("edit cmd", this, SLOT(on_btnEditCmd_action_triggered()));
    q_menu->exec(QCursor::pos());
    qDebug() << "qf button right clicked button";
}

/*************************************************
 * public func
 * ***********************************************/
QVector<uchar> qfPushButton::stringToHex(QString str_cmdHex)
{
    QVector<uchar> cmdHex;
    QStringList strList = str_cmdHex.split(' ', QString::SkipEmptyParts);

    for (int i=0; i<strList.size(); i++) {
        cmdHex.append(strList.at(i).toInt(nullptr, 16));
    }

    return cmdHex;
}
