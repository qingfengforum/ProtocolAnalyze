#include "protocolanalyze.h"
#include "ui_protocolanalyze.h"
#include "console.h"
#include "protocolgeneratordialog.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "qfpushbutton.h"

QT_USE_NAMESPACE
static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

ProtocolAnalyze::ProtocolAnalyze(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProtocolAnalyze)
{
    ui->setupUi(this);

    /* init private properties */
    btnIdx = 0;
    loadRcvAnalyzorSetTable();

    /* create serial object */
    serial = new QSerialPort(this);

    /* create new dialog of generate buttons */
    protGenDialog = new ProtocolGeneratorDialog(this);
    protGenDialogRecAnalyzor = new ProtocolGeneratorDialog(this);
    dialogRcvAnalyzor = new QDialog(this);

    console = new Console;
    ui->vtL_portOutPutInfo->addWidget(console);

    status = new QLabel;
    ui->statusBar->addWidget(status);



    fillPortsParameters();
    fillPortsInfo();

    /* initial */
    /* initial dialog protocol generator receive analyzor */
    initDialogGenSndButtons();
    initDialogGenRevAnalyzor();


    initActionsConnections();

    /* regist data read and write slot funcs */
    connect(serial, &QSerialPort::readyRead, this, &ProtocolAnalyze::readData);
    connect(console, &Console::getData, this, &ProtocolAnalyze::writeData);

    //on_pushBtn_loadBtnSettings_clicked();

    /* righ click menu*/
    ui->tabWdgt_btns->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tabWdgt_btns, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(show_rightClickedMenu(const QPoint&)));

}

ProtocolAnalyze::~ProtocolAnalyze()
{
    delete ui;
}

