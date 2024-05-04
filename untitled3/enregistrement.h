#ifndef ENREGISTREMENT_H
#define ENREGISTREMENT_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<string>
#include <QObject>
class enregistrement : public QObject
{
private:
    QString NOM_ENR, QUALITE_ENR, PATH_ENR;
    int ID_ENR, ID_EM_ENR;

public:
    // Constructeurs
    enregistrement();
    enregistrement(int, QString, QString, int , QString);

    // Getters
    QString getNOM_ENR() { return NOM_ENR; }
    QString getQualite() { return QUALITE_ENR; }
    QString getPath_enr() { return PATH_ENR; }
    int getID_ENR() { return ID_ENR; }
    int getID_EM_ENR() { return ID_EM_ENR; }
  //  int getCountByType() { return COUNT_BY_TYPE; }

    // Setters
    void setNOM_ENR(QString name) { NOM_ENR = name; }
    void setQualite(QString quality) { QUALITE_ENR = quality; }
    void setPath_enr(QString path_enr) { PATH_ENR = path_enr; }
    void setID_ENR(int id) { ID_ENR = id; }
    void setID_EM_ENR(int id_em_enr) { ID_EM_ENR = id_em_enr; }
  //  void setCountByType(int count) { COUNT_BY_TYPE = count; }

    // Fonctionnalités de base relatives
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id_enr, QString path);
    bool modifier(int ID_ENR, QString NOM_ENR, QString QUALITE_ENR, int ID_EM_ENR, QString PATH_ENR );
    bool rechercherParNom(const QString &nom);
    bool trierParIdCroissant();
    bool trierParIdDecroissant();
    bool trierParNom(QSqlQueryModel *model);

    QSqlQueryModel* filtrerParType(QString type);
    QSqlQueryModel* filtrerParQualite(QString qualite);
    QSqlQueryModel* filtrerParNom(QString nom);

  //  bool ajouterHistoriqueModification(int id_enr, const QString &utilisateur, const QString &description);
    QString recupererCoordonnees(int id_enr) const;
    void calculerStatistiquesParType(int &nombreEmissions, int &nombrePublicites);
    int getTotalEnregistrements();
    int getNombreParType(const QString &type);
};

#endif // ENREGISTREMENT_H
