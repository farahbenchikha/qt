#include "cryptage.h"
#include "qaesencryption.h"


QString cryptage::hashPassword(const QString& password)
{
    // Utilisation de l'algorithme de hachage SHA-256 pour hasher le mot de passe
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return QString(hashedPassword.toHex());
}
