/********************************************************************************
** Form generated from reading UI file 'mdp.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MDP_H
#define UI_MDP_H

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

class Ui_mdp
{
public:
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label;
    QPushButton *envoyer;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *server;
    QLineEdit *port;
    QLineEdit *uname;
    QLineEdit *paswd;
    QLabel *label_8;
    QLineEdit *rcpt;
    QLineEdit *subject;
    QLineEdit *msg;

    void setupUi(QDialog *mdp)
    {
        if (mdp->objectName().isEmpty())
            mdp->setObjectName(QStringLiteral("mdp"));
        mdp->resize(665, 418);
        label_30 = new QLabel(mdp);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(0, -10, 671, 431));
        label_30->setStyleSheet(QStringLiteral("background-color:rgb(63, 63, 63)"));
        label_31 = new QLabel(mdp);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(20, 20, 631, 371));
        label_31->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label = new QLabel(mdp);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(220, 20, 281, 81));
        QFont font;
        font.setFamily(QStringLiteral("MS Serif"));
        font.setPointSize(10);
        label->setFont(font);
        envoyer = new QPushButton(mdp);
        envoyer->setObjectName(QStringLiteral("envoyer"));
        envoyer->setGeometry(QRect(230, 350, 93, 28));
        envoyer->setStyleSheet(QLatin1String("border-color: rgb(255, 255, 255);\n"
"background-color: rgb(27, 27, 27);"));
        label_2 = new QLabel(mdp);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(160, 80, 91, 21));
        label_3 = new QLabel(mdp);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(170, 110, 81, 21));
        label_4 = new QLabel(mdp);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(180, 140, 71, 31));
        label_5 = new QLabel(mdp);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(170, 210, 81, 41));
        label_6 = new QLabel(mdp);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(170, 260, 61, 21));
        label_7 = new QLabel(mdp);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(170, 310, 81, 16));
        server = new QLineEdit(mdp);
        server->setObjectName(QStringLiteral("server"));
        server->setGeometry(QRect(270, 70, 113, 22));
        port = new QLineEdit(mdp);
        port->setObjectName(QStringLiteral("port"));
        port->setGeometry(QRect(270, 110, 113, 22));
        uname = new QLineEdit(mdp);
        uname->setObjectName(QStringLiteral("uname"));
        uname->setGeometry(QRect(260, 140, 113, 22));
        paswd = new QLineEdit(mdp);
        paswd->setObjectName(QStringLiteral("paswd"));
        paswd->setGeometry(QRect(260, 180, 113, 22));
        label_8 = new QLabel(mdp);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(180, 190, 56, 16));
        rcpt = new QLineEdit(mdp);
        rcpt->setObjectName(QStringLiteral("rcpt"));
        rcpt->setGeometry(QRect(260, 220, 113, 22));
        subject = new QLineEdit(mdp);
        subject->setObjectName(QStringLiteral("subject"));
        subject->setGeometry(QRect(250, 260, 113, 22));
        msg = new QLineEdit(mdp);
        msg->setObjectName(QStringLiteral("msg"));
        msg->setGeometry(QRect(250, 300, 113, 22));

        retranslateUi(mdp);

        QMetaObject::connectSlotsByName(mdp);
    } // setupUi

    void retranslateUi(QDialog *mdp)
    {
        mdp->setWindowTitle(QApplication::translate("mdp", "Dialog", Q_NULLPTR));
        label_30->setText(QString());
        label_31->setText(QString());
        label->setText(QApplication::translate("mdp", "Recuperer votre mot de passe ", Q_NULLPTR));
        envoyer->setText(QApplication::translate("mdp", "envoyer", Q_NULLPTR));
        label_2->setText(QApplication::translate("mdp", "smtp_server:", Q_NULLPTR));
        label_3->setText(QApplication::translate("mdp", "server port:", Q_NULLPTR));
        label_4->setText(QApplication::translate("mdp", "username", Q_NULLPTR));
        label_5->setText(QApplication::translate("mdp", "recipant to:", Q_NULLPTR));
        label_6->setText(QApplication::translate("mdp", "subjetct:", Q_NULLPTR));
        label_7->setText(QApplication::translate("mdp", "message:", Q_NULLPTR));
        label_8->setText(QApplication::translate("mdp", "password:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mdp: public Ui_mdp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MDP_H
