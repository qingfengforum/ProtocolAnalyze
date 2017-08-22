#include "protocolgeneratordialog.h"
#include "ui_protocolgeneratordialog.h"

#include <QDebug>
#include <QFile>


ProtocolGeneratorDialog::ProtocolGeneratorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProtocolGeneratorDialog)
{
    ui->setupUi(this);

    configFilePath = "./config/Generator_Config_settings.txt";
    genType = GEN_TYPE_GEN_BUTTONS;

    /* init */
    fillComboBoxParams();

    /* init QTreeWidget */
    initTreeWidget();
}

ProtocolGeneratorDialog::~ProtocolGeneratorDialog()
{
    delete ui;
}

void ProtocolGeneratorDialog::initDialogGenRevAnalyzor()
{
    this->setWindowTitle("protocol receive analyzor generator");
    ui->pushBtn_generate->setText("gen Analyzor");
    configFilePath = "./config/Generator_receiveAnalyzor_settings.txt";
    genType = GEN_TYPE_GEN_RCV_ANALYZOR;
}
/*******************************************
 * private slots
 * *****************************************/

void ProtocolGeneratorDialog::on_treeWidget_doubleClicked(QTreeWidgetItem *item, int colum)
{
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    qDebug() <<colum;
}

void ProtocolGeneratorDialog::on_pushBtn_addRoot_clicked()
{
    QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->treeW_CmdList);
    newItem->setText(0, tr("item"));
    newItem->setText(1, tr("0x0"));
}

void ProtocolGeneratorDialog::on_pushBtn_addNode_clicked()
{
    if (ui->treeW_CmdList->currentItem() == NULL) {
        QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->treeW_CmdList);
        newItem->setText(0, tr("item"));
        newItem->setText(1, tr("0x0"));
    } else {
        QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->treeW_CmdList->currentItem());
        newItem->setText(0, tr("item"));
        newItem->setText(1, tr("0x0"));
    }
}

void ProtocolGeneratorDialog::on_pushBtn_deleteItem_clicked()
{
    if (ui->treeW_CmdList->currentItem() == NULL) {
        qDebug("has no item select");
    } else {
       delete ui->treeW_CmdList->currentItem();
    }
}

/* save tree widget items */
void ProtocolGeneratorDialog::on_pushBtn_saveSettings_clicked()
{
    /* printf treeWidget items that is going to save */
    QTreeWidgetItemIterator it0(ui->treeW_CmdList);
    while (*it0) {
        qDebug() << (*it0)->text(0);
        it0++;
    }


    QSettings settings(configFilePath, QSettings::IniFormat);
    settings.clear();

    /* save settings */
    settings.beginGroup(ui->treeW_CmdList->objectName()); /*settins prefix*/

    QTreeWidgetItemIterator it(ui->treeW_CmdList);
    int items_idx = 1;
    while (*it) {
        /* not save items with no key*/
        if ((*it)->text(0) == NULL ) {
            it++;
            continue;
        }

        if ((*it)->childCount() != 0) {
            saveChildSettings(settings, it, ("item"+QString::number(items_idx)));
        } else {
            settings.setValue("item"+QString::number(items_idx) + "_meaning", (*it)->text(0));
            settings.setValue("item"+QString::number(items_idx) + "_value", (*it)->text(1));
            settings.setValue("item"+QString::number(items_idx) + "_byte", (*it)->text(2));
            settings.setValue("item"+QString::number(items_idx) + "_bit", (*it)->text(3));
        }
        ++it;
        items_idx++;
    }
    settings.endGroup();

    qDebug()<< "save settings";
}

