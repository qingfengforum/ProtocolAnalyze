#ifndef PROTOCOLGENERATORDIALOG_H
#define PROTOCOLGENERATORDIALOG_H

#include <QDialog>

namespace Ui {
class ProtocolGeneratorDialog;
}

class ProtocolGeneratorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProtocolGeneratorDialog(QWidget *parent = 0);
    ~ProtocolGeneratorDialog();

private:
    Ui::ProtocolGeneratorDialog *ui;
};

#endif // PROTOCOLGENERATORDIALOG_H