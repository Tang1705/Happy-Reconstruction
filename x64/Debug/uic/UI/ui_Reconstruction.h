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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReconstructionClass
{
public:
    QWidget *centralWidget;
    QFrame *line;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label_2;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QLabel *label_5;
    QTextBrowser *textBrowser_3;
    QLabel *label_7;
    QTextBrowser *textBrowser;
    QLabel *label_10;
    QTextBrowser *textBrowser_2;
    QLabel *label_8;
    QLabel *label_9;
    QTextBrowser *textBrowser_6;
    QTextBrowser *textBrowser_5;
    QTextBrowser *textBrowser_4;
    QGroupBox *groupBox_2;
    QWidget *gridLayoutWidget_6;
    QGridLayout *gridLayout_6;
    QLabel *label_22;
    QLabel *label_15;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QLabel *label_16;
    QGroupBox *groupBox_5;
    QLabel *label_11;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QGroupBox *groupBox_3;
    QTextBrowser *textBrowser_7;
    QWidget *page_2;
    QLabel *label_3;
    QGroupBox *groupBox_6;
    QLabel *label_21;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_4;
    QLineEdit *lineEdit;
    QLabel *label_18;
    QWidget *page_3;
    QGroupBox *groupBox_4;
    QSlider *horizontalSlider;
    QLabel *label_13;
    QLabel *label_12;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QLabel *label_14;
    QPushButton *pushButton_16;
    QGraphicsView *graphicsView;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label_4;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ReconstructionClass)
    {
        if (ReconstructionClass->objectName().isEmpty())
            ReconstructionClass->setObjectName(QString::fromUtf8("ReconstructionClass"));
        ReconstructionClass->resize(1111, 604);
        centralWidget = new QWidget(ReconstructionClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(230, 0, 20, 571));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(249, -1, 851, 551));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        label_2 = new QLabel(page);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(220, 20, 81, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe Devanagari"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        groupBox = new QGroupBox(page);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(520, 260, 321, 271));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(10);
        groupBox->setFont(font1);
        groupBox->setAlignment(Qt::AlignCenter);
        gridLayoutWidget_2 = new QWidget(groupBox);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 20, 321, 251));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetMinAndMaxSize);
        gridLayout_2->setHorizontalSpacing(7);
        gridLayout_2->setContentsMargins(10, 10, 10, 10);
        label_6 = new QLabel(gridLayoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Adobe Devanagari"));
        font2.setPointSize(10);
        label_6->setFont(font2);
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_6, 1, 0, 1, 1);

        label_5 = new QLabel(gridLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        textBrowser_3 = new QTextBrowser(gridLayoutWidget_2);
        textBrowser_3->setObjectName(QString::fromUtf8("textBrowser_3"));
        textBrowser_3->setMaximumSize(QSize(250, 31));
        textBrowser_3->setFont(font2);

        gridLayout_2->addWidget(textBrowser_3, 2, 1, 1, 1);

        label_7 = new QLabel(gridLayoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font2);
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_7, 2, 0, 1, 1);

        textBrowser = new QTextBrowser(gridLayoutWidget_2);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setMaximumSize(QSize(250, 31));
        textBrowser->setFont(font2);

        gridLayout_2->addWidget(textBrowser, 0, 1, 1, 1);

        label_10 = new QLabel(gridLayoutWidget_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font2);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_10, 5, 0, 1, 1);

        textBrowser_2 = new QTextBrowser(gridLayoutWidget_2);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setMaximumSize(QSize(250, 31));
        textBrowser_2->setFont(font2);

        gridLayout_2->addWidget(textBrowser_2, 1, 1, 1, 1);

        label_8 = new QLabel(gridLayoutWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font2);
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_8, 3, 0, 1, 1);

        label_9 = new QLabel(gridLayoutWidget_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font2);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_9, 4, 0, 1, 1);

        textBrowser_6 = new QTextBrowser(gridLayoutWidget_2);
        textBrowser_6->setObjectName(QString::fromUtf8("textBrowser_6"));
        textBrowser_6->setMaximumSize(QSize(250, 31));
        textBrowser_6->setFont(font2);

        gridLayout_2->addWidget(textBrowser_6, 5, 1, 1, 1);

        textBrowser_5 = new QTextBrowser(gridLayoutWidget_2);
        textBrowser_5->setObjectName(QString::fromUtf8("textBrowser_5"));
        textBrowser_5->setMaximumSize(QSize(250, 31));
        textBrowser_5->setFont(font2);

        gridLayout_2->addWidget(textBrowser_5, 4, 1, 1, 1);

        textBrowser_4 = new QTextBrowser(gridLayoutWidget_2);
        textBrowser_4->setObjectName(QString::fromUtf8("textBrowser_4"));
        textBrowser_4->setMaximumSize(QSize(250, 31));
        textBrowser_4->setFont(font2);

        gridLayout_2->addWidget(textBrowser_4, 3, 1, 1, 1);

        groupBox_2 = new QGroupBox(page);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 360, 251, 171));
        groupBox_2->setFont(font1);
        groupBox_2->setAlignment(Qt::AlignCenter);
        gridLayoutWidget_6 = new QWidget(groupBox_2);
        gridLayoutWidget_6->setObjectName(QString::fromUtf8("gridLayoutWidget_6"));
        gridLayoutWidget_6->setGeometry(QRect(20, 30, 211, 131));
        gridLayout_6 = new QGridLayout(gridLayoutWidget_6);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setSizeConstraint(QLayout::SetMinAndMaxSize);
        gridLayout_6->setHorizontalSpacing(7);
        gridLayout_6->setContentsMargins(10, 10, 10, 10);
        label_22 = new QLabel(gridLayoutWidget_6);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        QFont font3;
        font3.setPointSize(9);
        label_22->setFont(font3);
        label_22->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_22, 0, 0, 1, 1);

        label_15 = new QLabel(gridLayoutWidget_6);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font4.setPointSize(9);
        label_15->setFont(font4);
        label_15->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_15, 1, 0, 1, 1);

        spinBox = new QSpinBox(gridLayoutWidget_6);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        gridLayout_6->addWidget(spinBox, 0, 2, 1, 1);

        spinBox_2 = new QSpinBox(gridLayoutWidget_6);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));

        gridLayout_6->addWidget(spinBox_2, 1, 2, 1, 1);

        spinBox_3 = new QSpinBox(gridLayoutWidget_6);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));

        gridLayout_6->addWidget(spinBox_3, 2, 2, 1, 1);

        label_16 = new QLabel(gridLayoutWidget_6);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font4);
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_16, 2, 0, 1, 1);

        groupBox_5 = new QGroupBox(page);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 40, 491, 291));
        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(190, 120, 121, 31));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Adobe Devanagari"));
        font5.setPointSize(16);
        label_11->setFont(font5);
        pushButton_5 = new QPushButton(page);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(280, 390, 100, 28));
        pushButton_5->setMaximumSize(QSize(100, 16777215));
        pushButton_5->setFont(font4);
        pushButton_6 = new QPushButton(page);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(400, 390, 100, 28));
        pushButton_6->setMaximumSize(QSize(100, 16777215));
        pushButton_6->setFont(font4);
        pushButton_7 = new QPushButton(page);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(280, 470, 100, 28));
        pushButton_7->setMaximumSize(QSize(100, 16777215));
        pushButton_7->setFont(font4);
        pushButton_8 = new QPushButton(page);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(400, 470, 100, 28));
        pushButton_8->setMaximumSize(QSize(100, 16777215));
        pushButton_8->setFont(font4);
        groupBox_3 = new QGroupBox(page);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(520, 30, 321, 211));
        groupBox_3->setFont(font1);
        groupBox_3->setAlignment(Qt::AlignCenter);
        textBrowser_7 = new QTextBrowser(groupBox_3);
        textBrowser_7->setObjectName(QString::fromUtf8("textBrowser_7"));
        textBrowser_7->setGeometry(QRect(10, 20, 301, 181));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        label_3 = new QLabel(page_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(390, 20, 81, 16));
        label_3->setFont(font);
        groupBox_6 = new QGroupBox(page_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(80, 40, 701, 401));
        label_21 = new QLabel(groupBox_6);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(280, 170, 121, 31));
        label_21->setFont(font5);
        pushButton_9 = new QPushButton(page_2);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(620, 470, 93, 31));
        QFont font6;
        font6.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        pushButton_9->setFont(font6);
        pushButton_10 = new QPushButton(page_2);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(730, 470, 93, 31));
        pushButton_10->setFont(font6);
        pushButton_4 = new QPushButton(page_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(470, 470, 81, 31));
        pushButton_4->setFont(font6);
        lineEdit = new QLineEdit(page_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(160, 470, 294, 31));
        label_18 = new QLabel(page_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(40, 470, 111, 30));
        label_18->setMaximumSize(QSize(16777215, 30));
        label_18->setFont(font4);
        label_18->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        groupBox_4 = new QGroupBox(page_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(650, 60, 191, 171));
        groupBox_4->setFont(font6);
        groupBox_4->setAlignment(Qt::AlignCenter);
        horizontalSlider = new QSlider(groupBox_4);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(90, 80, 91, 22));
        horizontalSlider->setOrientation(Qt::Horizontal);
        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 80, 72, 15));
        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 50, 72, 15));
        pushButton_11 = new QPushButton(groupBox_4);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(70, 117, 51, 21));
        pushButton_12 = new QPushButton(groupBox_4);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(130, 117, 51, 21));
        label_14 = new QLabel(groupBox_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 120, 72, 15));
        pushButton_16 = new QPushButton(groupBox_4);
        pushButton_16->setObjectName(QString::fromUtf8("pushButton_16"));
        pushButton_16->setGeometry(QRect(100, 47, 51, 21));
        graphicsView = new QGraphicsView(page_3);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(0, 10, 641, 521));
        pushButton_13 = new QPushButton(page_3);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(700, 310, 93, 28));
        pushButton_13->setFont(font6);
        pushButton_14 = new QPushButton(page_3);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        pushButton_14->setGeometry(QRect(700, 380, 93, 28));
        pushButton_14->setFont(font6);
        pushButton_15 = new QPushButton(page_3);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));
        pushButton_15->setGeometry(QRect(700, 450, 93, 28));
        pushButton_15->setFont(font6);
        stackedWidget->addWidget(page_3);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 260, 219, 241));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setFont(font6);

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setFont(font6);

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setFont(font6);

        verticalLayout->addWidget(pushButton_3);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 180, 219, 91));
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignCenter);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 219, 151));
        label->setMaximumSize(QSize(16777215, 400));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Adobe Devanagari"));
        font7.setPointSize(14);
        font7.setBold(true);
        font7.setWeight(75);
        label->setFont(font7);
        ReconstructionClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ReconstructionClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1111, 26));
        ReconstructionClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ReconstructionClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ReconstructionClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ReconstructionClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ReconstructionClass->setStatusBar(statusBar);

        retranslateUi(ReconstructionClass);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(ReconstructionClass);
    } // setupUi

    void retranslateUi(QMainWindow *ReconstructionClass)
    {
        ReconstructionClass->setWindowTitle(QApplication::translate("ReconstructionClass", "Reconstruction", nullptr));
        label_2->setText(QApplication::translate("ReconstructionClass", "Live Video", nullptr));
        groupBox->setTitle(QApplication::translate("ReconstructionClass", "\347\233\270\346\234\272\345\217\202\346\225\260\346\240\217", nullptr));
        label_6->setText(QApplication::translate("ReconstructionClass", "T12", nullptr));
        label_5->setText(QApplication::translate("ReconstructionClass", "R12", nullptr));
        label_7->setText(QApplication::translate("ReconstructionClass", "KC1", nullptr));
        label_10->setText(QApplication::translate("ReconstructionClass", "HP2", nullptr));
        label_8->setText(QApplication::translate("ReconstructionClass", "KP2", nullptr));
        label_9->setText(QApplication::translate("ReconstructionClass", "HC1", nullptr));
        groupBox_2->setTitle(QApplication::translate("ReconstructionClass", "\346\240\207\345\256\232\346\235\277\350\256\276\347\275\256", nullptr));
        label_22->setText(QApplication::translate("ReconstructionClass", "\346\243\213\347\233\230\345\260\272\345\257\270(mm)", nullptr));
        label_15->setText(QApplication::translate("ReconstructionClass", "\350\241\214\346\225\260", nullptr));
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
        pushButton_9->setText(QApplication::translate("ReconstructionClass", "\347\233\270\346\234\272\346\213\215\347\205\247", nullptr));
        pushButton_10->setText(QApplication::translate("ReconstructionClass", "\344\277\235\345\255\230\347\205\247\347\211\207", nullptr));
        pushButton_4->setText(QApplication::translate("ReconstructionClass", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        label_18->setText(QApplication::translate("ReconstructionClass", "\350\275\275\345\205\245\346\212\225\345\275\261\345\233\276\346\241\210", nullptr));
        groupBox_4->setTitle(QApplication::translate("ReconstructionClass", "\350\256\276\347\275\256", nullptr));
        label_13->setText(QApplication::translate("ReconstructionClass", "\347\202\271\347\232\204\345\244\247\345\260\217", nullptr));
        label_12->setText(QApplication::translate("ReconstructionClass", "\351\242\234\350\211\262\351\200\211\346\213\251", nullptr));
        pushButton_11->setText(QApplication::translate("ReconstructionClass", "\351\200\211\346\213\251", nullptr));
        pushButton_12->setText(QApplication::translate("ReconstructionClass", "\345\211\224\351\231\244", nullptr));
        label_14->setText(QApplication::translate("ReconstructionClass", "\345\274\202\345\270\270\347\202\271", nullptr));
        pushButton_16->setText(QApplication::translate("ReconstructionClass", "COLOR", nullptr));
        pushButton_13->setText(QApplication::translate("ReconstructionClass", "\345\257\274\345\205\245\347\202\271\344\272\221", nullptr));
        pushButton_14->setText(QApplication::translate("ReconstructionClass", "\345\257\274\345\207\272\347\273\223\346\236\234", nullptr));
        pushButton_15->setText(QApplication::translate("ReconstructionClass", "\344\277\235\345\255\230\346\210\252\345\233\276", nullptr));
        pushButton->setText(QApplication::translate("ReconstructionClass", "\347\233\270\346\234\272\346\240\207\345\256\232", nullptr));
        pushButton_2->setText(QApplication::translate("ReconstructionClass", "\345\233\276\346\241\210\346\212\225\345\275\261", nullptr));
        pushButton_3->setText(QApplication::translate("ReconstructionClass", "\344\270\211\347\273\264\351\207\215\345\273\272", nullptr));
        label_4->setText(QApplication::translate("ReconstructionClass", "\345\212\237\350\203\275\351\200\211\346\213\251", nullptr));
        label->setText(QApplication::translate("ReconstructionClass", "3D RECONSTRUCTION", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReconstructionClass: public Ui_ReconstructionClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECONSTRUCTION_H
