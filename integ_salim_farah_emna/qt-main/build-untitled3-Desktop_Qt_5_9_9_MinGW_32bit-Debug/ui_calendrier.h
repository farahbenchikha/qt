/********************************************************************************
** Form generated from reading UI file 'calendrier.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALENDRIER_H
#define UI_CALENDRIER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_calendrier
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QFormLayout *formLayout;
    QCalendarWidget *calendarWidget;
    QListWidget *listWidget_studios;
    QPushButton *pushButton_reservation;
    QLabel *label;
    QListWidget *listWidgetRES;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *calendrier)
    {
        if (calendrier->objectName().isEmpty())
            calendrier->setObjectName(QStringLiteral("calendrier"));
        calendrier->resize(800, 600);
        centralwidget = new QWidget(calendrier);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 801, 551));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        calendarWidget = new QCalendarWidget(widget);
        calendarWidget->setObjectName(QStringLiteral("calendarWidget"));

        formLayout->setWidget(0, QFormLayout::LabelRole, calendarWidget);

        listWidget_studios = new QListWidget(widget);
        listWidget_studios->setObjectName(QStringLiteral("listWidget_studios"));

        formLayout->setWidget(0, QFormLayout::FieldRole, listWidget_studios);

        pushButton_reservation = new QPushButton(widget);
        pushButton_reservation->setObjectName(QStringLiteral("pushButton_reservation"));

        formLayout->setWidget(1, QFormLayout::FieldRole, pushButton_reservation);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label);

        listWidgetRES = new QListWidget(widget);
        listWidgetRES->setObjectName(QStringLiteral("listWidgetRES"));

        formLayout->setWidget(2, QFormLayout::FieldRole, listWidgetRES);

        calendrier->setCentralWidget(centralwidget);
        menubar = new QMenuBar(calendrier);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        calendrier->setMenuBar(menubar);
        statusbar = new QStatusBar(calendrier);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        calendrier->setStatusBar(statusbar);

        retranslateUi(calendrier);

        QMetaObject::connectSlotsByName(calendrier);
    } // setupUi

    void retranslateUi(QMainWindow *calendrier)
    {
        calendrier->setWindowTitle(QApplication::translate("calendrier", "MainWindow", Q_NULLPTR));
        pushButton_reservation->setText(QApplication::translate("calendrier", "Reserver", Q_NULLPTR));
        label->setText(QApplication::translate("calendrier", "les studios reserve", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class calendrier: public Ui_calendrier {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENDRIER_H
