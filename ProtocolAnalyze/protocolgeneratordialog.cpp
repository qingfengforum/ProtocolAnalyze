#include "protocolgeneratordialog.h"
#include "ui_protocolgeneratordialog.h"

#include <QDebug>
#include <QFile>


ProtocolGeneratorDialog::ProtocolGeneratorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProtocolGeneratorDialog)
{
    ui->setupUi(this);

    /* init */
    fillComboBoxParams();

    /* init QTreeWidget */
    initTreeWidget();
}

ProtocolGeneratorDialog::~ProtocolGeneratorDialog()
{
    delete ui;
}

void ProtocolGeneratorDialog::fillComboBoxParams()
{
    /* head */
    ui->cBBox_head->addItem(QStringLiteral("AB BA"));
    ui->cBBox_head->addItem(QStringLiteral("5A A5"));

    /* check method */
    ui->cBBox_check_method->addItem(QStringLiteral("checkSum 1 byte"));
    ui->cBBox_check_method->addItem(QStringLiteral("checkSum 2 byte"));
    ui->cBBox_check_method->addItem(QStringLiteral("checkCrc 2 byte"));

    /* len meaning */
    ui->cBBox_len_meaning->addItem(QStringLiteral("the whole lenght"));
    ui->cBBox_len_meaning->addItem(QStringLiteral("len = cmd + param + check"));
}

void ProtocolGeneratorDialog::addParam()
{
    static int a= 10;
    QPushButton* pb = new QPushButton("param add");
    pb->setParent(this);
    pb->setGeometry(a,0,20,30);
    pb->show();
    a = a+25;
}
/****************************************/
/************** QTreeWidget *************/
/****************************************/
void ProtocolGeneratorDialog::initTreeWidget()
{
    /* init params */
    ui->treeW_CmdList->setColumnCount(4);
    ui->treeW_CmdList->setHeaderLabels(QStringList()<<"meaning"<<"value"<<"byte"<<"bit");

    /* connect slots */
    connect(ui->treeW_CmdList, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(on_treeWidget_doubleClicked(QTreeWidgetItem *, int)));

    /* load items */
    on_pushBtn_loadSettings_clicked();

}

/* slots */
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

void ProtocolGeneratorDialog::on_pushBtn_saveSettings_clicked()
{
    QTreeWidgetItemIterator it0(ui->treeW_CmdList);
    while (*it0) {
        qDebug() << (*it0)->text(0);
        it0++;
    }

   QSettings settings("./config/settins.txt", QSettings::IniFormat);
   settings.clear();

   /* save settings */
   settings.beginGroup(ui->treeW_CmdList->objectName());

   //QTreeWidgetItem* headeritem = ui->treeW_CmdList->headerItem();
   QTreeWidgetItemIterator it(ui->treeW_CmdList);
   int i = 1;
   while (*it) {
        /* not save items with no key*/
       if ((*it)->text(0) == NULL ) {
           it++;
          continue;
       }

       if ((*it)->childCount() != 0) {
           saveChildSettings(settings, it, ("item"+QString::number(i)));
       } else {
           settings.setValue("item"+QString::number(i) + "_meaning", (*it)->text(0));
           settings.setValue("item"+QString::number(i) + "_value", (*it)->text(1));
           settings.setValue("item"+QString::number(i) + "_byte", (*it)->text(2));
           settings.setValue("item"+QString::number(i) + "_bit", (*it)->text(3));
       }
       ++it;
       i++;
   }
   settings.endGroup();

   qDebug()<< "save settings";
}

