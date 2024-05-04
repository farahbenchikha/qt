/*#include "decryptage.h"
#include "qaesencryption.h"

QString Decryptage::decrypt(const QString& encryptedText)
{
    // Créez une instance de QAesEncryption avec votre clé de déchiffrement.
    QAesEncryption aesEncryption(QAESEncryption::AES_256, QAESEncryption::ECB);

    // Définissez votre clé de déchiffrement.
    QByteArray decryptionKey = "Votre clé de déchiffrement";

    // Définissez votre texte crypté en tant que QByteArray.
    QByteArray encryptedData = QByteArray::fromHex(encryptedText.toLatin1());

    // Déchiffrez le texte.
    QByteArray decryptedData = aesEncryption.decode(encryptedData, decryptionKey);

    // Retournez le texte déchiffré en tant que QString.
    return QString::fromUtf8(decryptedData);
}
*/
