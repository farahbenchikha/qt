#include "mdp.h"
#include "ui_mdp.h"
#include "personnels.h"
#include "cryptage.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDateTime>
#include <QDebug>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include "smtp.h"
#include"smtpp.h"


mdp::mdp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mdp)
{
    ui->setupUi(this);


    connect(ui->envoyer, SIGNAL(clicked()), this, SLOT(on_envoyer_clicked()));
}

mdp::~mdp()
{
    delete ui;

}


void mdp::on_envoyer_clicked()
{
    sendMaile();
}

/*void mdp::sendResetEmail(const QString& emailAddress, const QString& resetToken)
{
    // Code pour envoyer un e-mail à l'adresse 'emailAddress' avec le lien de réinitialisation contenant 'resetToken'
    // Utilisez votre propre logique ou une bibliothèque externe pour l'envoi d'e-mails
    qDebug() << "Sending reset email to" << emailAddress << "with token" << resetToken;
}

QString mdp::generateToken()
{
    // Générer une chaîne aléatoire basée sur le timestamp actuel
    QString timestamp = QString::number(QDateTime::currentMSecsSinceEpoch());
    QByteArray hash = QCryptographicHash::hash(timestamp.toUtf8(), QCryptographicHash::Md5);
    return hash.toHex();
}

void mdp::resetPassword(const QString& emailAddress, const QString& newPassword)
{
    // Code pour réinitialiser le mot de passe de l'utilisateur associé à 'emailAddress' avec 'newPassword'
    // Assurez-vous que vous utilisez une méthode sécurisée pour stocker le mot de passe
    qDebug() << "Resetting password for" << emailAddress << "to" << newPassword;
}

void mdp::on_reset_clicked()
{
    QString userEmail = ui->adr->text();
        QString resetToken = ui->token->text();
        QString newPassword = ui->nmdp->text();

        // Vérification de la validité du token (vérification si le token est associé à l'utilisateur et non expiré)

        // Réinitialisation du mot de passe
        resetPassword(userEmail, newPassword);

        // Afficher un message à l'utilisateur pour lui indiquer que le mot de passe a été réinitialisé
        qDebug() << "Password reset successful for" << userEmail;

}
*/
/*QString mdp::getTelPersoFromDatabase(const QString& idPerso)
{
    // Déclarer un objet QSqlQuery pour exécuter la requête SQL
    QSqlQuery query;

    // Préparer la requête SQL avec une clause WHERE pour rechercher l'ID_PERSO donné
    query.prepare("SELECT TEL_PERSO FROM PERSONNELS WHERE ID_PERSO = :idPerso");
    query.bindValue(":idPerso", idPerso);

    // Exécuter la requête SQL
    if (query.exec() && query.next()) {
        // Si la requête a réussi et a trouvé un enregistrement, récupérer le contenu du champ TEL_PERSO
        return query.value(0).toString();
    } else {
        // Si la requête a échoué ou n'a trouvé aucun enregistrement, retourner une chaîne vide
        return QString();
    }
}
*/
/*bool mdp::emailExistsInDatabase(const QString& email)
{
    // Déclarer un objet QSqlQuery pour exécuter la requête SQL
    QSqlQuery query;

    // Préparer la requête SQL avec une clause WHERE pour rechercher l'adresse e-mail donnée
    query.prepare("SELECT COUNT(*) FROM PERSONNELS WHERE ADRESSE_PERSO = :email");
    query.bindValue(":email", email);

    // Exécuter la requête SQL
    if (query.exec() && query.next()) {
        // Si la requête a réussi et a retourné un résultat non nul, cela signifie que l'adresse e-mail existe dans la base de données
        return query.value(0).toInt() > 0;
    } else {
        // Si la requête a échoué, retourner false par défaut
        return false;
    }
}
-*
void mdp::sendMaile()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toUShort());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void mdp::mailSente(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
*/
void mdp::sendMaile()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toUShort());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->text());
}

void mdp::mailSente(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}
