#include "protocolgeneratordialog.h"
#include "ui_protocolgeneratordialog.h"

#include <QDebug>


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
    int topCount = ui->treeW_CmdList->topLevelItemCount();
    QVector<int> params(8);
    for (int i=0; i<topCount; i++) {
        QTreeWidgetItem* topItem= ui->treeW_CmdList->topLevelItem(i);
        QString totalCmd = "";
        QString head = "AB BA ";
        QString cmd = topItem->text(1) + " ";
        QString totalLen = QString::number((topItem->text(2).toInt(NULL, 16) + 7), 16) + " ";
        QString paramLen = topItem->text(2) + " ";
        QString crc = "crc_h crc_l";

        /* get params */
        QTreeWidgetItem* childItem = topItem->child(0);
        int paramPos = childItem->text(2).toInt(NULL, 16);

        QString bitStr = childItem->text(3);
        QString endBitStr = "";
        QString startBitStr = "";
        for(int i=0; i<bitStr.length(); i++) {
            if (bitStr[i] == '-') {
                for(int j=i+1; j<bitStr.length(); j++) {
                    startBitStr = startBitStr + bitStr[j];
                }
                break;
            } else {
                endBitStr = endBitStr + bitStr[i];
            }
        }
        int bitCount = endBitStr.toInt() - startBitStr.toInt();
        qDebug() << "endbit :" << endBitStr;
        qDebug() << "startBit :" << startBitStr;
        qDebug() << "bitCount :" << bitCount;

        QTreeWidgetItem* child2_Item = childItem->child(0);
        int param_int = child2_Item->text(1).toInt(NULL, 16);
        params[paramPos-1] = param_int << startBitStr.toInt();
        QString param ="";
        for (int i=0; i<params.count(); i++) {
            param += QString::number(params[i],16);
            param += " ";
        }

        totalCmd = head + cmd + totalLen + paramLen + param + crc;
        qDebug() << "totalCmd : " << totalCmd;
    }
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


