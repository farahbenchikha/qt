#include "inscrit.h"
#include "ui_inscrit.h"
#include"personnels.h"
#include"connection.h"
#include"mainwindow.h"
//#include<QTimer>
#include<QString>
#include <QTextStream>
//#include<QPdfWriter>
//#include <QPrinter>
//#include <QTextDocument>
//#include<QDateTime>
#include<QMessageBox>
#include<QObject>
#include<QTableView>
#include<QSqlQueryModel>
#include<QSqlError>
#include<QDebug>
#include<QWidget>
#include<QtWidgets>
//#include<QPainter>
#include <QTextDocument>
#include <QFileDialog>
#include<sms.h>
//#include<QtCharts>

inscrit::inscrit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inscrit)

{
    ui->setupUi(this);
    connect(ui->ajout_sinscrire, SIGNAL(clicked()), this, SLOT(on_ajout_sinscrire_clicked()));
     connect(ui->supprimer_2, SIGNAL(clicked()), this, SLOT(on_supprimer_2_clicked()));
     connect(ui->retourner, SIGNAL(clicked()), this, SLOT(on_retourner_clicked()));
     qsrand(QTime::currentTime().msec());
}

inscrit::~inscrit()
{
    delete ui;
}
void inscrit::on_ajout_sinscrire_clicked()
{
    // Extract user information from the input fields
    int ID_PERSO = ui->ID_Perso->text().toInt();
    QString ROLE_PERSO = ui->role->currentText();
    QString Nom_Perso = ui->Nom_Perso->text().trimmed();
    QString PRENOM_PERSO = ui->Prenom_Perso->text().trimmed();
    QString ADRESSE_PERSO = ui->Adresse->text().trimmed();
    QString TEL_PERSO = ui->Tel->text().trimmed();
    QString PASSWORD = ui->password->text().trimmed();
    //QString carte = ui->carte->text().trimmed();

    // Check if all required fields are filled
    if (Nom_Perso.isEmpty() || PRENOM_PERSO.isEmpty() || ADRESSE_PERSO.isEmpty() || TEL_PERSO.isEmpty() || PASSWORD.isEmpty()) {
        QMessageBox::warning(this, tr("Champs manquants"), tr("Tous les champs doivent être remplis."));
        return;
    }

    // Validate the email address format
    QRegExp regexEmail("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    if (!regexEmail.exactMatch(ADRESSE_PERSO)) {
        QMessageBox::warning(this, tr("Format d'adresse e-mail invalide"), tr("Veuillez entrer une adresse e-mail valide."));
        return;
    }

    // Check if the email address already exists in the database
    personnels verifierEmail;
    if (verifierEmail.emailExistsInDatabase(ADRESSE_PERSO)) {
        QMessageBox::warning(this, tr("Adresse e-mail existante"), tr("L'adresse e-mail saisie existe. Veuillez taper une autre adresse."));
        return;
    }

    // Check the ID format
    personnels verifierID;
    if (verifierID.rechercher(ID_PERSO)) {
        QMessageBox::warning(this, tr("ID existant"), tr("L'ID saisi existe déjà."));
        return;
    }

    // Validate the phone number format
    QRegExp regexTel("^\\+216\\d{8}$");
    if (!regexTel.exactMatch(TEL_PERSO)) {
        QMessageBox::warning(this, tr("Format téléphone invalide"), tr("Le téléphone doit commencer par +216 et être suivi de 8 chiffres."), QMessageBox::Ok);
        return;
    }
    // Generate a confirmation code (you can implement this function)
    QString confirmationCode = generateConfirmationCode();

    // Create the object personnels and add it to the database
    personnels p(ID_PERSO, ROLE_PERSO, Nom_Perso, PRENOM_PERSO, ADRESSE_PERSO, TEL_PERSO, PASSWORD);
    bool test = p.ajouter();

    // Display the result
    if (test) {
        // Send confirmation message to the user's phone number
        QString confirmationMessage = "Confirmation de votre inscription. Votre code de confirmation est : " + confirmationCode;
        SMS sms;
        sms.sendSMS(TEL_PERSO, confirmationMessage);

        // Prompt user for confirmation
        QString userConfirmation = QInputDialog::getText(this, tr("Vérification SMS"), tr("Un code de confirmation a été envoyé à votre numéro de téléphone. Veuillez saisir le code reçu :"));

        // Verify user confirmation
        if (userConfirmation == confirmationCode) {
            // Show confirmation dialog
            QMessageBox::information(this, tr("Inscription réussie"), tr("Votre inscription a été effectuée avec succès."), QMessageBox::Ok);
        } else {
            // Invalid confirmation code
            QMessageBox::critical(this, tr("Code de confirmation invalide"), tr("Le code de confirmation saisi est incorrect. Veuillez réessayer."), QMessageBox::Ok);
        }
    } else {
        QMessageBox::critical(this, tr("Erreur"), tr("L'inscription n'a pas pu être effectuée."), QMessageBox::Ok);
    }
}
void inscrit::on_supprimer_2_clicked()
{    personnels p;

    int ID_PERSO=ui->ID_Perso->text().toInt();
    bool test=p.supprimer(ID_PERSO);
    if(test)
    {
        //ui->tableau->setModel(p.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("suppression effectuee\n""click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::information(nullptr, QObject::tr("not ok"),QObject::tr("suppression n'as pas effectuee\n""click cancel to exit."),QMessageBox::Cancel);
}
QString inscrit::generateConfirmationCode()
{
    // Generate a random code here
    // For simplicity, let's generate a 6-digit random number
    QString code;
    for (int i = 0; i < 6; ++i) {
        code.append(QString::number(qrand() % 10)); // Append a random digit (0-9)
    }
    return code;
}

void inscrit::on_retourner_clicked()
{
    this->close();

       // Afficher la fenêtre de connexion
       login *loginWindow = new login();
       loginWindow->show();
}

void inscrit::on_sms_clicked()
{
    QString destinataire = "+21656398513"; // Numéro de téléphone du destinataire
    QString message = ui->Tel->text();

    // Préfixez l'appel avec le nom de la classe SMS
    SMS sms;
    sms.envoyerSMS(destinataire, message);
}
