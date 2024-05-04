/********************************************************************************
** Form generated from reading UI file 'inscrit.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSCRIT_H
#define UI_INSCRIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_inscrit
{
public:
    QLabel *label_30;
    QLabel *label_31;
    QLineEdit *ID_Perso;
    QLineEdit *Nom_Perso;
    QLineEdit *Prenom_Perso;
    QLineEdit *Tel;
    QLineEdit *Adresse;
    QComboBox *role;
    QPushButton *ajout_sinscrire;
    QPushButton *supprimer_2;
    QPushButton *pushButton_78;
    QLabel *label_37;
    QLabel *label_36;
    QLabel *label_38;
    QLabel *label_39;
    QLabel *label_41;
    QLabel *label_40;
    QLabel *label;
    QPushButton *retourner;
    QPushButton *sms;
    QLineEdit *password;
    QLabel *label_2;

    void setupUi(QDialog *inscrit)
    {
        if (inscrit->objectName().isEmpty())
            inscrit->setObjectName(QStringLiteral("inscrit"));
        inscrit->resize(783, 471);
        label_30 = new QLabel(inscrit);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(0, 0, 791, 471));
        label_30->setStyleSheet(QStringLiteral("background-color:rgb(63, 63, 63)"));
        label_31 = new QLabel(inscrit);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(30, 30, 721, 411));
        label_31->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        ID_Perso = new QLineEdit(inscrit);
        ID_Perso->setObjectName(QStringLiteral("ID_Perso"));
        ID_Perso->setGeometry(QRect(290, 110, 211, 31));
        ID_Perso->setStyleSheet(QStringLiteral("background-color: rgb(66, 66, 66);"));
        Nom_Perso = new QLineEdit(inscrit);
        Nom_Perso->setObjectName(QStringLiteral("Nom_Perso"));
        Nom_Perso->setGeometry(QRect(290, 150, 211, 31));
        Nom_Perso->setStyleSheet(QStringLiteral("background-color: rgb(66, 66, 66);"));
        Prenom_Perso = new QLineEdit(inscrit);
        Prenom_Perso->setObjectName(QStringLiteral("Prenom_Perso"));
        Prenom_Perso->setGeometry(QRect(290, 190, 211, 31));
        Prenom_Perso->setStyleSheet(QStringLiteral("background-color: rgb(66, 66, 66);"));
        Tel = new QLineEdit(inscrit);
        Tel->setObjectName(QStringLiteral("Tel"));
        Tel->setGeometry(QRect(290, 230, 211, 31));
        Tel->setStyleSheet(QStringLiteral("background-color: rgb(66, 66, 66);"));
        Tel->setEchoMode(QLineEdit::Normal);
        Adresse = new QLineEdit(inscrit);
        Adresse->setObjectName(QStringLiteral("Adresse"));
        Adresse->setGeometry(QRect(290, 270, 211, 31));
        Adresse->setStyleSheet(QStringLiteral("background-color: rgb(66, 66, 66);"));
        role = new QComboBox(inscrit);
        role->setObjectName(QStringLiteral("role"));
        role->setGeometry(QRect(300, 400, 211, 31));
        role->setStyleSheet(QStringLiteral("background:rgb(63, 63, 63)"));
        ajout_sinscrire = new QPushButton(inscrit);
        ajout_sinscrire->setObjectName(QStringLiteral("ajout_sinscrire"));
        ajout_sinscrire->setGeometry(QRect(520, 410, 93, 28));
        ajout_sinscrire->setStyleSheet(QStringLiteral("background-color: rgb(63, 63, 63);"));
        supprimer_2 = new QPushButton(inscrit);
        supprimer_2->setObjectName(QStringLiteral("supprimer_2"));
        supprimer_2->setGeometry(QRect(660, 410, 93, 31));
        supprimer_2->setStyleSheet(QLatin1String("\n"
"background-color: rgb(67, 67, 67);"));
        pushButton_78 = new QPushButton(inscrit);
        pushButton_78->setObjectName(QStringLiteral("pushButton_78"));
        pushButton_78->setGeometry(QRect(620, 410, 31, 31));
        pushButton_78->setStyleSheet(QStringLiteral("image:url(:/new/prefix1/delete.png)"));
        label_37 = new QLabel(inscrit);
        label_37->setObjectName(QStringLiteral("label_37"));
        label_37->setGeometry(QRect(180, 110, 91, 31));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_37->setFont(font);
        label_37->setStyleSheet(QStringLiteral(""));
        label_36 = new QLabel(inscrit);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(180, 150, 91, 31));
        label_36->setFont(font);
        label_38 = new QLabel(inscrit);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setGeometry(QRect(180, 200, 91, 21));
        label_38->setFont(font);
        label_39 = new QLabel(inscrit);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setGeometry(QRect(180, 239, 101, 21));
        label_39->setFont(font);
        label_41 = new QLabel(inscrit);
        label_41->setObjectName(QStringLiteral("label_41"));
        label_41->setGeometry(QRect(180, 270, 91, 31));
        label_41->setFont(font);
        label_40 = new QLabel(inscrit);
        label_40->setObjectName(QStringLiteral("label_40"));
        label_40->setGeometry(QRect(180, 400, 111, 20));
        label_40->setFont(font);
        label = new QLabel(inscrit);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(270, 50, 261, 41));
        QFont font1;
        font1.setFamily(QStringLiteral("MV Boli"));
        font1.setPointSize(22);
        label->setFont(font1);
        retourner = new QPushButton(inscrit);
        retourner->setObjectName(QStringLiteral("retourner"));
        retourner->setGeometry(QRect(30, 30, 91, 41));
        retourner->setStyleSheet(QLatin1String("color:rgb(255, 0, 0);\n"
"font: 63 10pt \"Segoe UI Variable Small Semibol\";"));
        sms = new QPushButton(inscrit);
        sms->setObjectName(QStringLiteral("sms"));
        sms->setGeometry(QRect(650, 40, 93, 28));
        password = new QLineEdit(inscrit);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(290, 311, 211, 31));
        password->setStyleSheet(QStringLiteral("background-color: rgb(66, 66, 66);"));
        password->setEchoMode(QLineEdit::Password);
        label_2 = new QLabel(inscrit);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(170, 320, 111, 21));
        QFont font2;
        font2.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        label_2->setFont(font2);

        retranslateUi(inscrit);

        QMetaObject::connectSlotsByName(inscrit);
    } // setupUi

    void retranslateUi(QDialog *inscrit)
    {
        inscrit->setWindowTitle(QApplication::translate("inscrit", "Dialog", Q_NULLPTR));
        label_30->setText(QString());
        label_31->setText(QString());
        role->clear();
        role->insertItems(0, QStringList()
         << QApplication::translate("inscrit", "Admin", Q_NULLPTR)
         << QApplication::translate("inscrit", "ingenieur son", Q_NULLPTR)
         << QApplication::translate("inscrit", "Animateur", Q_NULLPTR)
        );
        ajout_sinscrire->setText(QApplication::translate("inscrit", "s'inscrire", Q_NULLPTR));
        supprimer_2->setText(QApplication::translate("inscrit", "supprimer", Q_NULLPTR));
        pushButton_78->setText(QString());
        label_37->setText(QApplication::translate("inscrit", "ID_Perso:", Q_NULLPTR));
        label_36->setText(QApplication::translate("inscrit", "Nom        :", Q_NULLPTR));
        label_38->setText(QApplication::translate("inscrit", "Prenom   :", Q_NULLPTR));
        label_39->setText(QApplication::translate("inscrit", "Phone     :", Q_NULLPTR));
        label_41->setText(QApplication::translate("inscrit", "Adresse  :", Q_NULLPTR));
        label_40->setText(QApplication::translate("inscrit", "Role        :", Q_NULLPTR));
        label->setText(QApplication::translate("inscrit", "INSCRIPTION", Q_NULLPTR));
        retourner->setText(QApplication::translate("inscrit", "retourner", Q_NULLPTR));
        sms->setText(QApplication::translate("inscrit", "sms", Q_NULLPTR));
        label_2->setText(QApplication::translate("inscrit", "Passsword:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class inscrit: public Ui_inscrit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSCRIT_H