/*********************************************************
 * private slots
 * *******************************************************/
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
void ProtocolAnalyze::on_pB_autoGenBtn_clicked()
{
    qfPushButton* ptrBtn = (qfPushButton*)sender();

    QString cmd_str = "send : ";
    cmd_str += hexToString(ptrBtn->getCmdHex());
    cmd_str += "\n";
    qDebug() << cmd_str;
    console->putData(cmd_str.toLocal8Bit());

    sendDataToSerial(ptrBtn->getCmdHex());
}
void ProtocolAnalyze::on_pB_autoGenBtn_pressed()
{
   btnPressed = (QPushButton*)sender();
   qDebug() << "button has been pressed";
   if (btnPressed == nullptr) {
       qDebug() << "button pressed no";
   }
}
void ProtocolAnalyze::readData()
{
    QByteArray data = serial->readAll();
    QVector<uchar> data_hex;
    for (auto it = data.cbegin(); it != data.cend(); it++) {
        data_hex.append(*it);
    }

    QString data_str = hexToString(data_hex);
    QByteArray data_bArray;
    for(auto it = data_str.cbegin(); it!=data_str.cend(); it++) {
        data_bArray.append(*it);
    }
    data_bArray.append('\n');
    qDebug() << "read:(str)" << data_str;
    qDebug() << "read:(array)" << data_bArray;
    console->putData(data_bArray);
}
void ProtocolAnalyze::writeData(const QByteArray &data)
{
    serial->write(data);
}
void ProtocolAnalyze::on_pushBtn_loadBtnSettings_clicked()
{
    /* delete all buttons */
    QMap<int, qfPushButton*>::iterator i;
    for (i=cmdMap.begin(); i!=cmdMap.end(); ++i) {
           delete i.value();
    }
    cmdMap.clear();
    btnIdx = 0;

    /* open file */
    QFile btnSettings("./config/buttons_settings.txt");
    QTextStream fileIn(&btnSettings);

    if (!btnSettings.open(QFile::ReadOnly)) {
        qDebug() << "open file error";
        return;
    }
    qDebug() << fileIn.readLine();

    while (!fileIn.atEnd()) {
        QString btnName = "";
        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;
        QString str_cmdHex = "";
        QString line = fileIn.readLine();
        QStringList lineList = line.split(',', QString::SkipEmptyParts);
        btnName = lineList.at(0);
        str_cmdHex = lineList.at(1);
        x = lineList.at(2).toInt();
        y = lineList.at(3).toInt();
        w = lineList.at(4).toInt();
        h = lineList.at(5).toInt();
        qDebug() << str_cmdHex;

        QRect btnRect(x, y, w, h);
        QVector<uchar> cmd_hex = stringToHex(str_cmdHex);

        qfPushButton* pushBtn = new qfPushButton(ui->tabWdgt_btns);
        btnIdx++;
        pushBtn->setText(btnName);
        pushBtn->setGeometry(btnRect);
        pushBtn->setCmdHex(cmd_hex);
        pushBtn->setBtnIdx(btnIdx);
        pushBtn->show();

        cmdMap.insert(btnIdx, pushBtn);

        /* when btn clicked */
        connect(pushBtn, &qfPushButton::clicked, this ,&ProtocolAnalyze::on_pB_autoGenBtn_clicked);
    }

    btnSettings.close();
}
void ProtocolAnalyze::on_pushBtn_saveBtnSettings_clicked()
{
    /* open file */
    QFile btnSettins("./config/buttons_settings.txt");
    QTextStream out(&btnSettins);

    if (!btnSettins.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug() << "open file error";
        return ;
    }
    /* head */
    out << "btnName" << " " <<"btnCmd " << " " << "btnRect " << endl;

    QMap<int, qfPushButton*>::const_iterator i;
    for (i=cmdMap.begin(); i!=cmdMap.end(); ++i) {
        QString btnName = i.value()->text();
        QRect btnRect = i.value()->geometry();
        QString str_cmdHex = hexToString(i.value()->getCmdHex());
        qDebug() << btnRect << str_cmdHex;
        out << btnName << ","
            << str_cmdHex << ","
            << btnRect.x() << "," << btnRect.y() << ","
            << btnRect.width() << "," <<btnRect.height()
            << endl;
    }

    btnSettins.close();
}
void ProtocolAnalyze::on_pushBtn_clear_clicked()
{
    console->clear();
}
void ProtocolAnalyze::show_rightClickedMenu(const QPoint &)
{
    qDebug()<< "right clicked";
    QMenu * menu = new QMenu(ui->pushBtn_clear);
    menu->addAction("add button", this, SLOT(on_menuAddBtn_Action_triggered()));
    menu->exec(QCursor::pos());
    delete menu;
}
void ProtocolAnalyze::btnRename()
{
    QDialog* dialogRename = new QDialog(this);
    dialogRename->setWindowTitle("Rename");
    QGridLayout* lay = new QGridLayout(dialogRename);

    lay->setColumnMinimumWidth(0, 200);

    QPushButton* btn = new QPushButton(dialogRename);
    QLineEdit*  lineEdit = new QLineEdit(dialogRename);
    lay->addWidget(lineEdit, 0, 0);
    lay->addWidget(btn, 0, 1);

    btn->setText("OK");
    dialogRename->show();
}

void ProtocolAnalyze::on_deleteAction_triggered(uint btnIdx)
{
    qfPushButton* ptr_PushBtn = cmdMap.value(btnIdx);
    if (ptr_PushBtn != nullptr) {
        qDebug() << "ready to delete buttons : " << btnIdx;
        qDebug() << ptr_PushBtn->getBtnIdx();
        cmdMap.remove(btnIdx);
        ptr_PushBtn->deleteLater();
    }
}

void ProtocolAnalyze::on_menuAddBtn_Action_triggered()
{
    _lineEdit_btnName = nullptr;
    _lineEdit_cmdHex = nullptr;

    QDialog* dialogAddBtn = new QDialog();

    /* set title */
    dialogAddBtn->setWindowTitle("AddBtn");

    /* lay out */
    QGridLayout* lay = new QGridLayout(dialogAddBtn);
    //lay->setColumnMinimumWidth(0, 200);

    /* add items */
    QLabel* label_btnName = new QLabel("button name", dialogAddBtn);
    QLineEdit*  lineEdit_btnName = new QLineEdit(dialogAddBtn);
    QLabel* label_cmdHex = new QLabel("cmd hex", dialogAddBtn);
    QLineEdit*  lineEdit_cmdHex = new QLineEdit(dialogAddBtn);
    QPushButton* btn = new QPushButton(dialogAddBtn);

    lay->addWidget(label_btnName, 0, 0);
    lay->addWidget(lineEdit_btnName, 0, 1);
    lay->addWidget(label_cmdHex, 1, 0);
    lay->addWidget(lineEdit_cmdHex, 1, 1);
    lay->addWidget(btn, 2, 2);

    lay->setColumnMinimumWidth(1, 200);
    btn->setText("OK");

    _lineEdit_btnName = lineEdit_btnName;
    _lineEdit_cmdHex = lineEdit_cmdHex;

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(on_addBtn_OK_clicked()));

    /* show dialog*/
    dialogAddBtn->show();
    qDebug() << "add qf button dialog";
}

