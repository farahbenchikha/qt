#include "enregistrement.h"
#include<string>
#include <QDebug>
#include <QVector>
#include<QSqlError>
#include <QDateTime>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QVariant>
#include <QSqlQuery>
#include <QHeaderView>
#include <QObject>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <iostream>

enregistrement::enregistrement()
{

}

enregistrement::enregistrement(int ID_ENR, QString NOM_ENR, QString QUALITE_ENR , int ID_EM_ENR , QString PATH_ENR)
{
    this->NOM_ENR=NOM_ENR;
    this->QUALITE_ENR=QUALITE_ENR;
    this->ID_ENR=ID_ENR;
    this->ID_EM_ENR=ID_EM_ENR;
    this->PATH_ENR=PATH_ENR;
}




bool enregistrement::ajouter()
{
    if (NOM_ENR.isEmpty() || QUALITE_ENR.isEmpty() || PATH_ENR.isEmpty()) {
        qDebug() << "Erreur : Veuillez remplir tous les champs obligatoires.";
        return false;
    }

    QSqlQuery query;
    QString res = QString::number(ID_ENR);
    query.prepare("INSERT INTO ENREGISTREMENT (ID_ENR, NOM_ENR, QUALITE_ENR, ID_EM_ENR , PATH_ENR) VALUES (:ID_ENR, :NOM_ENR, :QUALITE_ENR, :ID_EM_ENR , :PATH_ENR)");
    query.bindValue(":ID_ENR", res);
    query.bindValue(":NOM_ENR", NOM_ENR);
    query.bindValue(":QUALITE_ENR", QUALITE_ENR);
    query.bindValue(":ID_EM_ENR", ID_EM_ENR);
    query.bindValue(":PATH_ENR", PATH_ENR);

    // Exécuter la requête d'insertion
    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion de l'enregistrement :" << query.lastError().text();
        return false;
    }


    return true;
}

QSqlQueryModel* enregistrement::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT  ID_ENR, NOM_ENR, ID_EM_ENR ,PATH_ENR, QUALITE_ENR FROM ENREGISTREMENT");
    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, tr("ID Emission"));
        model->setHeaderData(3, Qt::Horizontal, tr("Path"));
        model->setHeaderData(4, Qt::Horizontal, tr("Qualité"));
        return model;
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        delete model;
        return nullptr;
    }
}

 bool enregistrement::supprimer(int id_enr, QString path)
 {

         if (id_enr <= 0) {
             qDebug() << "Erreur : ID invalide.";
             return false;
         }
         // supprimer le video avant l'enregistrement
         QString baseDir = QCoreApplication::applicationDirPath();
         QString absoluteFilePath = "C:\\Users\\farah\\Downloads\\2a11-cr-er-une-quipe-visiondesk_2a11-main\\2a11-cr-er-une-quipe-visiondesk_2a11-main\\interf\\qt\\build-untitled3-Desktop_Qt_5_9_9_MinGW_32bit-Debug\\" + path;

         QFile file(absoluteFilePath);

         if (file.exists()) {
             if (file.remove()) {
                 QSqlQuery query;
                     query.prepare("DELETE FROM ENREGISTREMENT WHERE ID_ENR = :id_enr");
                     query.bindValue(":id_enr", id_enr);
                     if (query.exec()) {
                         return true;
                     } else {
                         qDebug() << "Erreur lors de la suppression de l'enregistrement :" << query.lastError().text();
                         return false;
                     }
             } else {
                 qDebug() << "Error deleting Video.";
                 return false;
             }
         } else {
             qDebug() << "Video does not exist.";
             return false;
         }


 }


