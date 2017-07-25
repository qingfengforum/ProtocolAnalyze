/********************************************************************************
** Form generated from reading UI file 'protocolgeneratordialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROTOCOLGENERATORDIALOG_H
#define UI_PROTOCOLGENERATORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ProtocolGeneratorDialog
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ProtocolGeneratorDialog)
    {
        if (ProtocolGeneratorDialog->objectName().isEmpty())
            ProtocolGeneratorDialog->setObjectName(QStringLiteral("ProtocolGeneratorDialog"));
        ProtocolGeneratorDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(ProtocolGeneratorDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(40, 260, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(ProtocolGeneratorDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ProtocolGeneratorDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ProtocolGeneratorDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ProtocolGeneratorDialog);
    } // setupUi

    void retranslateUi(QDialog *ProtocolGeneratorDialog)
    {
        ProtocolGeneratorDialog->setWindowTitle(QApplication::translate("ProtocolGeneratorDialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class ProtocolGeneratorDialog: public Ui_ProtocolGeneratorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROTOCOLGENERATORDIALOG_H
