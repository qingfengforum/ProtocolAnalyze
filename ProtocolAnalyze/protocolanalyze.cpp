#include "protocolanalyze.h"
#include "ui_protocolanalyze.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>

QT_USE_NAMESPACE
static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

ProtocolAnalyze::ProtocolAnalyze(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProtocolAnalyze)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);

    status = new QLabel;
    ui->statusBar->addWidget(status);

    fillPortsParameters();
    fillPortsInfo();

    initActionsConnections();

}

ProtocolAnalyze::~ProtocolAnalyze()
{
    delete ui;
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
/*
 * @ brief : open a serial port
 */
void ProtocolAnalyze::openSerialPort()
{
    serial->setPortName(ui->serialPortInfoListBox->currentText());
    serial->setBaudRate(ui->baudRateBox->currentText().toInt());
    serial->setDataBits(static_cast<QSerialPort::DataBits>(
                            ui->dataBitsBox->itemData(ui->dataBitsBox->currentIndex()).toInt()));
    serial->setParity(static_cast<QSerialPort::Parity>(
                          ui->parityBox->itemData(ui->parityBox->currentIndex()).toInt()));
    serial->setStopBits(static_cast<QSerialPort::StopBits>(
                            ui->stopBitsBox->itemData(ui->stopBitsBox->currentIndex()).toInt()));
    serial->setFlowControl(static_cast<QSerialPort::FlowControl>(
                               ui->flowControlBox->itemData(ui->flowControlBox->currentIndex()).toInt()));
    if (serial->open(QIODevice::ReadWrite)) {
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        showStatusMessage(tr("Connected Success!"));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        showStatusMessage(tr("Open error"));
    }

}

void ProtocolAnalyze::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
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
