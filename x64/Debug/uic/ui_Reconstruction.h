/********************************************************************************
** Form generated from reading UI file 'Reconstruction.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECONSTRUCTION_H
#define UI_RECONSTRUCTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReconstructionClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ReconstructionClass)
    {
        if (ReconstructionClass->objectName().isEmpty())
            ReconstructionClass->setObjectName(QString::fromUtf8("ReconstructionClass"));
        ReconstructionClass->resize(600, 400);
        menuBar = new QMenuBar(ReconstructionClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        ReconstructionClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ReconstructionClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ReconstructionClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ReconstructionClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ReconstructionClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ReconstructionClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ReconstructionClass->setStatusBar(statusBar);

        retranslateUi(ReconstructionClass);

        QMetaObject::connectSlotsByName(ReconstructionClass);
    } // setupUi

    void retranslateUi(QMainWindow *ReconstructionClass)
    {
        ReconstructionClass->setWindowTitle(QApplication::translate("ReconstructionClass", "Reconstruction", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReconstructionClass: public Ui_ReconstructionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECONSTRUCTION_H