void ProtocolAnalyze::on_addBtn_OK_clicked()
{
    qDebug() << "add button";
    if (_lineEdit_btnName != nullptr && _lineEdit_cmdHex != nullptr) {
        QString btnName = _lineEdit_btnName->text();
        QVector<uchar> v_cmdHex = stringToHex(_lineEdit_cmdHex->text());
        addNewBtn(btnName, v_cmdHex);
        ((QDialog*)_lineEdit_btnName->parent())->close();
    }
}

void ProtocolAnalyze::on_pushBtn_startRcvAnalyzor_clicked()
{
    initDialogRcvAnalyzor();
    dialogRcvAnalyzor->show();
}

/*********************************************************
 * public funcs
 * *******************************************************/
/*
 * return : 0 : old button ; 1: new button
 */
int ProtocolAnalyze::generateButtons(QString btnName, QRect& btnRect, QVector<uchar> &cmd_hex)
{
    QMap<int, qfPushButton*>::iterator i;
    for (i=cmdMap.begin(); i!=cmdMap.end(); ++i) {
        if (btnName == i.value()->text()) {
            i.value()->setCmdHex(cmd_hex);
            qDebug("this btnhas already exist, update cmd_hex only");
            return 0;
        }
    }

    qfPushButton* pushBtn = new qfPushButton(ui->tabWdgt_btns);
    btnIdx++;
    pushBtn->setText(btnName);
    //pushBtn->setGeometry(btnRect);
    pushBtn->setCmdHex(cmd_hex);
    pushBtn->setBtnIdx(btnIdx);
    pushBtn->show();
    /* store info in the cmdMap */
    cmdMap.insert(btnIdx, pushBtn);

    /* when btn clicked */
    connect(pushBtn, &qfPushButton::clicked, this ,&ProtocolAnalyze::on_pB_autoGenBtn_clicked);
    connect(pushBtn, &qfPushButton::deleteAction_triggered, this, &ProtocolAnalyze::on_deleteAction_triggered);
    return 1;
}

QString ProtocolAnalyze::hexToString(const QVector<uchar> hex)
{
    QString hexStr = "";
    for (int i=0; i<hex.size(); i++) {
        hexStr += QString("%1").arg(hex.at(i), 2, 16, QChar('0'));
        hexStr += " ";
    }

    return hexStr;
}

QVector<uchar> ProtocolAnalyze::stringToHex(QString str_cmdHex)
{
    QVector<uchar> cmdHex;
    QStringList strList = str_cmdHex.split(' ', QString::SkipEmptyParts);

    for (int i=0; i<strList.size(); i++) {
        cmdHex.append(strList.at(i).toInt(nullptr, 16));
    }

    return cmdHex;
}

QVector<ProtocolAnalyze::COMM_RCV_PARSE_s>& ProtocolAnalyze::get_rcvParseTable()
{
    return _rcvParseTable;
}

/*********************************************************
 * private funcs
 * *******************************************************/
void ProtocolAnalyze::initDialogGenSndButtons()
{
    protGenDialog->initDialogGenSndButtons();
}

/*
 * @ brief : initialize dialog generator receive analyzor.
 */
void ProtocolAnalyze::initDialogGenRevAnalyzor()
{
    protGenDialogRecAnalyzor->initDialogGenRevAnalyzor();
}

