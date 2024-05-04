#ifndef SMS_H
#define SMS_H

#include <QObject>
#include <QNetworkReply>

class SMS : public QObject
{
    Q_OBJECT

public:
    explicit SMS(QObject *parent = nullptr);

    // Fonction pour envoyer un SMS
    void sendSMS(const QString &destinataire, const QString &message);

private slots:
    // Slot pour gérer la réponse de la requête HTTP
    void replyFinished(QNetworkReply *reply);

public: // Déclarer la fonction envoyerSMS comme public
    // Fonction pour envoyer réellement le SMS via l'API Twilio
    void envoyerSMS(const QString &destinataire, const QString &message);
};

#endif // SMS_H
