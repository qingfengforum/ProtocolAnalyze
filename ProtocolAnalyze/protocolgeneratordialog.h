#ifndef PROTOCOLGENERATORDIALOG_H
#define PROTOCOLGENERATORDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include <QSettings>
#include <protocolanalyze.h>

namespace Ui {
class ProtocolGeneratorDialog;
}

class ProtocolGeneratorDialog : public QDialog
{
    Q_OBJECT
private:
        enum _TREE_COLUMS_MEANINGS_e_{
            ITEM_COLUM_MEANTING = 0,
            ITEM_COLUM_VALUE = 1,
            ITEM_COLUM_BYTE = 2,
            ITEM_COLUM_BIT = 3,
            ITEM_COLUM_NUM,
        };

        enum _CMD_HEAD_TYPE_e_ {
            CMD_HEAD_AB_BA,
            CMD_HEAD_5A_A5,
        };

        enum _CMD_CHECK_TYPE_e_ {
            CMD_CHECK_TYPE_CRC_2BYTE,
            CMD_CHECK_TYPE_CHECK_SUM_1BYTE,
            CMD_CHECK_TYPE_CHECK_SUM_2BYTE,
        };

        enum _GEN_TYPE_e_ {
            GEN_TYPE_GEN_BUTTONS,
            GEN_TYPE_GEN_RCV_ANALYZOR,
        };
public:
    explicit ProtocolGeneratorDialog(QWidget *parent = 0);
    ~ProtocolGeneratorDialog();

     void initDialogGenRevAnalyzor();

private slots:
    void on_treeWidget_doubleClicked(QTreeWidgetItem *item, int colum);
    void on_pushBtn_addRoot_clicked();
    void on_pushBtn_addNode_clicked();
    void on_pushBtn_deleteItem_clicked();

    /* save and load treeWidget settings */
    void on_pushBtn_saveSettings_clicked();
    void on_pushBtn_loadSettings_clicked();

    /* generate push buttons */
    void on_pushBtn_generate_clicked();

public:
    uint16_t crc16_check(QVector<uchar>& pLcPtr, uint16_t LcLen);

private:
    void fillComboBoxParams();
    void initTreeWidget();
    void saveChildSettings(QSettings &settings, QTreeWidgetItemIterator &it, QString head);
    void loadChildSettings(QSettings &settings, int size, QString head, QTreeWidgetItem* item);

    void generatePushButtons();
    void generateRcvAnalyzor();


private:
    Ui::ProtocolGeneratorDialog *ui;
    QString configFilePath;
    uint genType;
};

#endif // PROTOCOLGENERATORDIALOG_H
