#ifndef PROTOCOLANALYZE_H
#define PROTOCOLANALYZE_H

#include <QMainWindow>

namespace Ui {
class ProtocolAnalyze;
}

class ProtocolAnalyze : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProtocolAnalyze(QWidget *parent = 0);
    ~ProtocolAnalyze();

private:
    Ui::ProtocolAnalyze *ui;
};

#endif // PROTOCOLANALYZE_H
