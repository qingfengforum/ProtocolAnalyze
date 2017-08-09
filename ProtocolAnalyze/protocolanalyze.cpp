#include "protocolanalyze.h"
#include "ui_protocolanalyze.h"
#include "console.h"
#include "protocolgeneratordialog.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>

QT_USE_NAMESPACE
static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

ProtocolAnalyze::ProtocolAnalyze(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProtocolAnalyze)
{
    ui->setupUi(this);
    protGenDialog = new ProtocolGeneratorDialog(this);
    serial = new QSerialPort(this);

    console = new Console;
    //console->setEnabled(false);
    //console->copyAvailable(true);
    ui->vtL_portOutPutInfo->addWidget(console);

    status = new QLabel;
    ui->statusBar->addWidget(status);

    fillPortsParameters();
    fillPortsInfo();

    initActionsConnections();

    /* regist data read and write slot funcs */
    connect(serial, &QSerialPort::readyRead, this, &ProtocolAnalyze::readData);
    connect(console, &Console::getData, this, &ProtocolAnalyze::writeData);

    //generateButtons("init");
}

ProtocolAnalyze::~ProtocolAnalyze()
{
    delete ui;
}

void ProtocolAnalyze::generateButtons(QString btnName, QRect& btnRect, QVector<uchar> &cmd_hex)
{
    //QRect btnRect(0, 20, 100, 30);
    // btnRect.translate(0, move_dy);
    QPushButton* pushBtn = new QPushButton("qingfeng btn", ui->tabWdgt_btns);
    pushBtn->setText(btnName);
    pushBtn->setGeometry(btnRect);
    pushBtn->show();

    cmdMap[btnName] = cmd_hex;

    connect(pushBtn, &QPushButton::clicked, this ,&ProtocolAnalyze::on_pB_autoGenBtn_clicked);


}

void ProtocolAnalyze::fillPortsParameters()
{
    ui->baudRateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->baudRateBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->baudRateBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->baudRateBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    //ui->baudRateBox->addItem(tr("Custom"));

    ui->dataBitsBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->dataBitsBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->dataBitsBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->dataBitsBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->dataBitsBox->setCurrentIndex(3);

    ui->parityBox->addItem(tr("None"), QSerialPort::NoParity);
    ui->parityBox->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->parityBox->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->parityBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->parityBox->addItem(tr("Space"), QSerialPort::SpaceParity);

    ui->stopBitsBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    ui->stopBitsBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
    ui->stopBitsBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    ui->flowControlBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    ui->flowControlBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    ui->flowControlBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

/*
 * @ brief : auto fill the available port name
 */
void ProtocolAnalyze::fillPortsInfo()
{
    ui->serialPortInfoListBox->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);

        ui->serialPortInfoListBox->addItem(list.first(), list);
    }

}

void ProtocolAnalyze::updateSettings()
{
    portSetting.name = ui->serialPortInfoListBox->currentText();

    if (ui->baudRateBox->currentIndex() == 4) {
        portSetting.baudRate = ui->baudRateBox->currentText().toInt();
    } else {
        portSetting.baudRate = static_cast<QSerialPort::BaudRate>(
                    ui->baudRateBox->itemData(ui->baudRateBox->currentIndex()).toInt());
    }
    portSetting.stringBaudRate = QString::number(portSetting.baudRate);

    portSetting.dataBits = static_cast<QSerialPort::DataBits>(
                ui->dataBitsBox->itemData(ui->dataBitsBox->currentIndex()).toInt());
    portSetting.stringDataBits = ui->dataBitsBox->currentText();

    portSetting.parity = static_cast<QSerialPort::Parity>(
                ui->parityBox->itemData(ui->parityBox->currentIndex()).toInt());
    portSetting.stringParity = ui->parityBox->currentText();

    portSetting.stopBits = static_cast<QSerialPort::StopBits>(
                ui->stopBitsBox->itemData(ui->stopBitsBox->currentIndex()).toInt());
    portSetting.stringStopBits = ui->stopBitsBox->currentText();

    portSetting.flowControl = static_cast<QSerialPort::FlowControl>(
                ui->flowControlBox->itemData(ui->flowControlBox->currentIndex()).toInt());
    portSetting.stringFlowControl = ui->flowControlBox->currentText();
}