void ProtocolGeneratorDialog::on_pushBtn_loadSettings_clicked()
{
    static int first_in = 1;
    QSettings settings("./config/settins.txt", QSettings::IniFormat);
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
    ProtocolAnalyze* pMain = (ProtocolAnalyze*) QWidget::parent();
    //pMain->generateButtons("录像时长1min");

    QVector<int> cmd_hex(2);
    cmd_hex[0] = 0xab;
    cmd_hex[1] = 0xba;

    QRect btnRect(0,30, 100, 30);
    int btn_dy = 30;
    int btn_dx = 100;

    int topCount = ui->treeW_CmdList->topLevelItemCount();

    /* open file */
    QFile btnSettins("./config/buttons_settins.txt");
    QTextStream out(&btnSettins);

    if (btnSettins.open(QFile::WriteOnly | QFile::Truncate)) {
          //out << "Result: " << qSetFieldWidth(10) << left << 3.14 << 2.7;
          out << "btnName" << " " <<"btnCmd " << " " << "btnRect " << endl;
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
        int total_len = param_len + 7;

        for (int i=0; i<total_len-2; i++) {
            cmd_hex.append(0);
        }

        if (total_len < 7) {
            qDebug() <<"total_len is too short" << total_len;
            return;
        }

        for (int j=0; j<topItem->childCount(); j++) {
            for(int i=0; i< cmd_hex.size(); i++) {
                cmd_hex[i] = 0;
            }
            QTreeWidgetItem* level1_childItem = topItem->child(j);
            int paramPosByte = level1_childItem->text(ITEM_COLUM_BYTE).toInt(NULL, 16);
            QString strBit = level1_childItem->text(ITEM_COLUM_BIT);
            QStringList strBitList = strBit.split('-', QString::SkipEmptyParts);
            int startBit = strBitList.at(1).toInt();
            int endBit = strBitList.at(0).toInt();
            int bitCount = endBit - startBit;
            if (j != 0) {
                btnRect.translate(btn_dx,0);
                btnRect.moveTop(30);
            }

            cmd_hex[0] = 0xab;
            cmd_hex[1] = 0xba;
            cmd_hex[2] = cmd_id;
            cmd_hex[3] = total_len;
            cmd_hex[4] = param_len;

            for (int k=0; k<level1_childItem->childCount(); k++) {
                QTreeWidgetItem* level2_childItem = level1_childItem->child(k);
                btnName = level1_childItem->text(ITEM_COLUM_MEANTING) + level2_childItem->text(ITEM_COLUM_MEANTING);
                int int_param = level2_childItem->text(ITEM_COLUM_VALUE).toInt(NULL, 16);
                int_param = int_param << startBit;

                cmd_hex[paramPosByte+4] = int_param;

                qDebug() << hex << cmd_hex;
                //getFullCmd(topItem, btnName, cmd_hex);
                if (k != 0) {
                    if (k%4 == 0) {
                        btnRect.moveTop(30);
                        btnRect.translate(btn_dx,0);
                    } else {
                        btnRect.translate(0, btn_dy);
                    }
                }

                uint16_t crcCheck = crc16_check(cmd_hex, cmd_hex.size()-2);
                uchar crc_h = (uchar)(crcCheck>>8);
                uchar crc_l = (uchar)(crcCheck&0xff);
                cmd_hex[cmd_hex[3]-2] = crc_h;
                cmd_hex[cmd_hex[3]-1] = crc_l;
                qDebug() << "before send" << hex << cmd_hex;

                QString str_cmdHex= pMain->hexToString(cmd_hex);
                out << btnName << "," << str_cmdHex << "," << btnRect.x() << "," << btnRect.y() << "," << btnRect.width() << "," <<btnRect.height()<<endl; //<< cmd_hex << "," << btnRect;
                pMain->generateButtons(btnName, btnRect, cmd_hex);
            }
        }
    }

    btnSettins.close();
}

/* funcs */
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

void ProtocolGeneratorDialog::getFullCmd(QTreeWidgetItem* topItem, QString & btnName, QVector<int> & cmd_hex)
{
    //QVector<int> cmd_hex(2);

    /* |head1|head2| |cmd_id| |total_len| |param_len| |param[]| |crc_h| |crc_l|*/

    cmd_hex[0] = 0xab;
    cmd_hex[1] = 0xba;

    int cmd_id = topItem->text(ITEM_COLUM_VALUE).toInt(NULL, 16);// cmd_id
    int param_len = topItem->text(ITEM_COLUM_BYTE).toInt(NULL, 16); // param_len
    int total_len = param_len + 7;

    cmd_hex.append(cmd_id);
    cmd_hex.append(total_len);
    cmd_hex.append(param_len);

    qDebug() << cmd_hex;


    /* get params */
    QTreeWidgetItem* childItem = topItem->child(0);

    int paramPosByte = childItem->text(ITEM_COLUM_BYTE).toInt(NULL, 16);
    QString strBit = childItem->text(ITEM_COLUM_BIT);
    QStringList strBitList = strBit.split('-', QString::SkipEmptyParts);
    int startBit = strBitList.at(1).toInt();
    int endBit = strBitList.at(0).toInt();
    int bitCount = endBit - startBit;

    QTreeWidgetItem* child2_Item = childItem->child(0);
    btnName = childItem->text(ITEM_COLUM_MEANTING) + child2_Item->text(ITEM_COLUM_MEANTING);
    int int_param = child2_Item->text(ITEM_COLUM_VALUE).toInt(NULL, 16);
    int_param = int_param << startBit;
    cmd_hex.append(int_param);


    qDebug() << strBitList;
    qDebug() << startBit << endBit;
    qDebug() << cmd_hex;
    qDebug() << btnName;

}
/**************************************************************************
 *  tool s
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
