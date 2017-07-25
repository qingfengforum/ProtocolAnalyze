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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProtocolGeneratorDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QComboBox *cBBox_check_method;
    QLabel *label_8;
    QLabel *label_2;
    QComboBox *cBBox_head;
    QLabel *label;
    QComboBox *cBBox_len_meaning;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QLabel *label_5;
    QLineEdit *lineEdit_3;
    QLabel *label_6;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLabel *label_7;

    void setupUi(QDialog *ProtocolGeneratorDialog)
    {
        if (ProtocolGeneratorDialog->objectName().isEmpty())
            ProtocolGeneratorDialog->setObjectName(QStringLiteral("ProtocolGeneratorDialog"));
        ProtocolGeneratorDialog->resize(523, 357);
        buttonBox = new QDialogButtonBox(ProtocolGeneratorDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(150, 310, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        gridLayoutWidget = new QWidget(ProtocolGeneratorDialog);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 511, 84));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        cBBox_check_method = new QComboBox(gridLayoutWidget);
        cBBox_check_method->setObjectName(QStringLiteral("cBBox_check_method"));

        gridLayout->addWidget(cBBox_check_method, 1, 1, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 0, 2, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        cBBox_head = new QComboBox(gridLayoutWidget);
        cBBox_head->setObjectName(QStringLiteral("cBBox_head"));

        gridLayout->addWidget(cBBox_head, 1, 0, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cBBox_len_meaning = new QComboBox(gridLayoutWidget);
        cBBox_len_meaning->setObjectName(QStringLiteral("cBBox_len_meaning"));

        gridLayout->addWidget(cBBox_len_meaning, 1, 2, 1, 1);

        label_3 = new QLabel(ProtocolGeneratorDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 100, 54, 12));
        lineEdit = new QLineEdit(ProtocolGeneratorDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 120, 51, 16));
        label_4 = new QLabel(ProtocolGeneratorDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(80, 100, 54, 12));
        lineEdit_2 = new QLineEdit(ProtocolGeneratorDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(80, 120, 51, 16));
        label_5 = new QLabel(ProtocolGeneratorDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(150, 100, 54, 12));
        lineEdit_3 = new QLineEdit(ProtocolGeneratorDialog);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(150, 120, 51, 16));
        label_6 = new QLabel(ProtocolGeneratorDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(240, 100, 54, 12));
        lineEdit_4 = new QLineEdit(ProtocolGeneratorDialog);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(240, 120, 51, 16));
        lineEdit_5 = new QLineEdit(ProtocolGeneratorDialog);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(310, 120, 51, 16));
        label_7 = new QLabel(ProtocolGeneratorDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(310, 100, 54, 12));

        retranslateUi(ProtocolGeneratorDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ProtocolGeneratorDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ProtocolGeneratorDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ProtocolGeneratorDialog);
    } // setupUi

    void retranslateUi(QDialog *ProtocolGeneratorDialog)
    {
        ProtocolGeneratorDialog->setWindowTitle(QApplication::translate("ProtocolGeneratorDialog", "Dialog", 0));
        label_8->setText(QApplication::translate("ProtocolGeneratorDialog", "len", 0));
        label_2->setText(QApplication::translate("ProtocolGeneratorDialog", "check_method", 0));
        label->setText(QApplication::translate("ProtocolGeneratorDialog", "head", 0));
        label_3->setText(QApplication::translate("ProtocolGeneratorDialog", "cmd", 0));
        label_4->setText(QApplication::translate("ProtocolGeneratorDialog", "param_len", 0));
        label_5->setText(QApplication::translate("ProtocolGeneratorDialog", "len", 0));
        label_6->setText(QApplication::translate("ProtocolGeneratorDialog", "param 1", 0));
        label_7->setText(QApplication::translate("ProtocolGeneratorDialog", "param 2", 0));
    } // retranslateUi

};

namespace Ui {
    class ProtocolGeneratorDialog: public Ui_ProtocolGeneratorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROTOCOLGENERATORDIALOG_H
