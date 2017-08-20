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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProtocolGeneratorDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QComboBox *cBBox_check_method;
    QLabel *labl_len;
    QLabel *label_2;
    QComboBox *cBBox_head;
    QLabel *label;
    QComboBox *cBBox_len_meaning;
    QTreeWidget *treeW_CmdList;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushBtn_addRoot;
    QPushButton *pushBtn_addNode;
    QPushButton *pushBtn_deleteItem;
    QSpacerItem *verticalSpacer;
    QPushButton *pushBtn_saveSettings;
    QPushButton *pushBtn_loadSettings;
    QPushButton *pushBtn_generate;

    void setupUi(QDialog *ProtocolGeneratorDialog)
    {
        if (ProtocolGeneratorDialog->objectName().isEmpty())
            ProtocolGeneratorDialog->setObjectName(QStringLiteral("ProtocolGeneratorDialog"));
        ProtocolGeneratorDialog->resize(650, 485);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ProtocolGeneratorDialog->sizePolicy().hasHeightForWidth());
        ProtocolGeneratorDialog->setSizePolicy(sizePolicy);
        buttonBox = new QDialogButtonBox(ProtocolGeneratorDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(230, 450, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        gridLayoutWidget = new QWidget(ProtocolGeneratorDialog);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 511, 51));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        cBBox_check_method = new QComboBox(gridLayoutWidget);
        cBBox_check_method->setObjectName(QStringLiteral("cBBox_check_method"));

        gridLayout->addWidget(cBBox_check_method, 1, 1, 1, 1);

        labl_len = new QLabel(gridLayoutWidget);
        labl_len->setObjectName(QStringLiteral("labl_len"));

        gridLayout->addWidget(labl_len, 0, 2, 1, 1);

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

        treeW_CmdList = new QTreeWidget(ProtocolGeneratorDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeW_CmdList->setHeaderItem(__qtreewidgetitem);
        treeW_CmdList->setObjectName(QStringLiteral("treeW_CmdList"));
        treeW_CmdList->setGeometry(QRect(10, 90, 511, 351));
        verticalLayoutWidget = new QWidget(ProtocolGeneratorDialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(540, 90, 82, 191));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushBtn_addRoot = new QPushButton(verticalLayoutWidget);
        pushBtn_addRoot->setObjectName(QStringLiteral("pushBtn_addRoot"));

        verticalLayout->addWidget(pushBtn_addRoot);

        pushBtn_addNode = new QPushButton(verticalLayoutWidget);
        pushBtn_addNode->setObjectName(QStringLiteral("pushBtn_addNode"));

        verticalLayout->addWidget(pushBtn_addNode);

        pushBtn_deleteItem = new QPushButton(verticalLayoutWidget);
        pushBtn_deleteItem->setObjectName(QStringLiteral("pushBtn_deleteItem"));

        verticalLayout->addWidget(pushBtn_deleteItem);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushBtn_saveSettings = new QPushButton(verticalLayoutWidget);
        pushBtn_saveSettings->setObjectName(QStringLiteral("pushBtn_saveSettings"));

        verticalLayout->addWidget(pushBtn_saveSettings);

        pushBtn_loadSettings = new QPushButton(verticalLayoutWidget);
        pushBtn_loadSettings->setObjectName(QStringLiteral("pushBtn_loadSettings"));

        verticalLayout->addWidget(pushBtn_loadSettings);

        pushBtn_generate = new QPushButton(ProtocolGeneratorDialog);
        pushBtn_generate->setObjectName(QStringLiteral("pushBtn_generate"));
        pushBtn_generate->setGeometry(QRect(540, 420, 75, 23));

        retranslateUi(ProtocolGeneratorDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ProtocolGeneratorDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ProtocolGeneratorDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ProtocolGeneratorDialog);
    } // setupUi

    void retranslateUi(QDialog *ProtocolGeneratorDialog)
    {
        ProtocolGeneratorDialog->setWindowTitle(QApplication::translate("ProtocolGeneratorDialog", "Dialog", 0));
        labl_len->setText(QApplication::translate("ProtocolGeneratorDialog", "len", 0));
        label_2->setText(QApplication::translate("ProtocolGeneratorDialog", "check_method", 0));
        label->setText(QApplication::translate("ProtocolGeneratorDialog", "head", 0));
        pushBtn_addRoot->setText(QApplication::translate("ProtocolGeneratorDialog", "add root", 0));
        pushBtn_addNode->setText(QApplication::translate("ProtocolGeneratorDialog", "add node", 0));
        pushBtn_deleteItem->setText(QApplication::translate("ProtocolGeneratorDialog", "delete", 0));
        pushBtn_saveSettings->setText(QApplication::translate("ProtocolGeneratorDialog", "save", 0));
        pushBtn_loadSettings->setText(QApplication::translate("ProtocolGeneratorDialog", "load", 0));
        pushBtn_generate->setText(QApplication::translate("ProtocolGeneratorDialog", "generate", 0));
    } // retranslateUi

};

namespace Ui {
    class ProtocolGeneratorDialog: public Ui_ProtocolGeneratorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROTOCOLGENERATORDIALOG_H
