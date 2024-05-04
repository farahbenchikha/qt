#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("mayar");
db.setUserName("emna");//inserer nom de l'utilisateur
db.setPassword("emna");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::closeconnect()
{
    db.close();
}
