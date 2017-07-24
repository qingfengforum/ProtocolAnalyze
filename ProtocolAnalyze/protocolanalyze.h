#ifndef PROTOCOLANALYZE_H
#define PROTOCOLANALYZE_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

#include <QMessageBox>
#include <QLabel>

namespace Ui {
class ProtocolAnalyze;
}

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

public:
    explicit ProtocolAnalyze(QWidget *parent = 0);
    ~ProtocolAnalyze();

private slots:
    void openSerialPort();
    void closeSerialPort();

    void on_pB_refreshPortInfo_clicked();

private:
    void fillPortsInfo();
    void initActionsConnections();
    void fillPortsParameters();
    void showStatusMessage(const QString &message);

private:
    Ui::ProtocolAnalyze *ui;
    Settings portSetting;
    QLabel *status;
    QSerialPort *serial;

};

#endif // PROTOCOLANALYZE_H
