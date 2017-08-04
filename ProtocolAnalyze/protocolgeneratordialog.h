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

    Ui::ProtocolGeneratorDialog *ui;
};

#endif // PROTOCOLGENERATORDIALOG_H
