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
        };

public:
    explicit ProtocolGeneratorDialog(QWidget *parent = 0);
    ~ProtocolGeneratorDialog();

private slots:
    void addParam();
    void on_treeWidget_doubleClicked(QTreeWidgetItem *item, int colum);

    void on_pushBtn_addRoot_clicked();

    void on_pushBtn_addNode_clicked();

    void on_pushBtn_deleteItem_clicked();

    void on_pushBtn_saveSettings_clicked();

    void on_pushBtn_loadSettings_clicked();

    void on_pushBtn_generate_clicked();

private:
    void fillComboBoxParams();
    void initTreeWidget();
    void saveChildSettings(QSettings &settings, QTreeWidgetItemIterator &it, QString head);
    void loadChildSettings(QSettings &settings, int size, QString head, QTreeWidgetItem* item);

    void getFullCmd(QTreeWidgetItem *topItem, QString &btnName, QVector<int> &cmd_hex);

    /** tools */
    uint16_t crc16_check(QVector<uchar>& pLcPtr, uint16_t LcLen);

    Ui::ProtocolGeneratorDialog *ui;
};

#endif // PROTOCOLGENERATORDIALOG_H