/*
 * @ brief : open a serial port
 */
void ProtocolAnalyze::openSerialPort()
{
    updateSettings();
    Settings *ps = &portSetting;
    serial->setPortName(ps->name);
    serial->setBaudRate(ps->baudRate);
    serial->setDataBits(ps->dataBits);
    serial->setParity(ps->parity);
    serial->setStopBits(ps->stopBits);
    serial->setFlowControl(ps->flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        console->setEnabled(true);
        console->setLocalEchoEnabled(true);
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(ps->name).arg(ps->stringBaudRate).arg(ps->stringDataBits)
                          .arg(ps->stringParity).arg(ps->stringStopBits).arg(ps->stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        showStatusMessage(tr("Open error"));
    }

}

void ProtocolAnalyze::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();

    //console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    showStatusMessage(tr("Disconnected"));
}

/*
 *@ brief : initial actions(signals) with slot.
 */
void ProtocolAnalyze::initActionsConnections()
{
    connect(ui->actionConnect, &QPushButton::clicked, this, &ProtocolAnalyze::openSerialPort);
    connect(ui->actionDisconnect, &QPushButton::clicked, this, &ProtocolAnalyze::closeSerialPort);
    connect(ui->actionProtocol_generator, &QAction::triggered, protGenDialog, &ProtocolAnalyze::show);
}


void ProtocolAnalyze::readData()
{
    QByteArray data = serial->readAll();
    console->putData(data);
}

void ProtocolAnalyze::writeData(const QByteArray &data)
{
    serial->write(data);
}



/***************************************************/
/************* actions *****************************/
/***************************************************/
/*
 * @ brief : [refresh port] refresh available port name information
 */
void ProtocolAnalyze::on_pB_refreshPortInfo_clicked()
{
    ui->serialPortInfoListBox->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        list << info.portName();

        ui->serialPortInfoListBox->addItem(list.first(), list);
    }
}

void ProtocolAnalyze::showStatusMessage(const QString &message)
{
    status->setText(message);
}

/***************************************************/
/************* slots *****************************/
/***************************************************/

 void ProtocolAnalyze::on_pB_autoGenBtn_clicked()
 {
    QPushButton* ptrBtn = (QPushButton*)sender();
    QVector<uchar> cmd(cmdMap[ptrBtn->text()]);

    QString cmd_str = "send : ";
    cmd_str += hexToString(cmd);
    cmd_str += "\n";
    qDebug() << cmd_str;
    console->putData(cmd_str.toLocal8Bit());
 }

 /*********
  * tools
  * ******/
 QString ProtocolAnalyze::hexToString(QVector<uchar> &hex)
 {
     QString hexStr = "";
     for (int i=0; i<hex.size(); i++) {
         hexStr += QString("%1").arg(hex.at(i), 2, 16, QChar('0'));
         hexStr += " ";
     }

     return hexStr;
 }

void ProtocolAnalyze::on_pushBtn_loadBtnSettings_clicked()
{
    /* open file */
    QFile btnSettins("./config/buttons_settins.txt");
    QTextStream fileIn(&btnSettins);

    if (!btnSettins.open(QFile::ReadOnly)) {
        qDebug() << "open file error";
        return;
    }
    qDebug() << fileIn.readLine();
    QString btnName = "";
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
    QString str_cmdHex = "";
    QString line = fileIn.readLine();
    qDebug() << btnName;
    qDebug() << str_cmdHex;
    qDebug() << x << y << w << h;

#if 0
    QPushButton* pushBtn = new QPushButton("qingfeng btn", ui->tabWdgt_btns);
    pushBtn->setText(btnName);
    pushBtn->setGeometry(btnRect);
    pushBtn->show();

    cmdMap[btnName] = cmd_hex;

    connect(pushBtn, &QPushButton::clicked, this ,&ProtocolAnalyze::on_pB_autoGenBtn_clicked);
#endif
    //out << "btnName" << " " <<"btnCmd " << " " << "btnRect " << endl;
    btnSettins.close();
}
