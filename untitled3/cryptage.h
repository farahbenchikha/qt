#ifndef CRYPTAGE_H
#define CRYPTAGE_H
#include <QString>
#include <QCryptographicHash>
#include <QMainWindow>
#include <QObject>
#include <QWidget>

class cryptage
{
public:
    cryptage();
    static QString hashPassword(const QString& password);
};

#endif // CRYPTAGE_H
