#ifndef PROTOCOLANALYZE_H
#define PROTOCOLANALYZE_H


#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include <QLabel>
#include <QMap>
#include "qfpushbutton.h"

namespace Ui {
class ProtocolAnalyze;
}

class Console;
class ProtocolGeneratorDialog;

class ProtocolAnalyze : public QMainWindow
{
    Q_OBJECT

public:
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };
    struct BtnSettings {
        QString btnName;
        QVector<uchar> cmdHex;
        QRect btnRect;
    };

public:
    explicit ProtocolAnalyze(QWidget *parent = 0);
    ~ProtocolAnalyze();

private slots:
    void openSerialPort();
    void closeSerialPort();

    void on_pB_refreshPortInfo_clicked();
    void on_pB_autoGenBtn_clicked();
    void on_pB_autoGenBtn_pressed();

    void readData();
    void writeData(const QByteArray &data);

    void on_pushBtn_loadBtnSettings_clicked();
    void on_pushBtn_saveBtnSettings_clicked();

    void on_pushBtn_clear_clicked();
    void show_rightClickedMenu(const QPoint&);

    void btnRename();

    void on_deleteAction_triggered(uint btnIdx);
    void on_menuAddBtn_Action_triggered();
    void on_addBtn_OK_clicked();


public:
    int generateButtons(QString btnName, QRect &btnRect, QVector<uchar> &cmd_hex);
    QString hexToString(const QVector<uchar> hex);
    QVector<uchar> stringToHex(QString str_cmdHex);

private:
    void fillPortsInfo();
    void initActionsConnections();
    void fillPortsParameters();
    void showStatusMessage(const QString &message);
    void updateSettings();

    void addNewBtn(QString btnName, QVector<uchar> cmd_hex, QRect btnRect=QRect(0,30, 100, 30));

private:
    Ui::ProtocolAnalyze *ui;
    Console *console;
    Settings portSetting;
    QLabel *status;
    QSerialPort *serial;

    ProtocolGeneratorDialog *protGenDialog;

    QMap<int, qfPushButton*> cmdMap; /* store btn info */
    uint btnIdx;

    QPushButton* btnPressed;
    QPoint m_press;
    bool midBtnPress;

    QLineEdit* _lineEdit_btnName;
    QLineEdit* _lineEdit_cmdHex;

};

#endif // PROTOCOLANALYZE_H
