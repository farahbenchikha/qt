#ifndef PERSONNELS_H
#define PERSONNELS_H

#include <QString>
#include <QSqlQueryModel>


class personnels
{
private:
    QString NOM_PERSO, PRENOM_PERSO, ADRESSE_PERSO, TEL_PERSO, ROLE_PERSO, Password;
    int ID_PERSO;


public:
    personnels();
    personnels(int, QString, QString, QString, QString, QString, QString );


    void setID_PERSO(int id){ ID_PERSO = id; }
    void setNOM_Perso(QString n){ NOM_PERSO = n; }
    void setPRENOM_PERSO(QString p){ PRENOM_PERSO = p; }
    void setADRESSE_PERSO(QString a){ ADRESSE_PERSO = a; }
    void setTEL_PERSO(QString t){ TEL_PERSO = t; }
    void setROLE_PERSO(QString role){ ROLE_PERSO = role; }
    void setPassword(QString password){ Password = password; }
     // void setcarte(QString c){ CARTE = c; }


    bool ajouter();
    QSqlQueryModel *afficher();
    QSqlQueryModel *TRIER(bool ordreAscendant);
    bool rechercher(int ID_PERSO);
    bool supprimer(int ID_PERSO);
    bool modifier(int ID_PERSO, QString nv_nom ,QString nv_prenom , QString nv_adresse , QString nv_tel, QString nv_role, QString nv_password);
    int getRoleCount(const QString &role);
     int getTotalPersonnes();
     bool connexion(const QString& username, const QString& mdp);
      bool emailExistsInDatabase(const QString &email);


};

#endif // PERSONNELS_H
