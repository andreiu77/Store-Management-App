/********************************************************************************
** Form generated from reading UI file 'lab78oop.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB78OOP_H
#define UI_LAB78OOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lab78oopClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *lab78oopClass)
    {
        if (lab78oopClass->objectName().isEmpty())
            lab78oopClass->setObjectName("lab78oopClass");
        lab78oopClass->resize(600, 400);
        menuBar = new QMenuBar(lab78oopClass);
        menuBar->setObjectName("menuBar");
        lab78oopClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(lab78oopClass);
        mainToolBar->setObjectName("mainToolBar");
        lab78oopClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(lab78oopClass);
        centralWidget->setObjectName("centralWidget");
        lab78oopClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(lab78oopClass);
        statusBar->setObjectName("statusBar");
        lab78oopClass->setStatusBar(statusBar);

        retranslateUi(lab78oopClass);

        QMetaObject::connectSlotsByName(lab78oopClass);
    } // setupUi

    void retranslateUi(QMainWindow *lab78oopClass)
    {
        lab78oopClass->setWindowTitle(QCoreApplication::translate("lab78oopClass", "lab78oop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class lab78oopClass: public Ui_lab78oopClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB78OOP_H