void ProtocolGeneratorDialog::on_pushBtn_loadSettings_clicked()
{
    static int first_in = 1;
    QSettings settings(configFilePath, QSettings::IniFormat);
    ui->treeW_CmdList->clear();
    settings.beginGroup(ui->treeW_CmdList->objectName());

    QStringList list = settings.allKeys();

    for (int i=0; i<list.size(); i++) {
        QString itemMeaning = settings.value("item"+QString::number(i) + "_meaning").toString();
        QString itemValue = settings.value("item"+QString::number(i) + "_value").toString();
        QString itemByte = settings.value("item"+QString::number(i) + "_byte").toString();
        QString itemBit = settings.value("item"+QString::number(i) + "_bit").toString();

        if (itemMeaning == NULL) {
            continue;
        }

        QTreeWidgetItem* newItem = new QTreeWidgetItem(ui->treeW_CmdList);
        newItem->setText(0, itemMeaning);
        newItem->setText(1, itemValue);
        newItem->setText(2, itemByte);
        newItem->setText(3, itemBit);

        if (settings.value("item"+QString::number(i)+".0" + "_meaning", "").toString() != NULL) {
            loadChildSettings(settings, list.size()-i-1, ("item"+QString::number(i)), newItem);
        }
    }

    if (first_in == 1) {
        first_in = 0;
    }
    settings.endGroup();
    qDebug()<< "load settings";
}

void ProtocolGeneratorDialog::on_pushBtn_generate_clicked()
{
    on_pushBtn_saveSettings_clicked();

    switch (genType) {
    case GEN_TYPE_GEN_BUTTONS:
        generatePushButtons();
        break;
    case GEN_TYPE_GEN_RCV_ANALYZOR:
        generateRcvAnalyzor();
        break;
    default:
        qDebug() << "not defined type";
        break;
    }

}

/**************************************************************************
 *  public func
 * ************************************************************************/

/******************************************************************
* 函数名称: CalculateCRC16
* 功能描述: 循环校验
* 输入参数: pLcPtr(指针地址)， LcLen(数据长度)
* 输出参数: CRC 校验结果
* 返 回 值: lwCRC16， 循环校验
*********************************************************************/
uint16_t ProtocolGeneratorDialog::crc16_check(QVector<uchar>& pLcPtr, uint16_t LcLen)
{
    uchar i;
    uint16_t lwCRC16 = 0;
    for(int j=0; j<LcLen; j++) {
        for(i=0x80;i!=0;i>>=1)
        {
            if(0 != (lwCRC16&0x8000))
            {
                lwCRC16 <<= 1;
                lwCRC16 ^= 0x1021;
            }
            else
            {
                lwCRC16 <<= 1;
            }
            if(0 != (pLcPtr[j]&i))
            {
                lwCRC16 ^= 0x1021;
            }
        }
    }
    return(lwCRC16);
}

/******************************************
 * private funcs
 * ****************************************/
/* init comboBox */
void ProtocolGeneratorDialog::fillComboBoxParams()
{
    /* head */
    ui->cBBox_head->addItem(QStringLiteral("AB BA"), CMD_HEAD_AB_BA);
    ui->cBBox_head->addItem(QStringLiteral("5A A5"), CMD_HEAD_5A_A5);

    /* check method */
    ui->cBBox_check_method->addItem(QStringLiteral("checkSum 1 byte"), CMD_CHECK_TYPE_CHECK_SUM_1BYTE); /* index 0*/
    ui->cBBox_check_method->addItem(QStringLiteral("checkSum 2 byte"), CMD_CHECK_TYPE_CHECK_SUM_2BYTE); /* index 1*/
    ui->cBBox_check_method->addItem(QStringLiteral("checkCrc 2 byte"), CMD_CHECK_TYPE_CRC_2BYTE); /* index 2*/
    ui->cBBox_check_method->setCurrentIndex(2);

    /* len meaning */
    ui->cBBox_len_meaning->addItem(QStringLiteral("the whole lenght"));
    ui->cBBox_len_meaning->addItem(QStringLiteral("len = cmd + param + check"));

    /* hide not used widget */
    ui->cBBox_len_meaning->hide();
    ui->labl_len->hide();
}

/* init treeWidget */
void ProtocolGeneratorDialog::initTreeWidget()
{
    /* init params */
    ui->treeW_CmdList->setColumnCount(ITEM_COLUM_NUM);
    ui->treeW_CmdList->setHeaderLabels(QStringList()<<"meaning"<<"value"<<"byte"<<"bit");

    /* connect slots  double clicked */
    connect(ui->treeW_CmdList, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(on_treeWidget_doubleClicked(QTreeWidgetItem *, int)));

    /* load items */
    on_pushBtn_loadSettings_clicked();

}