void ProtocolAnalyze::initDialogRcvAnalyzor()
{
    QVector<COMM_RCV_PARSE_s>& rcvParseTable = _rcvParseTable;

    QGridLayout* layout = new QGridLayout(dialogRcvAnalyzor);
    int layoutRow = 0;

    /* print rcv Parse Table info */
    for (int i=0; i<rcvParseTable.size(); i++) {
        //qDebug() << "***********************************";
        //qDebug() << hex << rcvParseTable[i].cmdInfo.cmdId << ":" << rcvParseTable[i].cmdInfo.cmdName;
        //qDebug() << "value Info size " << rcvParseTable[i].valueInfo.size();
        QLabel* label_cmdId = new QLabel("[ " + rcvParseTable.at(i).cmdInfo.cmdName + " ]", dialogRcvAnalyzor);
        layout->addWidget(label_cmdId, layoutRow++, 0);
        for (int j=0; j<rcvParseTable[i].valueInfo.size(); j++) {
           // qDebug() << "================================";
            //qDebug() << "start bit :" << rcvParseTable[i].valueInfo[j].start_bit << endl
//                     << "end bit :"   << rcvParseTable[i].valueInfo[j].end_bit   << endl
//                     << "value name : " << rcvParseTable[i].valueInfo[j].value_name << endl
//                     << "cur value : " << rcvParseTable[i].valueInfo[j].value << endl;
             //qDebug() << "------------------------------------";
            QString valueInfo = QString( "start bit:%1 \n"
                                         "end   bit:%2 \n"
                                         "value name:%3 \n"
                                         "cur value:%4 \n")
                                         .arg(rcvParseTable[i].valueInfo[j].start_bit)
                                         .arg(rcvParseTable[i].valueInfo[j].end_bit)
                                         .arg(rcvParseTable[i].valueInfo[j].value_name)
                                         .arg(rcvParseTable[i].valueInfo[j].value);

            QLabel* label_valueInfo = new QLabel(valueInfo, dialogRcvAnalyzor);
            layout->addWidget(label_valueInfo, layoutRow++, 1);
            QLineEdit* lineEdt = new QLineEdit(dialogRcvAnalyzor);
            QLabel* label_valueName = new QLabel(rcvParseTable[i].valueInfo[j].value_name, dialogRcvAnalyzor);
            rcvParseTable[i].valueInfo[j].lineEdt = lineEdt;
            layout->addWidget(label_valueName, layoutRow, 0);
            layout->addWidget(lineEdt, layoutRow++, 1);

        }

        //qDebug() << "***********************************";
    }
    updateRcvAnalyzor();
}

