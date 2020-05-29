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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_ReconstructionClass
{
public:
    QAction *actioncamera;
    QAction *actionstyle;
    QWidget *centralWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label_2;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QTextBrowser *textBrowser;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_8;
    QTextBrowser *textBrowser_3;
    QTextBrowser *textBrowser_2;
    QTextBrowser *textBrowser_4;
    QGroupBox *groupBox_2;
    QWidget *gridLayoutWidget_6;
    QGridLayout *gridLayout_6;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QLabel *label_15;
    QLabel *label_22;
    QSpinBox *spinBox_3;
    QLabel *label_16;
    QGroupBox *groupBox_5;
    QLabel *label_11;
    QGraphicsView *graphicsView_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QGroupBox *groupBox_3;
    QTreeView *treeView;
    QWidget *page_2;
    QLabel *label_3;
    QGroupBox *groupBox_6;
    QLabel *label_21;
    QGraphicsView *graphicsView_2;
    QPushButton *pushButton_4;
    QLineEdit *lineEdit;
    QLabel *label_18;
    QGroupBox *groupBox_7;
    QTextBrowser *textBrowser_8;
    QGroupBox *groupBox_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_17;
    QPushButton *pushButton_19;
    QWidget *page_3;
    QGroupBox *groupBox_4;
    QLabel *label_12;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QLabel *label_14;
    QPushButton *pushButton_16;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QVTKWidget *qvtkWidget;
    QLabel *label_9;
    QPushButton *pushButton_18;
    QWidget *widget;
    QLabel *label;
    QLabel *label_4;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *ReconstructionClass)
    {
        if (ReconstructionClass->objectName().isEmpty())
            ReconstructionClass->setObjectName(QString::fromUtf8("ReconstructionClass"));
        ReconstructionClass->resize(1240, 680);
        ReconstructionClass->setMinimumSize(QSize(1240, 680));
        ReconstructionClass->setMaximumSize(QSize(1240, 680));
        actioncamera = new QAction(ReconstructionClass);
        actioncamera->setObjectName(QString::fromUtf8("actioncamera"));
        actionstyle = new QAction(ReconstructionClass);
        actionstyle->setObjectName(QString::fromUtf8("actionstyle"));
        centralWidget = new QWidget(ReconstructionClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(1240, 680));
        centralWidget->setMaximumSize(QSize(1240, 680));
        centralWidget->setAutoFillBackground(false);
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(239, -4, 1001, 651));
        stackedWidget->setAutoFillBackground(true);
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        label_2 = new QLabel(page);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(310, 20, 81, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe Devanagari"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        groupBox = new QGroupBox(page);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(690, 430, 291, 201));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(10);
        groupBox->setFont(font1);
        groupBox->setAlignment(Qt::AlignCenter);
        groupBox->setFlat(false);
        gridLayoutWidget_2 = new QWidget(groupBox);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 20, 281, 181));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetMinAndMaxSize);
        gridLayout_2->setHorizontalSpacing(7);
        gridLayout_2->setContentsMargins(10, 10, 10, 10);
        textBrowser = new QTextBrowser(gridLayoutWidget_2);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setMaximumSize(QSize(250, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Adobe Devanagari"));
        font2.setPointSize(10);
        textBrowser->setFont(font2);
        textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout_2->addWidget(textBrowser, 0, 1, 1, 1);

        label_7 = new QLabel(gridLayoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font2);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_7, 2, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font2);
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_6, 1, 0, 1, 1);

        label_5 = new QLabel(gridLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        label_8 = new QLabel(gridLayoutWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font2);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_8, 3, 0, 1, 1);

        textBrowser_3 = new QTextBrowser(gridLayoutWidget_2);
        textBrowser_3->setObjectName(QString::fromUtf8("textBrowser_3"));
        textBrowser_3->setMaximumSize(QSize(250, 31));
        textBrowser_3->setFont(font2);
        textBrowser_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout_2->addWidget(textBrowser_3, 2, 1, 1, 1);

        textBrowser_2 = new QTextBrowser(gridLayoutWidget_2);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setMaximumSize(QSize(250, 31));
        textBrowser_2->setFont(font2);
        textBrowser_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout_2->addWidget(textBrowser_2, 1, 1, 1, 1);

        textBrowser_4 = new QTextBrowser(gridLayoutWidget_2);
        textBrowser_4->setObjectName(QString::fromUtf8("textBrowser_4"));
        textBrowser_4->setMaximumSize(QSize(250, 31));
        textBrowser_4->setFont(font2);
        textBrowser_4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textBrowser_4->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout_2->addWidget(textBrowser_4, 3, 1, 1, 1);

        groupBox_2 = new QGroupBox(page);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(690, 30, 291, 151));
        groupBox_2->setFont(font1);
        groupBox_2->setAlignment(Qt::AlignCenter);
        gridLayoutWidget_6 = new QWidget(groupBox_2);
        gridLayoutWidget_6->setObjectName(QString::fromUtf8("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(30, 20, 231, 121));
        gridLayout_6 = new QGridLayout(gridLayoutWidget_6);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setSizeConstraint(QLayout::SetMinAndMaxSize);
        gridLayout_6->setHorizontalSpacing(7);
        gridLayout_6->setContentsMargins(10, 10, 10, 10);
        spinBox = new QSpinBox(gridLayoutWidget_6);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        gridLayout_6->addWidget(spinBox, 0, 2, 1, 1);

        spinBox_2 = new QSpinBox(gridLayoutWidget_6);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));

        gridLayout_6->addWidget(spinBox_2, 1, 2, 1, 1);

        label_15 = new QLabel(gridLayoutWidget_6);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font3.setPointSize(9);
        label_15->setFont(font3);
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_15, 1, 0, 1, 1);

        label_22 = new QLabel(gridLayoutWidget_6);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        label_22->setFont(font4);
        label_22->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_22, 0, 0, 1, 1);

        spinBox_3 = new QSpinBox(gridLayoutWidget_6);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));

        gridLayout_6->addWidget(spinBox_3, 2, 2, 1, 1);

        label_16 = new QLabel(gridLayoutWidget_6);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font3);
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_16, 2, 0, 1, 1);

        groupBox_5 = new QGroupBox(page);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(30, 40, 640, 512));
        groupBox_5->setFlat(false);
        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(0, 0, 640, 512));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Adobe Devanagari"));
        font5.setPointSize(16);
        label_11->setFont(font5);
        label_11->setAlignment(Qt::AlignCenter);
        graphicsView_3 = new QGraphicsView(groupBox_5);
        graphicsView_3->setObjectName(QString::fromUtf8("graphicsView_3"));
        graphicsView_3->setGeometry(QRect(0, 0, 640, 511));
        graphicsView_3->raise();
        label_11->raise();
        pushButton_5 = new QPushButton(page);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(50, 580, 120, 51));
        pushButton_5->setMinimumSize(QSize(120, 0));
        pushButton_5->setMaximumSize(QSize(110, 16777215));
        pushButton_5->setFont(font3);
        pushButton_6 = new QPushButton(page);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(210, 580, 120, 51));
        pushButton_6->setMinimumSize(QSize(120, 0));
        pushButton_6->setMaximumSize(QSize(110, 16777215));
        pushButton_6->setFont(font3);
        pushButton_7 = new QPushButton(page);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(370, 580, 120, 51));
        pushButton_7->setMinimumSize(QSize(120, 0));
        pushButton_7->setMaximumSize(QSize(110, 16777215));
        pushButton_7->setFont(font3);
        pushButton_8 = new QPushButton(page);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(530, 580, 120, 51));
        pushButton_8->setMinimumSize(QSize(120, 0));
        pushButton_8->setMaximumSize(QSize(120, 16777215));
        pushButton_8->setFont(font3);
        groupBox_3 = new QGroupBox(page);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(690, 200, 291, 231));
        groupBox_3->setFont(font1);
        groupBox_3->setAlignment(Qt::AlignCenter);
        treeView = new QTreeView(groupBox_3);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(10, 20, 271, 181));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        label_3 = new QLabel(page_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(310, 30, 81, 16));
        label_3->setFont(font);
        groupBox_6 = new QGroupBox(page_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(30, 60, 640, 512));
        label_21 = new QLabel(groupBox_6);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(0, 0, 640, 512));
        label_21->setFont(font5);
        label_21->setAlignment(Qt::AlignCenter);
        graphicsView_2 = new QGraphicsView(groupBox_6);
        graphicsView_2->setObjectName(QString::fromUtf8("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(0, 0, 640, 512));
        graphicsView_2->raise();
        label_21->raise();
        pushButton_4 = new QPushButton(page_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(550, 590, 120, 41));
        pushButton_4->setMinimumSize(QSize(120, 0));
        pushButton_4->setFont(font4);
        lineEdit = new QLineEdit(page_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(150, 590, 381, 41));
        label_18 = new QLabel(page_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(30, 590, 111, 40));
        label_18->setMinimumSize(QSize(0, 40));
        label_18->setMaximumSize(QSize(16777215, 40));
        label_18->setFont(font3);
        label_18->setAlignment(Qt::AlignCenter);
        groupBox_7 = new QGroupBox(page_2);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(700, 50, 281, 291));
        groupBox_7->setFont(font1);
        groupBox_7->setAlignment(Qt::AlignCenter);
        textBrowser_8 = new QTextBrowser(groupBox_7);
        textBrowser_8->setObjectName(QString::fromUtf8("textBrowser_8"));
        textBrowser_8->setGeometry(QRect(10, 20, 261, 261));
        QFont font6;
        font6.setPointSize(9);
        textBrowser_8->setFont(font6);
        groupBox_8 = new QGroupBox(page_2);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(710, 350, 261, 281));
        groupBox_8->setFont(font1);
        groupBox_8->setAlignment(Qt::AlignCenter);
        pushButton_9 = new QPushButton(groupBox_8);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(70, 80, 120, 51));
        pushButton_9->setMinimumSize(QSize(120, 0));
        pushButton_9->setFont(font4);
        pushButton_10 = new QPushButton(groupBox_8);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(70, 150, 120, 51));
        pushButton_10->setMinimumSize(QSize(120, 0));
        pushButton_10->setFont(font4);
        pushButton_17 = new QPushButton(groupBox_8);
        pushButton_17->setObjectName(QString::fromUtf8("pushButton_17"));
        pushButton_17->setGeometry(QRect(70, 220, 120, 51));
        pushButton_17->setMinimumSize(QSize(120, 0));
        pushButton_17->setFont(font4);
        pushButton_19 = new QPushButton(groupBox_8);
        pushButton_19->setObjectName(QString::fromUtf8("pushButton_19"));
        pushButton_19->setGeometry(QRect(70, 10, 120, 51));
        pushButton_19->setMinimumSize(QSize(120, 0));
        pushButton_19->setFont(font4);
        stackedWidget->addWidget(page_2);
        groupBox_8->raise();
        label_3->raise();
        groupBox_6->raise();
        pushButton_4->raise();
        lineEdit->raise();
        label_18->raise();
        groupBox_7->raise();
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        groupBox_4 = new QGroupBox(page_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(785, 70, 201, 171));
        groupBox_4->setFont(font4);
        groupBox_4->setAlignment(Qt::AlignCenter);
        groupBox_4->setFlat(false);
        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(20, 50, 61, 16));
        pushButton_11 = new QPushButton(groupBox_4);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(70, 100, 51, 31));
        pushButton_12 = new QPushButton(groupBox_4);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(140, 100, 51, 31));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 110, 51, 16));
        pushButton_16 = new QPushButton(groupBox_4);
        pushButton_16->setObjectName(QString::fromUtf8("pushButton_16"));
        pushButton_16->setGeometry(QRect(100, 40, 51, 31));
        pushButton_13 = new QPushButton(page_3);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(815, 290, 141, 41));
        pushButton_13->setFont(font4);
        pushButton_14 = new QPushButton(page_3);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        pushButton_14->setGeometry(QRect(815, 380, 141, 41));
        pushButton_14->setFont(font4);
        pushButton_15 = new QPushButton(page_3);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));
        pushButton_15->setGeometry(QRect(815, 470, 141, 41));
        pushButton_15->setFont(font4);
        qvtkWidget = new QVTKWidget(page_3);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(30, 20, 741, 621));
        label_9 = new QLabel(page_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 20, 741, 611));
        QFont font7;
        font7.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font7.setPointSize(18);
        label_9->setFont(font7);
        label_9->setStyleSheet(QString::fromUtf8(""));
        pushButton_18 = new QPushButton(page_3);
        pushButton_18->setObjectName(QString::fromUtf8("pushButton_18"));
        pushButton_18->setGeometry(QRect(815, 560, 141, 41));
        pushButton_18->setFont(font4);
        stackedWidget->addWidget(page_3);
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, -10, 241, 671));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(44, 46, 70, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(212, 0, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(85, 0, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(113, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush7(QColor(212, 127, 127, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush7);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        QBrush brush9(QColor(0, 0, 0, 128));
        brush9.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush9);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        QBrush brush10(QColor(0, 0, 0, 128));
        brush10.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush10);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        QBrush brush11(QColor(170, 0, 0, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush11);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        QBrush brush12(QColor(0, 0, 0, 128));
        brush12.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush12);
#endif
        widget->setPalette(palette);
        widget->setAutoFillBackground(true);
        widget->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 221, 151));
        label->setMaximumSize(QSize(16777215, 400));
        QFont font8;
        font8.setFamily(QString::fromUtf8("Adobe Devanagari"));
        font8.setPointSize(13);
        font8.setBold(true);
        font8.setWeight(75);
        label->setFont(font8);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 290, 201, 91));
        QFont font9;
        font9.setFamily(QString::fromUtf8("\347\255\211\347\272\277"));
        font9.setPointSize(9);
        label_4->setFont(font9);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        label_4->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 390, 221, 241));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(40);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setFont(font1);
        pushButton_2->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
        pushButton_3->setFont(font1);
        pushButton_3->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(pushButton_3);

        ReconstructionClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ReconstructionClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ReconstructionClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(ReconstructionClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1240, 26));
        ReconstructionClass->setMenuBar(menuBar);

        retranslateUi(ReconstructionClass);
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ReconstructionClass);
    } // setupUi

    void retranslateUi(QMainWindow *ReconstructionClass)
    {
        ReconstructionClass->setWindowTitle(QApplication::translate("ReconstructionClass", "Reconstruction", nullptr));
        actioncamera->setText(QApplication::translate("ReconstructionClass", "camera", nullptr));
        actionstyle->setText(QApplication::translate("ReconstructionClass", "style", nullptr));
        label_2->setText(QApplication::translate("ReconstructionClass", "Live Video", nullptr));
        groupBox->setTitle(QApplication::translate("ReconstructionClass", "\347\233\270\346\234\272\345\217\202\346\225\260\346\240\217", nullptr));
        label_7->setText(QApplication::translate("ReconstructionClass", "KC1", nullptr));
        label_6->setText(QApplication::translate("ReconstructionClass", "T12", nullptr));
        label_5->setText(QApplication::translate("ReconstructionClass", "R12", nullptr));
        label_8->setText(QApplication::translate("ReconstructionClass", "KP2", nullptr));
        groupBox_2->setTitle(QApplication::translate("ReconstructionClass", "\346\240\207\345\256\232\346\235\277\350\256\276\347\275\256", nullptr));
        label_15->setText(QApplication::translate("ReconstructionClass", "\350\241\214\346\225\260", nullptr));
        label_22->setText(QApplication::translate("ReconstructionClass", "\346\243\213\347\233\230\345\260\272\345\257\270(mm)", nullptr));
        label_16->setText(QApplication::translate("ReconstructionClass", "\345\210\227\346\225\260", nullptr));
        groupBox_5->setTitle(QString());
        label_11->setText(QApplication::translate("ReconstructionClass", "NO VIDEO", nullptr));
        pushButton_5->setText(QApplication::translate("ReconstructionClass", "\346\267\273\345\212\240\345\233\276\345\203\217", nullptr));
        pushButton_6->setText(QApplication::translate("ReconstructionClass", "\347\233\270\346\234\272\346\213\215\346\221\204", nullptr));
        pushButton_7->setText(QApplication::translate("ReconstructionClass", "\347\233\270\346\234\272\346\240\207\345\256\232", nullptr));
        pushButton_8->setText(QApplication::translate("ReconstructionClass", "\344\277\235\345\255\230\347\273\223\346\236\234", nullptr));
        groupBox_3->setTitle(QApplication::translate("ReconstructionClass", "\346\240\207\345\256\232\346\227\245\345\277\227", nullptr));
        label_3->setText(QApplication::translate("ReconstructionClass", "Live Video", nullptr));
        groupBox_6->setTitle(QString());
        label_21->setText(QApplication::translate("ReconstructionClass", "NO VIDEO", nullptr));
        pushButton_4->setText(QApplication::translate("ReconstructionClass", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        label_18->setText(QApplication::translate("ReconstructionClass", "\350\275\275\345\205\245\346\212\225\345\275\261\345\233\276\345\203\217", nullptr));
        groupBox_7->setTitle(QApplication::translate("ReconstructionClass", "\351\207\215\345\273\272\346\227\245\345\277\227", nullptr));
        groupBox_8->setTitle(QString());
        pushButton_9->setText(QApplication::translate("ReconstructionClass", "\347\233\270\346\234\272\346\213\215\347\205\247", nullptr));
        pushButton_10->setText(QApplication::translate("ReconstructionClass", "\344\277\235\345\255\230\347\205\247\347\211\207", nullptr));
        pushButton_17->setText(QApplication::translate("ReconstructionClass", "\345\274\200\345\247\213\351\207\215\345\273\272", nullptr));
        pushButton_19->setText(QApplication::translate("ReconstructionClass", "\346\212\225\345\275\261\345\233\276\346\241\210", nullptr));
        groupBox_4->setTitle(QApplication::translate("ReconstructionClass", "\350\256\276\347\275\256", nullptr));
        label_12->setText(QApplication::translate("ReconstructionClass", "\351\242\234\350\211\262\351\200\211\346\213\251", nullptr));
        pushButton_11->setText(QApplication::translate("ReconstructionClass", "\351\200\211\346\213\251", nullptr));
        pushButton_12->setText(QApplication::translate("ReconstructionClass", "\345\211\224\351\231\244", nullptr));
        label_14->setText(QApplication::translate("ReconstructionClass", "\345\274\202\345\270\270\347\202\271", nullptr));
        pushButton_16->setText(QString());
        pushButton_13->setText(QApplication::translate("ReconstructionClass", "\345\257\274\345\205\245\347\202\271\344\272\221", nullptr));
        pushButton_14->setText(QApplication::translate("ReconstructionClass", "\345\257\274\345\207\272\347\273\223\346\236\234", nullptr));
        pushButton_15->setText(QApplication::translate("ReconstructionClass", "\346\233\262\351\235\242\351\207\215\345\273\272", nullptr));
        label_9->setText(QString());
        pushButton_18->setText(QApplication::translate("ReconstructionClass", "\344\275\277\347\224\250\345\270\256\345\212\251", nullptr));
        label->setText(QApplication::translate("ReconstructionClass", "3D RECONSTRUCTION", nullptr));
        label_4->setText(QApplication::translate("ReconstructionClass", "\345\212\237\350\203\275\351\200\211\346\213\251", nullptr));
        pushButton->setText(QApplication::translate("ReconstructionClass", "\347\263\273\347\273\237\346\240\207\345\256\232", nullptr));
        pushButton_2->setText(QApplication::translate("ReconstructionClass", "\344\270\211\347\273\264\351\207\215\345\273\272", nullptr));
        pushButton_3->setText(QApplication::translate("ReconstructionClass", "\347\202\271\344\272\221\346\270\262\346\237\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReconstructionClass: public Ui_ReconstructionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECONSTRUCTION_H