void ProtocolGeneratorDialog::saveChildSettings(QSettings &settings, QTreeWidgetItemIterator &it, QString head)
{
    int count = (*it)->childCount();
    /* save parent */
    settings.setValue(head + "_meaning", (*it)->text(0));
    settings.setValue(head + "_value", (*it)->text(1));
    settings.setValue(head + "_byte", (*it)->text(2));
    settings.setValue(head + "_bit", (*it)->text(3));

    for (int j=0; j<count; j++) {
        ++it;
        if ((*it)->childCount() != 0) {
            saveChildSettings(settings, it, (head + "." + QString::number(j)));
        } else {
            settings.setValue(head + "." + QString::number(j) + "_meaning", (*it)->text(0));
            settings.setValue(head + "." + QString::number(j)+"_value", (*it)->text(1));
            settings.setValue(head + "." + QString::number(j)+"_byte", (*it)->text(2));
            settings.setValue(head + "." + QString::number(j)+"_bit", (*it)->text(3));
        }
    }
    return;
}

void ProtocolGeneratorDialog::loadChildSettings(QSettings &settings, int size, QString head, QTreeWidgetItem* item)
{
    for (int i=0; i<size; i++) {
        QString itemMeaning = settings.value(head + "." + QString::number(i) + "_meaning").toString();
        QString itemValue = settings.value(head + "." + QString::number(i) + "_value").toString();
        QString itemByte = settings.value(head + "." + QString::number(i) + "_byte").toString();
        QString itemBit = settings.value(head + "." + QString::number(i) + "_bit").toString();

        if (itemMeaning == NULL) {
            continue;
        }

        QTreeWidgetItem* newItem = new QTreeWidgetItem(item);
        newItem->setText(0, itemMeaning);
        newItem->setText(1, itemValue);
        newItem->setText(2, itemByte);
        newItem->setText(3, itemBit);

        if (settings.value(head + "." + QString::number(i) +".0" + "_meaning", "").toString() != NULL) {
            loadChildSettings(settings, size-i-1, (head + "." + QString::number(i)), newItem);
        }
    }
}


