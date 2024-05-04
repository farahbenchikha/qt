// studio.cpp
#include "studio.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
#include<QTabWidget>
#include <QSortFilterProxyModel>
#include<QDateTime>
studio::studio(int numS, QString nomS, QString descreptionS,int etatS)
{
    this->ID_S = numS;
    this->NOM_S = nomS;
    this->DESCRIPTION_S = descreptionS;
    this->ETAT_S = etatS;
}
 studio::studio(int id)
 {
     this->ID_S=id;
 }

studio::studio() {

    ID_S = 0;
    NOM_S = " ";
    DESCRIPTION_S = " ";
    ETAT_S = 0;
}


QString studio::ajouter() {
    // Vérification de l'unicité du nom
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM STUDIO WHERE NOM_S = :nom");
    checkQuery.bindValue(":nom", NOM_S);
    if (checkQuery.exec() && checkQuery.next()) {
        int count = checkQuery.value(0).toInt();
        if (count > 0) {
            qDebug() << "Erreur : Un studio avec le même nom existe déjà.";
            return "Un studio avec le même nom existe déjà.";
        }
    } else {
        qDebug() << "Erreur lors de la vérification du doublon:" << checkQuery.lastError().text();
        return checkQuery.lastError().text();
    }

    // Vérification de l'unicité de l'ID
    checkQuery.prepare("SELECT COUNT(*) FROM STUDIO WHERE ID_S = :id");
    checkQuery.bindValue(":id", ID_S);
    if (checkQuery.exec() && checkQuery.next()) {
        int count = checkQuery.value(0).toInt();
        if (count > 0) {
            qDebug() << "Erreur : Un studio avec le même ID existe déjà.";
            return "Un studio avec le même ID existe déjà.";
        }
    } else {
        qDebug() << "Erreur lors de la vérification de l'unicité de l'ID:" << checkQuery.lastError().text();
        return checkQuery.lastError().text();
    }

    // Insertion du studio dans la base de données
    QSqlQuery query;
    query.prepare("INSERT INTO STUDIO (ID_S, NOM_S, DESCRIPTION_S, ETAT_S) VALUES (:num, :nom, :desc, :etat)");

    query.bindValue(":num", ID_S);
    query.bindValue(":nom", NOM_S);
    query.bindValue(":desc", DESCRIPTION_S);
    query.bindValue(":etat", ETAT_S);

    if (query.exec()) {
        // Enregistrement de l'action dans l'historique
        QString description = "Ajout du studio " + NOM_S + " (ID: " + QString::number(ID_S) + ")";
        QString errorMsgHistorique = ajouterHistoriqueAjoutStudio(ID_S, QDateTime::currentDateTime(), description);
        if (!errorMsgHistorique.isEmpty()) {
            qDebug() << "Erreur lors de l'enregistrement dans l'historique :" << errorMsgHistorique;
            // Retourner une erreur si l'enregistrement dans l'historique échoue
            return errorMsgHistorique;
        }
        return QString(); // Succès
    } else {
        qDebug() << "Erreur lors de l'ajout:" << query.lastError().text();
        return query.lastError().text();
    }
}

QString studio::ajouterHistoriqueAjoutStudio(int idStudio, const QDateTime& dateAjout, const QString& description) {
    QSqlQuery query;
    query.prepare("INSERT INTO Historique_Ajout_Studio (ID_Studio, Date_Ajout, Description) VALUES (:idStudio, :dateAjout, :description)");
    query.bindValue(":idStudio", idStudio);
    query.bindValue(":dateAjout", dateAjout);
    query.bindValue(":description", description);
    if (query.exec()) {
        return QString();
    } else {
        return query.lastError().text();
    }
}

QSqlQueryModel *studio::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();

    //alloue dynamiquement de la mémoire pour cet objet Ce modèle sera utilisé pour stocker les résultats de la requête SQL.
    QSqlQuery query;
    query.prepare("SELECT * FROM STUDIO");

    // Execute the query
    if (query.exec()) {
        // Set the query result to the model
        model->setQuery(query);
    } else {
        // If an error occurs, print the error message to the console
        qDebug() << "Erreur lors de l'affichage des studios:" << query.lastError().text();
    }

    return model;
}

bool studio::supprimer(int id) {
    QSqlQuery query;
       query.prepare("DELETE FROM STUDIO WHERE ID_S = :id");
       query.bindValue(":id", id);

       if (query.exec()) {
           // Enregistrez la suppression dans l'historique
           QString description = "Suppression du studio avec ID: " + QString::number(id);
           QString errorMsgHistorique = ajouterHistoriqueAjoutStudio(ID_S, QDateTime::currentDateTime(), description);

           if (!errorMsgHistorique.isEmpty()) {
               qDebug() << "Erreur lors de l'enregistrement dans l'historique :" << errorMsgHistorique;
               return false;
           }
           return true; // Deletion successful
       } else {
           lastErrorMessage = query.lastError().text();
           qDebug() << "Erreur lors de la suppression:" << lastErrorMessage;
           return false; // Deletion failed
       }
}


