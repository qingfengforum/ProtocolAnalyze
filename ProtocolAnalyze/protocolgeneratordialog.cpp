#include "protocolgeneratordialog.h"
#include "ui_protocolgeneratordialog.h"

ProtocolGeneratorDialog::ProtocolGeneratorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProtocolGeneratorDialog)
{
    ui->setupUi(this);
}

ProtocolGeneratorDialog::~ProtocolGeneratorDialog()
{
    delete ui;
}
