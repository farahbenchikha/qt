
#include "equipement.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
#include<QDateTime>

equipement::equipement(int idEq, QString nomEq, QString discreptionEq, int idStudio)
{
    this->ID_EQ = idEq;
    this->NOM_EQ = nomEq;
    this->DISCREPTION_EQ = discreptionEq;
this->ID_STUDIO = idStudio;
}

equipement::equipement() {

    ID_EQ = 0;
    NOM_EQ = " ";
    DISCREPTION_EQ = " ";
    ID_STUDIO = 0;

}



QString equipement::ajouterHistoriqueAjoutEquipement(int idEquipement, const QDateTime& dateAjout, const QString& description) {
    QSqlQuery query;
    query.prepare("INSERT INTO HISTORIQUE_AJOUT_EQUIPEMENT (ID_EQUIPEMENT, DATE_AJOUTE, DESCRIPTION) VALUES (:idEquipement, :dateAjout, :description)");
    query.bindValue(":idEquipement", idEquipement);
    query.bindValue(":dateAjout", dateAjout);
    query.bindValue(":description", description);
    if (query.exec()) {
        return QString();
    } else {
        return query.lastError().text();
    }
}


QString equipement::ajouter() {
    QSqlQuery query;
        query.prepare("INSERT INTO EQUIPEMENTS (ID_EQ, NOM_EQ, DISCREPTION_EQ,  ID_STUDIO) VALUES (:id, :nom, :desc, :idStudio)");

        query.bindValue(":id", ID_EQ);
        query.bindValue(":nom", NOM_EQ);
        query.bindValue(":desc", DISCREPTION_EQ);
        query.bindValue(":idStudio", ID_STUDIO);

        if (query.exec()) {
            // Appel à la méthode pour ajouter l'historique d'ajout
            QString historiqueError = ajouterHistoriqueAjoutEquipement(ID_EQ, QDateTime::currentDateTime(), "Ajout d'équipement");
            if (!historiqueError.isEmpty()) {
                qDebug() << "Erreur lors de l'ajout de l'historique:" << historiqueError;
                // Gérer l'erreur de l'historique ici
            }
            return QString();
        } else {
            qDebug() << "Erreur lors de l'ajout:" << query.lastError().text();
            return query.lastError().text();
        }
}

QSqlQueryModel *equipement::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();

        // Set up the query to retrieve data from the EQUIPEMENT table
        QSqlQuery query;
        query.prepare("SELECT EQUIPEMENTS.*, STUDIO.NOM_S FROM EQUIPEMENTS LEFT JOIN STUDIO ON EQUIPEMENTS.ID_STUDIO = STUDIO.ID_S");

        // Execute the query
        if (query.exec()) {
            // Set the query result to the model
            model->setQuery(query);
        } else {
            // If an error occurs, print the error message to the console
            lastErrorMessage = query.lastError().text();
            qDebug() << "Erreur lors de l'affichage des équipements:" << lastErrorMessage;
            // Assurez-vous de libérer la mémoire du modèle
            delete model;
            model = nullptr;
        }

        return model;
}

bool equipement::supprimer(int ide) {

    QSqlQuery query;

       // Début de la transaction
       query.exec("START TRANSACTION");

       // Suppression de l'équipement spécifié
       query.prepare("DELETE FROM EQUIPEMENTS WHERE ID_EQ = :ide");
       query.bindValue(":ide", ide);

       if (!query.exec()) {
           // En cas d'erreur, annulation des modifications (rollback)
           query.exec("ROLLBACK");

           lastErrorMessage = query.lastError().text();
           qDebug() << "Erreur lors de la suppression de l'équipement:" << lastErrorMessage;
           return false; // Suppression échouée
       }

       // Ajout d'une entrée dans l'historique de suppression
           QString historiqueError = ajouterHistoriqueAjoutEquipement(ID_EQ, QDateTime::currentDateTime(), "suppression d'équipement");
       if (!historiqueError.isEmpty()) {
           qDebug() << "Erreur lors de l'ajout de l'historique de suppression:" << historiqueError;
           // Gérer l'erreur de l'historique ici
       }

       // Validation de la transaction (commit)
       query.exec("COMMIT");
       return true; // Suppression réussie

}

QString equipement::modifier(int id) {
    QSqlQuery query;
    query.prepare("UPDATE EQUIPEMENTS SET NOM_EQ = :nom, DISCREPTION_EQ = :desc WHERE ID_EQ = :id");

    query.bindValue(":nom", NOM_EQ);
    query.bindValue(":desc", DISCREPTION_EQ);

    query.bindValue(":id", id);


    if (query.exec()) {
        return QString(); // Empty string indicates success
    } else {
        lastErrorMessage = query.lastError().text();
        qDebug() << "Erreur lors de la modification:" << lastErrorMessage;
        return lastErrorMessage; // Return the error message
    }
}

QSqlQueryModel *equipement::chercher(const QString &searchText) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT ID_EQ, NOM_EQ, DISCREPTION_EQ FROM EQUIPEMENTS WHERE NOM_EQ LIKE :search");
    query.bindValue(":search", "%" + searchText + "%");

    if (query.exec()) {
        model->setQuery(query);
    } else {
        lastErrorMessage = query.lastError().text();
        qDebug() << "Erreur lors de la recherche:" << lastErrorMessage;
    }

    return model;
}

QSqlQueryModel *equipement::trierParNom() {
    QSqlQueryModel *model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT * FROM EQUIPEMENTS ORDER BY NOM_EQ ASC");

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Erreur lors du tri des équipements par nom:" << query.lastError().text();
    }

    return model;
}

