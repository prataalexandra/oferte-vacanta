#pragma once


#ifndef UI_QT_OFERTA_H
#define UI_QT_OFERTA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QT_OFERTAClass
{
public:
    QMenuBar* menuBar;
    QToolBar* mainToolBar;
    QWidget* centralWidget;
    QStatusBar* statusBar;

    void setupUi(QMainWindow* QT_OFERTAClass)
    {
        if (QT_OFERTAClass->objectName().isEmpty())
            QT_OFERTAClass->setObjectName("QT_OFERTAClass");
        QT_OFERTAClass->resize(600, 400);
        menuBar = new QMenuBar(QT_OFERTAClass);
        menuBar->setObjectName("menuBar");
        QT_OFERTAClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QT_OFERTAClass);
        mainToolBar->setObjectName("mainToolBar");
        QT_OFERTAClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QT_OFERTAClass);
        centralWidget->setObjectName("centralWidget");
        QT_OFERTAClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QT_OFERTAClass);
        statusBar->setObjectName("statusBar");
        QT_OFERTAClass->setStatusBar(statusBar);

        retranslateUi(QT_OFERTAClass);

        QMetaObject::connectSlotsByName(QT_OFERTAClass);
    } // setupUi

    void retranslateUi(QMainWindow* QT_OFERTAClass)
    {
        QT_OFERTAClass->setWindowTitle(QCoreApplication::translate("QT_OFERTAClass", "QT_OFERTA", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QT_OFERTAClass : public Ui_QT_OFERTAClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_OFERTA_H
