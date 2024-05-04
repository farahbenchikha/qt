#include "sms.h"
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

SMS::SMS(QObject *parent) : QObject(parent) {}
void SMS::sendSMS(const QString &destinataire, const QString &message)
{
    envoyerSMS(destinataire, message);
}


void SMS::replyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        // Afficher un message d'erreur
        QMessageBox::warning(nullptr, "Erreur", "Une erreur est survenue lors de l'envoi du SMS : " + reply->errorString());
    }
    // Libérer la mémoire
    reply->deleteLater();
}

void SMS::envoyerSMS(const QString &destinataire, const QString &message)
{
    // SID et auth token de Twilio
    QString sid = "ACc56b407955c9008dfe67c3355a592095";
    QString authToken = "4c77f78ea422b4d6f70e07639c082922";

    // Construire l'URL de l'API Twilio
    QString url = "https://api.twilio.com/2010-04-01/Accounts/" + sid + "/Messages.json";

    // Créer le gestionnaire de réseau
    QNetworkAccessManager *networkAccessManager = new QNetworkAccessManager();
    networkAccessManager->setNetworkAccessible(QNetworkAccessManager::Accessible); // Définir l'accessibilité du réseau
    connect(networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    // Construire les données de la requête
    QByteArray postData;
    postData.append("To=" + destinataire.toUtf8());
    postData.append("&From=+12563715374");
    postData.append("&Body=" + message.toUtf8());

    // Créer la requête HTTP
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("Authorization", "Basic " + QByteArray(QString("%1:%2").arg(sid).arg(authToken).toUtf8()).toBase64());

    // Envoyer la requête
    networkAccessManager->post(request, postData);
}
