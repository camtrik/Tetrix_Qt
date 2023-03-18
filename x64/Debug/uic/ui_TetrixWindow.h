/********************************************************************************
** Form generated from reading UI file 'TetrixWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TETRIXWINDOW_H
#define UI_TETRIXWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TetrixWindowClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QFrame *boardFrame;
    QFrame *otherFrame;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QLabel *nextPieceLabel;
    QLabel *label_2;
    QLCDNumber *levelNumber;
    QLabel *label;
    QLCDNumber *lineNumber;
    QLabel *label_3;
    QLCDNumber *scoreNumber;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *startButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *pauseButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TetrixWindowClass)
    {
        if (TetrixWindowClass->objectName().isEmpty())
            TetrixWindowClass->setObjectName(QString::fromUtf8("TetrixWindowClass"));
        TetrixWindowClass->resize(1104, 1256);
        centralWidget = new QWidget(TetrixWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        boardFrame = new QFrame(centralWidget);
        boardFrame->setObjectName(QString::fromUtf8("boardFrame"));
        boardFrame->setMinimumSize(QSize(650, 900));
        boardFrame->setFrameShape(QFrame::StyledPanel);
        boardFrame->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(boardFrame);

        otherFrame = new QFrame(centralWidget);
        otherFrame->setObjectName(QString::fromUtf8("otherFrame"));
        otherFrame->setFrameShape(QFrame::StyledPanel);
        otherFrame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(otherFrame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_4 = new QLabel(otherFrame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe \345\256\213\344\275\223 Std L"));
        font.setPointSize(14);
        label_4->setFont(font);

        verticalLayout->addWidget(label_4);

        nextPieceLabel = new QLabel(otherFrame);
        nextPieceLabel->setObjectName(QString::fromUtf8("nextPieceLabel"));
        nextPieceLabel->setMinimumSize(QSize(280, 280));
        nextPieceLabel->setFrameShape(QFrame::Box);
        nextPieceLabel->setFrameShadow(QFrame::Raised);
        nextPieceLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(nextPieceLabel);

        label_2 = new QLabel(otherFrame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        levelNumber = new QLCDNumber(otherFrame);
        levelNumber->setObjectName(QString::fromUtf8("levelNumber"));

        verticalLayout->addWidget(levelNumber);

        label = new QLabel(otherFrame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);

        verticalLayout->addWidget(label);

        lineNumber = new QLCDNumber(otherFrame);
        lineNumber->setObjectName(QString::fromUtf8("lineNumber"));

        verticalLayout->addWidget(lineNumber);

        label_3 = new QLabel(otherFrame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        scoreNumber = new QLCDNumber(otherFrame);
        scoreNumber->setObjectName(QString::fromUtf8("scoreNumber"));

        verticalLayout->addWidget(scoreNumber);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        startButton = new QPushButton(otherFrame);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setMinimumSize(QSize(150, 80));

        horizontalLayout_2->addWidget(startButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pauseButton = new QPushButton(otherFrame);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        pauseButton->setMinimumSize(QSize(150, 80));

        horizontalLayout_2->addWidget(pauseButton);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addWidget(otherFrame);

        TetrixWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TetrixWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1104, 26));
        TetrixWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TetrixWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        TetrixWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TetrixWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TetrixWindowClass->setStatusBar(statusBar);

        retranslateUi(TetrixWindowClass);

        QMetaObject::connectSlotsByName(TetrixWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *TetrixWindowClass)
    {
        TetrixWindowClass->setWindowTitle(QCoreApplication::translate("TetrixWindowClass", "TetrixWindow", nullptr));
        label_4->setText(QCoreApplication::translate("TetrixWindowClass", "NEXT PIECE", nullptr));
        nextPieceLabel->setText(QString());
        label_2->setText(QCoreApplication::translate("TetrixWindowClass", "LEVEL", nullptr));
        label->setText(QCoreApplication::translate("TetrixWindowClass", "LINES REMOVED", nullptr));
        label_3->setText(QCoreApplication::translate("TetrixWindowClass", "SCORE", nullptr));
        startButton->setText(QCoreApplication::translate("TetrixWindowClass", "Start", nullptr));
        pauseButton->setText(QCoreApplication::translate("TetrixWindowClass", "Pause", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TetrixWindowClass: public Ui_TetrixWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TETRIXWINDOW_H
