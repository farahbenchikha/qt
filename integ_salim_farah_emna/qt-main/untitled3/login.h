#ifndef LOGIN_H
#define LOGIN_H
#include "mdp.h"
#include <QDialog>
#include"smtp.h"
#include"personnels.h"


class inscrit; // Déclaration forward de la classe inscrit

class MainWindow; // Déclaration forward de la classe MainWindow

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);


    ~login();

signals:
    void connexionReussie();
    void connexionAutomatique(const QString &idCarteRFID);

private slots:
     void on_ou_mouseClicked();
    void on_inscrire_clicked();
    void on_connexion_clicked();
    //void ouvrirMainWindow();
    //void on_label_35_linkActivated(const QString &link);

    void on_ou_linkActivated(const QString &link);


    void on_sms_clicked();


public slots:
    void inscrire();

private:
    Ui::login *ui;
    inscrit *inscriptionWindow;
    MainWindow *mainwindow=nullptr;
    mdp *mdpInterface;
     personnels p;
    //QDateTime startTime;
};

#endif // LOGIN_H