void ProtocolGeneratorDialog::generatePushButtons()
{
    int lastBtn_isNewBtn = 1;

    /* get parent pointer to access its public funcs */
    ProtocolAnalyze* pMain = (ProtocolAnalyze*) QWidget::parent();

    /* for lay out */
    QRect btnRect(0,30, 100, 30);
    int btn_dy = 30;
    int btn_dx = 100;

    int topCount = ui->treeW_CmdList->topLevelItemCount();

    /* open file */
    QFile btnSettings("./config/buttons_settings.txt");
    QTextStream out(&btnSettings);

    if (btnSettings.open(QFile::WriteOnly | QFile::Truncate)) {
          out << "btnName " <<"btnCmd " << "btnRect " << endl;
     } else {
        qDebug() << "open file error";
        return;
    }

    for (int i=0; i<topCount; i++) {
        QString btnName = "";
        QVector<uchar> cmd_hex(2);

        QTreeWidgetItem* topItem= ui->treeW_CmdList->topLevelItem(i);
        int cmd_id = topItem->text(ITEM_COLUM_VALUE).toInt(NULL, 16);// cmd_id
        int param_len = topItem->text(ITEM_COLUM_BYTE).toInt(NULL, 16); // param_len
        int total_len = param_len + 7; // 2(head) + 1(cmd_id) + 1(total_len) + 1(param_len) + 2(crc_check)

        for (int i=0; i<total_len-2; i++) {
            cmd_hex.append(0);
        }

        if (total_len < 7) {
            qDebug() <<"total_len is too short" << total_len;
            return;
        }

        /* head */
        if (ui->cBBox_head->currentData() == CMD_HEAD_AB_BA) {
            cmd_hex[0] = 0xab;
            cmd_hex[1] = 0xba;
        } else if (ui->cBBox_head->currentData() == CMD_HEAD_5A_A5) {
            cmd_hex[0] = 0x5a;
            cmd_hex[1] = 0xa5;
        }

        cmd_hex[2] = cmd_id;    // cmd_id
        cmd_hex[3] = total_len; // total_len
        cmd_hex[4] = param_len; // param_len

        for (int j=0; j<topItem->childCount(); j++) {
            /* clear param[] and crc_check */
            for(int i=5; i< cmd_hex.size(); i++) {
                cmd_hex[i] = 0;
            }


            QTreeWidgetItem* level1_childItem = topItem->child(j);
            int paramPosByte = level1_childItem->text(ITEM_COLUM_BYTE).toInt(NULL, 16);
            QString strBit = level1_childItem->text(ITEM_COLUM_BIT);
            QStringList strBitList = strBit.split('-', QString::SkipEmptyParts);
            int startBit = 0;
            int endBit = 0;
            if (strBitList.at(0).toInt() < strBitList.at(1).toInt()) {
                 startBit = strBitList.at(0).toInt();
                 endBit = strBitList.at(1).toInt();
            } else {
                startBit = strBitList.at(1).toInt();
                endBit = strBitList.at(0).toInt();
            }
            qDebug() << "startBit: " << startBit << ", endBit: " << endBit;

            /* adjust button position --> move to top*/
            if (j != 0 && lastBtn_isNewBtn) {
                btnRect.translate(btn_dx,0);
                btnRect.moveTop(30);
            }

            for (int k=0; k<level1_childItem->childCount(); k++) {
                QTreeWidgetItem* level2_childItem = level1_childItem->child(k);
                btnName = level1_childItem->text(ITEM_COLUM_MEANTING) + level2_childItem->text(ITEM_COLUM_MEANTING);
                int int_param = level2_childItem->text(ITEM_COLUM_VALUE).toInt(NULL, 16);
                int_param = int_param << startBit;

                cmd_hex[paramPosByte+4] = int_param;

                qDebug() << hex << cmd_hex;
                if (k != 0 && lastBtn_isNewBtn) {
                    if (k%4 == 0) {
                        btnRect.moveTop(30);
                        btnRect.translate(btn_dx,0);
                    } else {
                        btnRect.translate(0, btn_dy);
                    }
                }

                /* crc_check */
                uint16_t crcCheck = 0;
                if (ui->cBBox_check_method->currentData() == CMD_CHECK_TYPE_CRC_2BYTE) {
                    crcCheck = crc16_check(cmd_hex, cmd_hex.size()-2);
                }
                uchar crc_h = (uchar)(crcCheck>>8);
                uchar crc_l = (uchar)(crcCheck&0xff);
                cmd_hex[cmd_hex[3]-2] = crc_h;
                cmd_hex[cmd_hex[3]-1] = crc_l;
                qDebug() << "before send" << hex << cmd_hex;

                QString str_cmdHex= pMain->hexToString(cmd_hex);
                out << btnName << "," << str_cmdHex << "," << btnRect.x() << "," << btnRect.y() << "," << btnRect.width() << "," <<btnRect.height()<<endl; //<< cmd_hex << "," << btnRect;
                lastBtn_isNewBtn = pMain->generateButtons(btnName, btnRect, cmd_hex);
            }
        }
    }

    btnSettings.close();
}
void ProtocolGeneratorDialog::generateRcvAnalyzor()
{
#if 0
    qDebug() << __func__;

    /* get parent pointer to access its public funcs */
    ProtocolAnalyze* pMain = (ProtocolAnalyze*) QWidget::parent();

    int topCount = ui->treeW_CmdList->topLevelItemCount();

#if 0 // save settings
    /* open file */
    QFile rcvAnalyzorSettings("./config/receiveAnalyzor_settings.txt");
    QTextStream out(&rcvAnalyzorSettings);

    if (rcvAnalyzorSettings.open(QFile::WriteOnly | QFile::Truncate)) {
          out << "btnName " <<"btnCmd " << "btnRect " << endl;
     } else {
        qDebug() << "open file error";
        return;
    }
#endif
    for (int i=0; i<topCount; i++) {
        QString btnName = "";
        QVector<uchar> cmd_hex(2);

        QTreeWidgetItem* topItem= ui->treeW_CmdList->topLevelItem(i);
        int cmd_id = topItem->text(ITEM_COLUM_VALUE).toInt(NULL, 16);// cmd_id
        int param_len = topItem->text(ITEM_COLUM_BYTE).toInt(NULL, 16); // param_len
        int total_len = param_len + 7; // 2(head) + 1(cmd_id) + 1(total_len) + 1(param_len) + 2(crc_check)

        for (int i=0; i<total_len-2; i++) {
            cmd_hex.append(0);
        }

        if (total_len < 7) {
            qDebug() <<"total_len is too short" << total_len;
            return;
        }

        /* head */
        if (ui->cBBox_head->currentData() == CMD_HEAD_AB_BA) {
            cmd_hex[0] = 0xab;
            cmd_hex[1] = 0xba;
        } else if (ui->cBBox_head->currentData() == CMD_HEAD_5A_A5) {
            cmd_hex[0] = 0x5a;
            cmd_hex[1] = 0xa5;
        }

        cmd_hex[2] = cmd_id;    // cmd_id
        cmd_hex[3] = total_len; // total_len
        cmd_hex[4] = param_len; // param_len

        for (int j=0; j<topItem->childCount(); j++) {
            /* clear param[] and crc_check */
            for(int i=5; i< cmd_hex.size(); i++) {
                cmd_hex[i] = 0;
            }


            QTreeWidgetItem* level1_childItem = topItem->child(j);
            int paramPosByte = level1_childItem->text(ITEM_COLUM_BYTE).toInt(NULL, 16);
            QString strBit = level1_childItem->text(ITEM_COLUM_BIT);
            QStringList strBitList = strBit.split('-', QString::SkipEmptyParts);
            int startBit = 0;
            int endBit = 0;
            if (strBitList.at(0).toInt() < strBitList.at(1).toInt()) {
                 startBit = strBitList.at(0).toInt();
                 endBit = strBitList.at(1).toInt();
            } else {
                startBit = strBitList.at(1).toInt();
                endBit = strBitList.at(0).toInt();
            }
            qDebug() << "startBit: " << startBit << ", endBit: " << endBit;

            /* adjust button position --> move to top*/
            if (j != 0 && lastBtn_isNewBtn) {
                btnRect.translate(btn_dx,0);
                btnRect.moveTop(30);
            }

            for (int k=0; k<level1_childItem->childCount(); k++) {
                QTreeWidgetItem* level2_childItem = level1_childItem->child(k);
                btnName = level1_childItem->text(ITEM_COLUM_MEANTING) + level2_childItem->text(ITEM_COLUM_MEANTING);
                int int_param = level2_childItem->text(ITEM_COLUM_VALUE).toInt(NULL, 16);
                int_param = int_param << startBit;

                cmd_hex[paramPosByte+4] = int_param;

                qDebug() << hex << cmd_hex;
                if (k != 0 && lastBtn_isNewBtn) {
                    if (k%4 == 0) {
                        btnRect.moveTop(30);
                        btnRect.translate(btn_dx,0);
                    } else {
                        btnRect.translate(0, btn_dy);
                    }
                }

                /* crc_check */
                uint16_t crcCheck = 0;
                if (ui->cBBox_check_method->currentData() == CMD_CHECK_TYPE_CRC_2BYTE) {
                    crcCheck = crc16_check(cmd_hex, cmd_hex.size()-2);
                }
                uchar crc_h = (uchar)(crcCheck>>8);
                uchar crc_l = (uchar)(crcCheck&0xff);
                cmd_hex[cmd_hex[3]-2] = crc_h;
                cmd_hex[cmd_hex[3]-1] = crc_l;
                qDebug() << "before send" << hex << cmd_hex;

                QString str_cmdHex= pMain->hexToString(cmd_hex);
                out << btnName << "," << str_cmdHex << "," << btnRect.x() << "," << btnRect.y() << "," << btnRect.width() << "," <<btnRect.height()<<endl; //<< cmd_hex << "," << btnRect;
                lastBtn_isNewBtn = pMain->generateButtons(btnName, btnRect, cmd_hex);
            }
        }
    }

    btnSettings.close();
#endif
}


