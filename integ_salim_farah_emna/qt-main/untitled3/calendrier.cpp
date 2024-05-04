#include "calendrier.h"
#include "ui_calendrier.h"
#include "studio.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QMessageBox>
calendrier::calendrier(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::calendrier)
{
    ui->setupUi(this);

    studio studioManager;
    QSqlQueryModel *modelStudios = studioManager.afficherStudiosNonOccupes();

    // Vérifier si le modèle est valide
    if (modelStudios) {
        // Afficher les studios dans le QListWidget
        for (int i = 0; i < modelStudios->rowCount(); ++i) {
            QString nomStudio = modelStudios->index(i, 1).data().toString(); // Nom du studio
            ui->listWidget_studios->addItem(nomStudio);
        }

        // Nettoyer la mémoire allouée pour le modèle
        delete modelStudios;
    } else {
        qDebug() << "Impossible d'afficher les studios non occupés.";
    }
    QList<QPair<QString, QString>> studiosReserves = studioManager.afficherStudiosReserves();

    for (const QPair<QString, QString>& studioReserve : studiosReserves) {
        QString nomStudio = studioReserve.first;
        QString dateReservation = studioReserve.second;
        QString itemText = "Studio: " + nomStudio + " - Date: " + dateReservation;
        ui->listWidgetRES->addItem(itemText);
    }
}

calendrier::~calendrier()
{
    delete ui;
}



void calendrier::on_pushButton_reservation_clicked()
{
    if (ui->listWidget_studios->currentRow() == -1) {
            QMessageBox::warning(this, "Attention", "Veuillez sélectionner un studio dans la liste.");
            return;
        }

        // Récupérer la date sélectionnée
        QDate selectedDate = ui->calendarWidget->selectedDate();

        // Récupérer l'ID du studio sélectionné
        QModelIndex selectedIndex = ui->listWidget_studios->currentIndex();
        int idStudio = selectedIndex.row() + 1; // Supposons que les ID des studios commencent à partir de 1

        // Réserver le studio pour la date sélectionnée
        studio studioSelected(idStudio);
        int reservationID = studioSelected.reserverStudio(selectedDate.toString("yyyy-MM-dd"));

        if (reservationID != -1) {
            QMessageBox::information(this, "Succès", "Studio réservé avec succès pour la date " + selectedDate.toString("dd/MM/yyyy") + " avec l'ID de réservation : " + QString::number(reservationID));
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la réservation du studio.");
        }
}