QString studio::modifier(int id) {
    QSqlQuery query;
        query.prepare("UPDATE STUDIO SET NOM_S = :nom, DESCRIPTION_S = :desc, ETAT_S = :etat WHERE ID_S = :id");

        query.bindValue(":nom", NOM_S);
        query.bindValue(":desc", DESCRIPTION_S);
        query.bindValue(":etat", ETAT_S);
        query.bindValue(":id", id);

        if (query.exec()) {
            // Enregistrez la modification dans l'historique
            QString description = "<span style='color: #2E8B57;'>Modification :</span> <strong>" + NOM_S + "</strong> (ID: " + QString::number(id) + ")";
            QString errorMsgHistorique = ajouterHistoriqueAjoutStudio(ID_S, QDateTime::currentDateTime(), description);

            if (!errorMsgHistorique.isEmpty()) {
                qDebug() << "Erreur lors de l'enregistrement dans l'historique :" << errorMsgHistorique;
                return errorMsgHistorique;
            }
            return QString();  // Empty string indicates success
        } else {
            lastErrorMessage = query.lastError().text();
            qDebug() << "Erreur lors de la modification:" << lastErrorMessage;
            return lastErrorMessage;  // Return the error message
        }
}

QSqlQueryModel *studio::chercher(const QString &searchText) {
    QSqlQueryModel *model = new QSqlQueryModel();//stocke les resultat du requette

    QSqlQuery query;
    query.prepare("SELECT ID_S, NOM_S, DESCRIPTION_S, ETAT_S FROM STUDIO WHERE NOM_S LIKE :search");
    query.bindValue(":search", "%" + searchText + "%");

    if (query.exec()) {
        model->setQuery(query);
    } else {
        lastErrorMessage = query.lastError().text();
        qDebug() << "Erreur lors de la recherche:" << lastErrorMessage;
    }

    return model;
}

QSqlQueryModel *studio::trierParId() {
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT * FROM STUDIO ORDER BY ID_S ASC");

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Erreur lors du tri des studios par ID:" << query.lastError().text();
    }

    return model;
}


QSqlQueryModel *studio::afficherStudiosNonOccupes() {
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT * FROM STUDIO WHERE ETAT_S = 0");

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Erreur lors de l'affichage des studios non occupés:" << query.lastError().text();
    }

    return model;
}

bool studio::reserverStudio(const QString& date) {
      QSqlQuery query;

    // Préparez la requête pour insérer la réservation dans la table appropriée
    query.prepare("INSERT INTO RESERVATIONS (ID_S, DATE_RESERVATION) VALUES (:idStudio, TO_DATE(:dateReservation, 'YYYY-MM-DD'))");
    query.bindValue(":idStudio", ID_S); // Utilisez l'ID du studio actuel
    query.bindValue(":dateReservation", date);

    // Exécutez la requête et vérifiez si elle s'est bien déroulée
    if (query.exec()) {
        // Si la réservation a réussi, mettez à jour l'état du studio dans la table des studios
        query.prepare("UPDATE STUDIO SET ETAT_S = 1 WHERE ID_S = :idStudio");
        query.bindValue(":idStudio", ID_S); // Utilisez l'ID du studio actuel

        if (query.exec()) {
            // La réservation et la mise à jour de l'état ont réussi
            return true;
        } else {
            // La mise à jour de l'état a échoué
            qDebug() << "Erreur lors de la mise à jour de l'état du studio après réservation:" << query.lastError().text();
            return false;
        }
    } else {
        // La réservation a échoué
        qDebug() << "Erreur lors de la réservation du studio:" << query.lastError().text();
        return false;
    }
}

QList<QPair<QString, QString>> studio::afficherStudiosReserves() {
    QList<QPair<QString, QString>> studiosReserves;

    QSqlQuery query;
    query.prepare("SELECT STUDIO.NOM_S, RESERVATIONS.DATE_RESERVATION FROM STUDIO INNER JOIN RESERVATIONS ON STUDIO.ID_S = RESERVATIONS.ID_S");

    if (query.exec()) {
        while (query.next()) {
            QString nomStudio = query.value(0).toString();
            QString dateReservation = query.value(1).toString();
            studiosReserves.append(qMakePair(nomStudio, dateReservation));
        }
    } else {
        qDebug() << "Erreur lors de l'affichage des studios réservés:" << query.lastError().text();
    }

    return studiosReserves;
}
