#include "login.h"
#include "inscrit.h"
#include "smtp.h"
#include "mdp.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "personnels.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QWidget>
#include <QtWidgets>
#include <QString>
#include <QTextStream>
#include <QPixmap>
#include <QMessageBox>

void login::on_ou_mouseClicked()
{
    qDebug() << "Clic détecté sur le QLabel 'ou'";
    // Ajoutez ici le code pour gérer le clic sur le QLabel 'ou'
}

login::login(QWidget *parent) : QDialog(parent),
                                ui(new Ui::login)
{
    ui->setupUi(this);
    ui->ou->setText("<a href=\"#\">mot de passe oubliée ?</a>");
    connect(ui->connexion, SIGNAL(clicked()), this, SLOT(on_connexion_clicked()));
    connect(ui->ou, SIGNAL(clicked()), this, SLOT(on_ou_linkActivated()));
}

login::~login()
{
    delete ui;
}

void login::on_inscrire_clicked()
{
    this->close();
    inscrit *inscriptionWindow = new inscrit();
    inscriptionWindow->show();
}

void login::on_connexion_clicked()
{
    QString email = ui->nom->text().trimmed();
    QString password = ui->mdp->text().trimmed();

    QString role;

    personnels p;
    if (p.connexion(email, password))
    {
        QSqlQuery query;
        query.prepare("SELECT ROLE_PERSO FROM PERSONNELS WHERE ADRESSE_PERSO = :email");
        query.bindValue(":email", email);
        if (query.exec() && query.next())
        {
            role = query.value(0).toString();
        }
        else
        {
            QMessageBox::warning(this, "Erreur de récupération du rôle", "Impossible de récupérer le rôle de l'utilisateur !");
            return;
        }

        QString messageBienvenue;
        if (role == "Admin")
        {
            messageBienvenue = "Bienvenue à notre administrateur !";
        }
        else if (role == "Animateur")
        {
            messageBienvenue = "Bienvenue à notre animateur !";
        }
        else if (role == "ingenieur son")
        {
            messageBienvenue = "Bienvenue à notre ingénieur son !";
        }

        QMessageBox::information(this, "Connexion réussie", messageBienvenue);

        // Vérifiez si mainWindow est nullptr
        if (!mainwindow)
        {
            mainwindow = new MainWindow();
        }

        // Affichez la fenêtre MainWindow
        mainwindow->show();
        mainwindow->showtab();

        // Cachez la fenêtre de connexion
        this->hide();
    }
    else
    {
        QMessageBox::warning(this, "Erreur de connexion", "Adresse e-mail ou mot de passe incorrect !");
    }
}

void login::on_ou_linkActivated(const QString &link)
{
    qDebug() << "Clic sur le lien détecté : " << link;
    mdpInterface = new mdp(this);
    mdpInterface->show();
}
