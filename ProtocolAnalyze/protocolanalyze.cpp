#include "protocolanalyze.h"
#include "ui_protocolanalyze.h"

ProtocolAnalyze::ProtocolAnalyze(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProtocolAnalyze)
{
    ui->setupUi(this);
}

ProtocolAnalyze::~ProtocolAnalyze()
{
    delete ui;
}