/*
 bool enregistrement::ajouterHistoriqueModification(int id_enr, const QString &utilisateur, const QString &description)
 {
     QSqlQuery query;
     query.prepare("INSERT INTO Historique (ID_ENR, Date_Modification, Utilisateur_Modification, Description) "
                   "VALUES (:id_enr, :date_modification, :utilisateur, :description)");
     query.bindValue(":id_enr", id_enr);
     query.bindValue(":date_modification", QDateTime::currentDateTime()); // Date et heure actuelles
     query.bindValue(":utilisateur", utilisateur);
     query.bindValue(":description", description);

     return query.exec();
 }
*/

 bool enregistrement::modifier(int ID_ENR, QString NOM_ENR, QString QUALITE_ENR,  int ID_EM_ENR, QString PATH_ENR )
 {
     QSqlQuery checkQuery;

     if (NOM_ENR.isEmpty() || QUALITE_ENR.isEmpty() || PATH_ENR.isEmpty()) {
         qDebug() << "Erreur : Veuillez remplir tous les champs obligatoires.";
         return false;
     }

         QSqlQuery query;
         query.prepare("UPDATE ENREGISTREMENT SET NOM_ENR = :nom_enr, QUALITE_ENR = :qualite_enr, ID_EM_ENR = :id_em_enr, PATH_ENR = :path WHERE ID_ENR = :id_enr");
         query.bindValue(":id_enr", ID_ENR);
         query.bindValue(":nom_enr", NOM_ENR);
         query.bindValue(":qualite_enr", QUALITE_ENR);
         query.bindValue(":path", PATH_ENR);
         query.bindValue(":id_em_enr", ID_EM_ENR);
         if (query.exec()) {
                          return true;

     } else {
         qDebug() << "Erreur lors de la vérification de l'existence de l'ID :" << checkQuery.lastError().text();
         return false;
     }
 }

 bool enregistrement::rechercherParNom(const QString &nom)
 {
     // Préparer la requête pour compter le nombre d'enregistrements avec le nom spécifié
     QSqlQuery checkQuery;
     checkQuery.prepare("SELECT COUNT(*) FROM ENREGISTREMENT WHERE NOM_ENR = :nom");
     checkQuery.bindValue(":nom", nom);

     // Exécuter la requête
     if (checkQuery.exec() && checkQuery.next()) {
         // Récupérer le nombre d'enregistrements avec le nom spécifié
         int count = checkQuery.value(0).toInt();

         // Vérifier s'il y a au moins un enregistrement avec le nom spécifié
         if (count > 0) {
             // Le nom existe dans la base de données, retourner true
             return true;
         } else {
             // Le nom n'existe pas dans la base de données, retourner false
             return false;
         }
     } else {
         // Une erreur s'est produite lors de l'exécution de la requête, afficher un message de débogage et retourner false
         qDebug() << "Erreur lors de la recherche par nom :" << checkQuery.lastError().text();
         return false;
     }
 }

 bool enregistrement::trierParNom(QSqlQueryModel *model) {
     QSqlQuery query;
     query.prepare("SELECT * FROM ENREGISTREMENT ORDER BY NOM_ENR ASC");

     // Exécuter la requête pour obtenir les enregistrements triés par nom
     if (query.exec()) {
         // Mettre à jour le modèle avec les enregistrements triés
         model->setQuery(query);

         // Assurer que le modèle est prêt à être utilisé
         if (model->lastError().isValid()) {
             qDebug() << "Erreur lors de la mise à jour du modèle après le tri :" << model->lastError().text();
             return false;
         }

         return true;
     } else {
         qDebug() << "Erreur lors du tri des enregistrements par nom :" << query.lastError().text();
         return false;
     }
 }


 bool enregistrement::trierParIdCroissant()
 {
     QSqlQuery query;
        QSqlQueryModel *model = new QSqlQueryModel();
     query.prepare("SELECT * FROM ENREGISTREMENT ORDER BY ID_ENR ASC");

     // Exécuter la requête pour obtenir les enregistrements triés par ID croissant
     if (query.exec()) {
         // Mettre à jour le modèle avec les enregistrements triés
         model->setQuery(query);

         // Assurer que le modèle est prêt à être utilisé
         if (model->lastError().isValid()) {
             qDebug() << "Erreur lors de la mise à jour du modèle après le tri :" << model->lastError().text();
             return false;
         }

         return true;
     } else {
         qDebug() << "Erreur lors du tri des enregistrements par ID croissant :" << query.lastError().text();
         return false;
     }
 }

 bool enregistrement::trierParIdDecroissant()
 {
     QSqlQuery query;
     QSqlQueryModel *model = new QSqlQueryModel();
     query.prepare("SELECT * FROM ENREGISTREMENT ORDER BY ID_ENR DESC");

     // Exécuter la requête pour obtenir les enregistrements triés par ID décroissant
     if (query.exec()) {
         // Mettre à jour le modèle avec les enregistrements triés
         model->setQuery(query);

         // Assurer que le modèle est prêt à être utilisé
         if (model->lastError().isValid()) {
             qDebug() << "Erreur lors de la mise à jour du modèle après le tri :" << model->lastError().text();
             return false;
         }

         return true;
     } else {
         qDebug() << "Erreur lors du tri des enregistrements par ID décroissant :" << query.lastError().text();
         return false;
     }
 }

 QSqlQueryModel* enregistrement::filtrerParType(QString type)
 {
     QSqlQueryModel *model = new QSqlQueryModel();
     QSqlQuery query;
     query.prepare("SELECT * FROM enregistrement WHERE TYPE_ENR = :type");
     query.bindValue(":type", type);
     query.exec();
     model->setQuery(query);
     return model;
 }
 QSqlQueryModel* enregistrement::filtrerParQualite(QString qualite)
 {
     QSqlQueryModel *model = new QSqlQueryModel();
     QSqlQuery query;
     query.prepare("SELECT * FROM enregistrement WHERE QUALITE_ENR = :qualite");
     query.bindValue(":qualite", qualite);
     query.exec();
     model->setQuery(query);
     return model;
 }
 QSqlQueryModel* enregistrement::filtrerParNom(QString nom)
 {
     QSqlQueryModel *model = new QSqlQueryModel();
     QSqlQuery query;
     query.prepare("SELECT * FROM enregistrement WHERE NOM_ENR LIKE :nom");
     query.bindValue(":nom", "%" + nom + "%");
     query.exec();
     model->setQuery(query);
     return model;
 }
 void enregistrement::calculerStatistiquesParType(int &nombreEmissions, int &nombrePublicites)
 {
     // Réinitialiser les compteurs
     nombreEmissions = 0;
     nombrePublicites = 0;

     // Récupérer les données de la base de données ou d'où vous stockez les enregistrements
     QSqlQuery query;
     query.prepare("SELECT TYPE_ENR FROM ENREGISTREMENT");

     if (query.exec()) {
         while (query.next()) {
             QString type = query.value(0).toString();
             // Vérifier le type et incrémenter le compteur approprié
             if (type == "emission") {
                 nombreEmissions++;
             } else if (type == "publicite") {
                 nombrePublicites++;
             }
         }
     } else {
         qDebug() << "Erreur lors de la récupération des enregistrements :" << query.lastError().text();
     }
 }
 int enregistrement::getTotalEnregistrements()
 {
     QSqlQuery query;
     query.exec("SELECT COUNT(*) FROM ENREGISTREMENT");
     if (query.next()) {
         return query.value(0).toInt();
     } else {
         return 0; // Retourner 0 si aucune donnée n'est disponible
     }
 }

 int enregistrement::getNombreParType(const QString &type)
 {
     QSqlQuery query;
     query.prepare("SELECT COUNT(*) FROM ENREGISTREMENT WHERE TYPE_ENR = ?");
     query.bindValue(0, type);
     query.exec();
     if (query.next()) {
         return query.value(0).toInt();
     } else {
         return 0; // Retourner 0 si aucune donnée n'est disponible
     }
 }
