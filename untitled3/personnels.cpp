#include "personnels.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include "cryptage.h"

personnels::personnels()
{
   ID_PERSO = 0;

   NOM_PERSO = "";
   PRENOM_PERSO = "";
   ADRESSE_PERSO = "";
   TEL_PERSO = "";
   ROLE_PERSO = "";
   Password ="";
  //CARTE ="";

}

personnels::personnels(int ID_PERSO, QString ROLE_PERSO, QString NOM_PERSO, QString PRENOM_PERSO, QString ADRESSE_PERSO, QString TEL_PERSO, QString Password)
{
    this->ID_PERSO = ID_PERSO;
    this->NOM_PERSO = NOM_PERSO;
    this->PRENOM_PERSO = PRENOM_PERSO;
    this->ADRESSE_PERSO = ADRESSE_PERSO;
    this->TEL_PERSO = TEL_PERSO;
    this->ROLE_PERSO = ROLE_PERSO;
    this->Password = Password;
     //this->CARTE = CARTE;

}

bool personnels::ajouter()
{
    QSqlQuery query;
    QString hashedPassword = cryptage::hashPassword(Password);

    query.prepare("INSERT INTO PERSONNELS (NOM_PERSO, PRENOM_PERSO, ADRESSE_PERSO, TEL_PERSO, ID_PERSO, ROLE_PERSO, PASSWORD) "
                  "VALUES (:nom_PERSO, :prenom_PERSO, :adresse_PERSO, :tel_PERSO, :id_perso, :role_PERSO, :password)");
     query.bindValue(":id_perso", ID_PERSO);
    query.bindValue(":nom_PERSO", NOM_PERSO);
    query.bindValue(":prenom_PERSO", PRENOM_PERSO);
    query.bindValue(":adresse_PERSO", ADRESSE_PERSO);
    query.bindValue(":tel_PERSO",TEL_PERSO);

    query.bindValue(":role_PERSO", ROLE_PERSO);
     query.bindValue(":password", Password);
     //query.bindValue(":carte", CARTE);


    if (query.exec())
    {
        return true;
    }
    else
    {
        qDebug() << "Error in adding personnel:" << query.lastError().text();
        return false;
    }
}
bool personnels::emailExistsInDatabase(const QString &email) {
    // Établir la connexion à la base de données

    // Préparer la requête SQL pour sélectionner les enregistrements correspondants
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM PERSONNELS WHERE ADRESSE_PERSO = :email");
    query.bindValue(":email", email);

    // Exécuter la requête
    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0; // Si count > 0, l'e-mail existe déjà dans la base de données
    } else {
        // Gérer les erreurs d'exécution de la requête
        qDebug() << "Erreur lors de la vérification de l'existence de l'adresse e-mail dans la base de données :" << query.lastError().text();
        return false;
    }
}

QSqlQueryModel* personnels::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM PERSONNELS");
    if (model->lastError().isValid()) {
        qDebug() << "Erreur lors de la requête SQL:" << model->lastError().text();

    }


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Perso"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_PERSO"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_PERSO"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ROLE_PERSO"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE_PERSO"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL_PERSO"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("PASSWORD"));


    return model;
}

bool personnels::modifier(int ID_PERSO, QString nv_nom, QString nv_prenom, QString nv_adresse, QString nv_tel, QString nv_role, QString nv_password)
{
    QSqlQuery query;

    query.prepare("UPDATE PERSONNELS SET NOM_PERSO = :nv_nom, PRENOM_PERSO = :nv_prenom, "
                  "ADRESSE_PERSO = :nv_adresse, TEL_PERSO = :nv_tel, ROLE_PERSO = :nv_role, PASSWORD= :nv_password "
                  "WHERE ID_PERSO = :id_perso");


    query.bindValue(":id_perso", ID_PERSO);
    query.bindValue(":nv_nom", nv_nom);
    query.bindValue(":nv_prenom", nv_prenom);
    query.bindValue(":nv_adresse", nv_adresse);
    query.bindValue(":nv_tel", nv_tel);
    query.bindValue(":nv_role", nv_role);
     query.bindValue(":nv_password", nv_password);


    if (query.exec())
    {
        return true;
    }
    else
    {
        qDebug() << "Erreur de modification:" << query.lastError().text();
        return false;
    }
}
bool personnels::supprimer(int ID_PERSO)
{
    QSqlQuery query;
    QString res=QString::number(ID_PERSO);
    query.prepare("DELETE FROM PERSONNELS WHERE ID_PERSO =:ID_PERSO");
    query.bindValue(":ID_PERSO",res);
    return query.exec();

}
QSqlQueryModel* personnels :: TRIER(bool ordreAscendant)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString ordreSQL = ordreAscendant ? "ASC" : "DESC";

    model->setQuery("SELECT * FROM PERSONNELS ORDER BY NOM_PERSO " + ordreSQL);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Perso"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_PERSO"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM_PERSO"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE_PERSO"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TEL_PERSO"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ROLE_PERSO"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("PASSWORD"));


    return model;
}
bool personnels::rechercher(int ID_PERSO)
{
   QSqlQuery query;
   query.prepare("SELECT * FROM PERSONNELS WHERE ID_PERSO = :ID_PERSO");
   query.bindValue(":ID_PERSO", ID_PERSO);

   if (query.exec() && query.next()) {

       return true;
   } else {

       return false;
   }
}
int personnels::getRoleCount(const QString &role)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM personnels WHERE ROLE_PERSO = ?");
    query.addBindValue(role);
    query.exec();

    if (query.next()) {
        return query.value(0).toInt();
    }

    return 0;
}
int personnels::getTotalPersonnes()
{
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM PERSONNELS");

    if (query.next()) {
        return query.value(0).toInt();
    }

    return 0;
}
bool personnels::connexion(const QString& email, const QString& password) {
    QSqlQuery query;
    //QString hashedTel = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
    query.prepare("SELECT COUNT(*) FROM PERSONNELS WHERE ADRESSE_PERSO = :email AND PASSWORD = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0; // Si count est supérieur à 0, cela signifie que l'utilisateur existe
    }

    return false;
}


