#include "protocolanalyze.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProtocolAnalyze w;
    w.show();

    return a.exec();
}
