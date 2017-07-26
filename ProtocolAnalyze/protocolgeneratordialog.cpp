#include "protocolgeneratordialog.h"
#include "ui_protocolgeneratordialog.h"

ProtocolGeneratorDialog::ProtocolGeneratorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProtocolGeneratorDialog)
{
    ui->setupUi(this);

    /* init */
    fillComboBoxParams();

    /* connect */
    connect(ui->pB_add_param, QPushButton::clicked, this, &ProtocolGeneratorDialog::addParam);
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
