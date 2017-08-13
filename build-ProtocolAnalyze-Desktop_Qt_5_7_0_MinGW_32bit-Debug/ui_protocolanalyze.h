/********************************************************************************
** Form generated from reading UI file 'protocolanalyze.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROTOCOLANALYZE_H
#define UI_PROTOCOLANALYZE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProtocolAnalyze
{
public:
    QAction *actionProtocol_generator;
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pB_refreshPortInfo;
    QComboBox *serialPortInfoListBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *baudRateBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QComboBox *dataBitsBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *parityBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QComboBox *stopBitsBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QComboBox *flowControlBox;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *actionDisconnect;
    QPushButton *actionConnect;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *vtL_portOutPutInfo;
    QTabWidget *tabWdgt_btns;
    QWidget *tab;
    QWidget *tab_2;
    QPushButton *pushBtn_saveBtnSettings;
    QPushButton *pushBtn_loadBtnSettings;
    QPushButton *pushBtn_clear;
    QPushButton *pushBtn_test;
    QMenuBar *menuBar;
    QMenu *menuTools;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProtocolAnalyze)
    {
        if (ProtocolAnalyze->objectName().isEmpty())
            ProtocolAnalyze->setObjectName(QStringLiteral("ProtocolAnalyze"));
        ProtocolAnalyze->resize(799, 674);
        actionProtocol_generator = new QAction(ProtocolAnalyze);
        actionProtocol_generator->setObjectName(QStringLiteral("actionProtocol_generator"));
        centralWidget = new QWidget(ProtocolAnalyze);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 211, 261));
        verticalLayoutWidget = new QWidget(groupBox);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 20, 181, 221));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        pB_refreshPortInfo = new QPushButton(verticalLayoutWidget);
        pB_refreshPortInfo->setObjectName(QStringLiteral("pB_refreshPortInfo"));

        horizontalLayout_7->addWidget(pB_refreshPortInfo);

        serialPortInfoListBox = new QComboBox(verticalLayoutWidget);
        serialPortInfoListBox->setObjectName(QStringLiteral("serialPortInfoListBox"));

        horizontalLayout_7->addWidget(serialPortInfoListBox);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        baudRateBox = new QComboBox(verticalLayoutWidget);
        baudRateBox->setObjectName(QStringLiteral("baudRateBox"));

        horizontalLayout_3->addWidget(baudRateBox);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_5->addWidget(label_2);

        dataBitsBox = new QComboBox(verticalLayoutWidget);
        dataBitsBox->setObjectName(QStringLiteral("dataBitsBox"));

        horizontalLayout_5->addWidget(dataBitsBox);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        parityBox = new QComboBox(verticalLayoutWidget);
        parityBox->setObjectName(QStringLiteral("parityBox"));

        horizontalLayout_4->addWidget(parityBox);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_5 = new QLabel(verticalLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        stopBitsBox = new QComboBox(verticalLayoutWidget);
        stopBitsBox->setObjectName(QStringLiteral("stopBitsBox"));

        horizontalLayout_2->addWidget(stopBitsBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout->addWidget(label_6);

        flowControlBox = new QComboBox(verticalLayoutWidget);
        flowControlBox->setObjectName(QStringLiteral("flowControlBox"));

        horizontalLayout->addWidget(flowControlBox);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        actionDisconnect = new QPushButton(verticalLayoutWidget);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));

        horizontalLayout_6->addWidget(actionDisconnect);

        actionConnect = new QPushButton(verticalLayoutWidget);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));

        horizontalLayout_6->addWidget(actionConnect);


        verticalLayout_2->addLayout(horizontalLayout_6);


        verticalLayout->addLayout(verticalLayout_2);

        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(220, 10, 571, 351));
        vtL_portOutPutInfo = new QVBoxLayout(verticalLayoutWidget_2);
        vtL_portOutPutInfo->setSpacing(6);
        vtL_portOutPutInfo->setContentsMargins(11, 11, 11, 11);
        vtL_portOutPutInfo->setObjectName(QStringLiteral("vtL_portOutPutInfo"));
        vtL_portOutPutInfo->setContentsMargins(0, 0, 0, 0);
        tabWdgt_btns = new QTabWidget(centralWidget);
        tabWdgt_btns->setObjectName(QStringLiteral("tabWdgt_btns"));
        tabWdgt_btns->setGeometry(QRect(0, 430, 791, 181));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWdgt_btns->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWdgt_btns->addTab(tab_2, QString());
        pushBtn_saveBtnSettings = new QPushButton(centralWidget);
        pushBtn_saveBtnSettings->setObjectName(QStringLiteral("pushBtn_saveBtnSettings"));
        pushBtn_saveBtnSettings->setGeometry(QRect(0, 400, 75, 23));
        pushBtn_loadBtnSettings = new QPushButton(centralWidget);
        pushBtn_loadBtnSettings->setObjectName(QStringLiteral("pushBtn_loadBtnSettings"));
        pushBtn_loadBtnSettings->setGeometry(QRect(80, 400, 75, 23));
        pushBtn_clear = new QPushButton(centralWidget);
        pushBtn_clear->setObjectName(QStringLiteral("pushBtn_clear"));
        pushBtn_clear->setGeometry(QRect(140, 340, 75, 23));
        pushBtn_test = new QPushButton(centralWidget);
        pushBtn_test->setObjectName(QStringLiteral("pushBtn_test"));
        pushBtn_test->setGeometry(QRect(0, 340, 75, 23));
        ProtocolAnalyze->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ProtocolAnalyze);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 799, 23));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        ProtocolAnalyze->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ProtocolAnalyze);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ProtocolAnalyze->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ProtocolAnalyze);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ProtocolAnalyze->setStatusBar(statusBar);

        menuBar->addAction(menuTools->menuAction());
        menuTools->addAction(actionProtocol_generator);

        retranslateUi(ProtocolAnalyze);

        QMetaObject::connectSlotsByName(ProtocolAnalyze);
    } // setupUi

    void retranslateUi(QMainWindow *ProtocolAnalyze)
    {
        ProtocolAnalyze->setWindowTitle(QApplication::translate("ProtocolAnalyze", "ProtocolAnalyze", 0));
        actionProtocol_generator->setText(QApplication::translate("ProtocolAnalyze", "protocol generator", 0));
        groupBox->setTitle(QApplication::translate("ProtocolAnalyze", "Serail Param", 0));
        pB_refreshPortInfo->setText(QApplication::translate("ProtocolAnalyze", "\345\210\267\346\226\260", 0));
        label_3->setText(QApplication::translate("ProtocolAnalyze", "BaudTate:", 0));
        label_2->setText(QApplication::translate("ProtocolAnalyze", "Data bits:", 0));
        dataBitsBox->setCurrentText(QString());
        label_4->setText(QApplication::translate("ProtocolAnalyze", "Parity:", 0));
        label_5->setText(QApplication::translate("ProtocolAnalyze", "Stop bits:", 0));
        label_6->setText(QApplication::translate("ProtocolAnalyze", "Flow control:", 0));
        actionDisconnect->setText(QApplication::translate("ProtocolAnalyze", "\346\226\255\345\274\200", 0));
        actionConnect->setText(QApplication::translate("ProtocolAnalyze", "\350\277\236\346\216\245", 0));
        tabWdgt_btns->setTabText(tabWdgt_btns->indexOf(tab), QApplication::translate("ProtocolAnalyze", "Tab 1", 0));
        tabWdgt_btns->setTabText(tabWdgt_btns->indexOf(tab_2), QApplication::translate("ProtocolAnalyze", "Tab 2", 0));
        pushBtn_saveBtnSettings->setText(QApplication::translate("ProtocolAnalyze", "save", 0));
        pushBtn_loadBtnSettings->setText(QApplication::translate("ProtocolAnalyze", "load", 0));
        pushBtn_clear->setText(QApplication::translate("ProtocolAnalyze", "clear", 0));
        pushBtn_test->setText(QApplication::translate("ProtocolAnalyze", "test", 0));
        menuTools->setTitle(QApplication::translate("ProtocolAnalyze", "tools", 0));
    } // retranslateUi

};

namespace Ui {
    class ProtocolAnalyze: public Ui_ProtocolAnalyze {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROTOCOLANALYZE_H