void ProtocolAnalyze::updateRcvAnalyzor()
{
    QVector<COMM_RCV_PARSE_s>& rcvParseTable = _rcvParseTable;

    QGridLayout* layout = new QGridLayout(dialogRcvAnalyzor);
    int layoutRow = 0;

    /* print rcv Parse Table info */
    for (int i=0; i<rcvParseTable.size(); i++) {
        for (int j=0; j<rcvParseTable[i].valueInfo.size(); j++) {
            QString strValue = rcvParseTable[i].valueInfo[j].map_value.value(rcvParseTable[i].valueInfo[j].value);
            if (strValue != nullptr) {
                rcvParseTable[i].valueInfo[j].lineEdt->setText(strValue);
            }

        }
    }
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
 *@ brief : initial actions(signals) with slot.
 */
void ProtocolAnalyze::initActionsConnections()
{
    connect(ui->actionConnect, &QPushButton::clicked, this, &ProtocolAnalyze::openSerialPort);
    connect(ui->actionDisconnect, &QPushButton::clicked, this, &ProtocolAnalyze::closeSerialPort);
    connect(ui->actionProtocol_generator, &QAction::triggered, protGenDialog, &ProtocolAnalyze::show);
    connect(ui->actionProtocol_rev_gen_analyzor, &QAction::triggered, protGenDialogRecAnalyzor, &ProtocolAnalyze::show);
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

void ProtocolAnalyze::showStatusMessage(const QString &message)
{
    status->setText(message);
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

void ProtocolAnalyze::addNewBtn(QString btnName, QVector<uchar> cmd_hex, QRect btnRect)
{
    qfPushButton* pushBtn = new qfPushButton(ui->tabWdgt_btns);
    btnIdx++;
    pushBtn->setText(btnName);
    pushBtn->setGeometry(btnRect);
    pushBtn->setCmdHex(cmd_hex);
    pushBtn->setBtnIdx(btnIdx);
    pushBtn->show();
    /* store info in the cmdMap */
    cmdMap.insert(btnIdx, pushBtn);

    /* when btn clicked */
    connect(pushBtn, &qfPushButton::clicked, this ,&ProtocolAnalyze::on_pB_autoGenBtn_clicked);
    connect(pushBtn, &qfPushButton::deleteAction_triggered, this, &ProtocolAnalyze::on_deleteAction_triggered);
}

void ProtocolAnalyze::loadRcvAnalyzorSetTable()
{
    QVector<COMM_RCV_PARSE_s>& rcvParseTable = _rcvParseTable;
    // load settings
    /* open file */
    QFile rcvAnalyzorSettings("./config/receiveAnalyzor_settings_table.txt");
    QTextStream fileIn(&rcvAnalyzorSettings);

    if (!rcvAnalyzorSettings.open(QFile::ReadOnly)) {
        qDebug() << "open file error";
        return;
    }

    while(!fileIn.atEnd()) {
        QString line = fileIn.readLine();
        QStringList tmp = line.split('=');
        qDebug() << "load:" <<  tmp.at(0) << tmp.at(1);
        if (tmp.at(0) == "cmdId") {
            COMM_RCV_PARSE_s rcv_parse_item;
            rcv_parse_item.cmdInfo.cmdId = tmp.at(1).toInt();
            tmp = fileIn.readLine().split('=');
            qDebug() << "load:" << tmp.at(0) << tmp.at(1);
            rcv_parse_item.cmdInfo.cmdName = tmp.at(1);

            tmp = fileIn.readLine().split('=');
            qDebug() << "load:" << tmp.at(0) << tmp.at(1);
            while(!fileIn.atEnd()) {
                if (tmp.at(0) == "startBit") {
                    COMM_RCV_PARSE_VALUE_INFO_s rcv_parse_value_info;
                    rcv_parse_value_info.start_bit = tmp.at(1).toInt();

                    tmp = fileIn.readLine().split('=');
                    qDebug() << "load:" << tmp.at(0) << tmp.at(1);
                    rcv_parse_value_info.end_bit = tmp.at(1).toInt();

                    tmp = fileIn.readLine().split('=');
                    qDebug() << "load:" << tmp.at(0) << tmp.at(1);
                    rcv_parse_value_info.value_name = tmp.at(1);

                    tmp = fileIn.readLine().split('=');
                    qDebug() << "load:" << tmp.at(0) << tmp.at(1);
                    rcv_parse_value_info.value = tmp.at(1).toInt();

                    while(!fileIn.atEnd()) {
                        tmp = fileIn.readLine().split('=');
                        qDebug() << "load:" << tmp.at(0) << tmp.at(1);
                        if (tmp.at(0) == "key") {
                            QStringList value = fileIn.readLine().split('=');
                            qDebug() << "load:" << value.at(0) << value.at(1);
                            rcv_parse_value_info.map_value.insert(tmp.at(1).toInt(), value.at(1));
                        } else {
                            break;
                        }
                    }

                    rcv_parse_item.valueInfo.append(rcv_parse_value_info);
                } else {
                    break;
                }

            }
            rcvParseTable.append(rcv_parse_item);
        }

    }

    rcvAnalyzorSettings.close();

    printRcvAnalyzorSetTable();
}

void ProtocolAnalyze::printRcvAnalyzorSetTable()
{
    QVector<COMM_RCV_PARSE_s>& rcvParseTable = _rcvParseTable;
    /* print rcv Parse Table info */
    for (int i=0; i<rcvParseTable.size(); i++) {
        qDebug() << "***********************************";
        qDebug() << hex << rcvParseTable[i].cmdInfo.cmdId << ":" << rcvParseTable[i].cmdInfo.cmdName;
        qDebug() << "value Info size " << rcvParseTable[i].valueInfo.size();

        for (int j=0; j<rcvParseTable[i].valueInfo.size(); j++) {
            qDebug() << "================================";
            qDebug() << "start bit :" << rcvParseTable[i].valueInfo[j].start_bit << endl
                     << "end bit :"   << rcvParseTable[i].valueInfo[j].end_bit   << endl
                     << "value name : " << rcvParseTable[i].valueInfo[j].value_name << endl
                     << "cur value : " << rcvParseTable[i].valueInfo[j].value << endl;
            qDebug() << "------------------------------------";

            QMapIterator<int, QString> k(rcvParseTable[i].valueInfo[j].map_value);
            while (k.hasNext()) {
                k.next();
                qDebug() << k.key() << "--" << (QString)k.value();
            }

        }

        qDebug() << "***********************************";
    }

}

 void ProtocolAnalyze::sendDataToSerial(QVector<uchar> data)
 {
    QByteArray byteArrayData;

    for(auto iter = data.cbegin(); iter != data.cend(); iter++) {
        byteArrayData.append(*iter);
    }


    writeData(byteArrayData);
 }

void ProtocolAnalyze::on_pushButton_snd_carInfo_clicked()
{
    QVector<uchar> cmd_hex;
    cmd_hex.append(0xAB);
    cmd_hex.append(0xBA);
    cmd_hex.append(0x03);
    cmd_hex.append(0x0C);
    cmd_hex.append(0x05);

    /* speed */
    uint16_t speed = 0;
    speed = ui->lineEdit_carSpeed->text().toInt();
    cmd_hex.append((speed>>8) & 0xff);
    cmd_hex.append(speed & 0xff);

    /* gear */
    uint8_t gear = 0;
    if (ui->radioButton_p->isChecked()) {
        gear = 0x01;
    } else if (ui->radioButton_r->isChecked()) {
        gear = 0x02;
    } else if (ui->radioButton_n->isChecked()) {
        gear = 0x03;
    } else if (ui->radioButton_d->isChecked()) {
        gear = 0x04;
    } else if (ui->radioButton_m1->isChecked()) {
        gear = 0x05;
    } else if (ui->radioButton_m2->isChecked()) {
        gear = 0x06;
    } else if (ui->radioButton_m3->isChecked()) {
        gear = 0x07;
    } else if (ui->radioButton_m4->isChecked()) {
        gear = 0x08;
    } else if (ui->radioButton_m5->isChecked()) {
        gear = 0x09;
    } else if (ui->radioButton_m6->isChecked()) {
        gear = 0x0A;
    } else if (ui->radioButton_m7->isChecked()) {
        gear = 0x0B;
    } else if (ui->radioButton_m1_plus->isChecked()) {
        gear = 0x0D;
    } else if (ui->radioButton_m2_plus->isChecked()) {
        gear = 0x0E;
    } else if (ui->radioButton_m3_plus->isChecked()) {
        gear = 0x0F;
    } else if (ui->radioButton_m4_plus->isChecked()) {
        gear = 0x10;
    } else if (ui->radioButton_m5_plus->isChecked()) {
        gear = 0x11;
    } else if (ui->radioButton_m6_plus->isChecked()) {
        gear = 0x12;
    } else if (ui->radioButton_m2_minus->isChecked()) {
        gear = 0x14;
    } else if (ui->radioButton_m3_minus->isChecked()) {
        gear = 0x15;
    } else if (ui->radioButton_m4_minus->isChecked()) {
        gear = 0x16;
    } else if (ui->radioButton_m5_minus->isChecked()) {
        gear = 0x17;
    } else if (ui->radioButton_m6_minus->isChecked()) {
        gear = 0x18;
    } else if (ui->radioButton_m7_minus->isChecked()) {
        gear = 0x19;
    }
    cmd_hex.append(gear);

    /* light signal */
    uint8_t light = 0;
    if (ui->checkBox_leftLight->isChecked()) {
        light |= 0x1;
    }
    if (ui->checkBox_rightLight->isChecked()) {
        light |= 0x01 << 1;
    }
    if (ui->checkBox_highbeam->isChecked()) {
        light |= 0x01 << 2;
    }
    if (ui->checkBox_dippedHeadLight->isChecked()) {
        light |= 0x01 << 3;
    }
    if (ui->checkBox_afterFogLight->isChecked()) {
        light |= 0x01 << 4;
    }
    if (ui->checkBox_beforeFogLight->isChecked()) {
        light |= 0x01 << 5;
    }
    if (ui->checkBox_hazardLight->isChecked()) {
        light |= 0x01 << 6;
    }
    cmd_hex.append(light);

    /* safety signals */
    uint8_t safety = 0;
    if (ui->checkBox_throttle->isChecked()) {
        safety |= 0x01;
    }
    if (ui->checkBox_brake->isChecked()) {
        safety |= 0x01 << 1;
    }
    if (ui->checkBox_safetyBelt->isChecked()) {
        safety |= 0x01 << 2;
    }
    cmd_hex.append(safety);

    ProtocolGeneratorDialog p;
    uint16_t crc_check = p.crc16_check(cmd_hex, cmd_hex.size());
    cmd_hex.append((crc_check>>8) & 0xff);
    cmd_hex.append(crc_check & 0xff);

    qDebug() << hex << cmd_hex;
    sendDataToSerial(cmd_hex);
}
