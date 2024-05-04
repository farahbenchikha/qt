/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QLabel *label_21;
    QLabel *label_13;
    QLabel *label_29;
    QLabel *label_27;
    QLineEdit *nom;
    QLineEdit *mdp;
    QPushButton *connexion;
    QLabel *label_34;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_28;
    QLabel *ou;
    QPushButton *inscrire;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->resize(981, 486);
        label_21 = new QLabel(login);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(0, -20, 981, 511));
        label_21->setStyleSheet(QStringLiteral("background-color:rgb(63, 63, 63)"));
        label_13 = new QLabel(login);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(40, 20, 911, 441));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        label_13->setFont(font);
        label_13->setStyleSheet(QLatin1String("background-color: rgb(248, 248, 248);\n"
"\n"
""));
        label_29 = new QLabel(login);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(310, 40, 371, 51));
        label_29->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        label_27 = new QLabel(login);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(400, 90, 191, 81));
        label_27->setStyleSheet(QStringLiteral("image: url(:/login1/login1.png);"));
        nom = new QLineEdit(login);
        nom->setObjectName(QStringLiteral("nom"));
        nom->setGeometry(QRect(410, 180, 171, 41));
        nom->setStyleSheet(QStringLiteral("background-color: rgb(63, 63, 63);"));
        mdp = new QLineEdit(login);
        mdp->setObjectName(QStringLiteral("mdp"));
        mdp->setGeometry(QRect(410, 230, 171, 41));
        mdp->setStyleSheet(QStringLiteral("background-color: rgb(63, 63, 63);"));
        mdp->setFrame(true);
        mdp->setEchoMode(QLineEdit::Password);
        connexion = new QPushButton(login);
        connexion->setObjectName(QStringLiteral("connexion"));
        connexion->setGeometry(QRect(440, 300, 101, 31));
        connexion->setStyleSheet(QLatin1String("background-color: rgb(67, 67, 67);\n"
"QPushBoutton:\n"
"{\n"
"   border-radius:40px;\n"
"}"));
        label_34 = new QLabel(login);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(250, 230, 161, 41));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label_34->setFont(font1);
        label_32 = new QLabel(login);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(250, 180, 161, 31));
        label_32->setFont(font1);
        label_33 = new QLabel(login);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(200, 180, 41, 31));
        label_33->setStyleSheet(QStringLiteral("image: url(:/login1/login1.png);"));
        label_28 = new QLabel(login);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(200, 230, 41, 31));
        label_28->setStyleSheet(QStringLiteral("image: url(:/mdp/mdpp.png);"));
        ou = new QLabel(login);
        ou->setObjectName(QStringLiteral("ou"));
        ou->setGeometry(QRect(400, 360, 201, 20));
        inscrire = new QPushButton(login);
        inscrire->setObjectName(QStringLiteral("inscrire"));
        inscrire->setGeometry(QRect(820, 410, 93, 28));
        inscrire->setStyleSheet(QLatin1String("background-color: rgb(8, 8, 8);\n"
"color: rgb(214, 214, 214);"));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QApplication::translate("login", "Dialog", Q_NULLPTR));
        label_21->setText(QString());
        label_13->setText(QString());
        label_29->setText(QApplication::translate("login", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">BIENVENUE</span></p></body></html>", Q_NULLPTR));
        label_27->setText(QString());
        connexion->setText(QApplication::translate("login", "connexion", Q_NULLPTR));
        label_34->setText(QApplication::translate("login", "Mot De Passe   :", Q_NULLPTR));
        label_32->setText(QApplication::translate("login", "Adresse Mail:", Q_NULLPTR));
        label_33->setText(QString());
        label_28->setText(QString());
        ou->setText(QApplication::translate("login", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600; text-decoration: underline;\">Mot De Passe Oubli\303\251e?</span></p></body></html>", Q_NULLPTR));
        inscrire->setText(QApplication::translate("login", "S'inscrire", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
