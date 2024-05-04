/********************************************************************************
** Form generated from reading UI file 'oublierr.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OUBLIERR_H
#define UI_OUBLIERR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_oublierr
{
public:

    void setupUi(QDialog *oublierr)
    {
        if (oublierr->objectName().isEmpty())
            oublierr->setObjectName(QStringLiteral("oublierr"));
        oublierr->resize(596, 376);

        retranslateUi(oublierr);

        QMetaObject::connectSlotsByName(oublierr);
    } // setupUi

    void retranslateUi(QDialog *oublierr)
    {
        oublierr->setWindowTitle(QApplication::translate("oublierr", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class oublierr: public Ui_oublierr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OUBLIERR_H
