#include "mainwindow.h"
#include "connection.h"
#include "login.h"
#include "arduino.h" // Ajout de l'en-tête pour la classe Arduino
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QApplication>
#include <QCoreApplication>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Créer une instance de la classe login
    login loginDialog;

    // Afficher la fenêtre de connexion en premier
    loginDialog.show();

    // Créer une instance de la classe Arduino pour la communication avec la carte Arduino
    Arduino arduino;

    // Connexion à la carte Arduino
    int arduinoConnectResult = arduino.connect_arduino();
    if (arduinoConnectResult == 0) {
        qDebug() << "Connexion à la carte Arduino réussie.";

        // Lecture des données de la carte RFID à partir de l'Arduino
        QByteArray rfidData = arduino.read_from_arduino();
        qDebug() << "Données de la carte RFID lues depuis l'Arduino : " << rfidData;

        // Ici vous pouvez traiter les données de la carte RFID comme nécessaire
    } else {
        qDebug() << "Erreur lors de la connexion à la carte Arduino.";
    }

    // Connexion à la base de données
    Connection c;
    bool test = c.createconnect();

    if (test) {
        // Si la connexion à la base de données est réussie
        // Créer une instance de la classe MainWindow
        MainWindow w;

        // Connecter le signal de connexion de loginDialog à une fonction qui cache loginDialog et affiche w.
        QObject::connect(&loginDialog, &login::connexionReussie, [&]() {
            // Fermer la fenêtre de connexion
            loginDialog.close();
            // Afficher la fenêtre principale
            w.show();
            // Afficher le tableau dans la fenêtre principale
            w.showtableau();
        });

        // Afficher un message d'information sur la connexion réussie à la base de données
        QMessageBox::information(nullptr, QObject::tr("Base de données ouverte"),
                                 QObject::tr("Connexion réussie.\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    } else {
        // Afficher un message d'erreur sur la connexion échouée à la base de données
        QMessageBox::critical(nullptr, QObject::tr("Base de données non ouverte"),
                               QObject::tr("La connexion a échoué.\n"
                                           "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }

    return a.exec();
}
