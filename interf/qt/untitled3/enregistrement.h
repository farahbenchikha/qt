#ifndef ENREGISTREMENT_H
#define ENREGISTREMENT_H
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<string>
#include <QObject>
class enregistrement : public QObject
{
private:
    QString NOM_ENR, TYPE_ENR, QUALITE_ENR, DUREE_ENR;
    int ID_ENR, ID_EM_ENR;

public:
    // Constructeurs
    enregistrement();
    enregistrement(int, QString, QString, QString, QString, int);

    // Getters
    QString getNOM_ENR() { return NOM_ENR; }
    QString getType() { return TYPE_ENR; }
    QString getQualite() { return QUALITE_ENR; }
    QString getDuree_enr() { return DUREE_ENR; }
    int getID_ENR() { return ID_ENR; }
    int getID_EM_ENR() { return ID_EM_ENR; }
  //  int getCountByType() { return COUNT_BY_TYPE; }

    // Setters
    void setNOM_ENR(QString name) { NOM_ENR = name; }
    void setType(QString type_en) { TYPE_ENR = type_en; }
    void setQualite(QString quality) { QUALITE_ENR = quality; }
    void setDuree_enr(QString duree) { DUREE_ENR = duree; }
    void setID_ENR(int id) { ID_ENR = id; }
    void setID_EM_ENR(int id_em_enr) { ID_EM_ENR = id_em_enr; }
  //  void setCountByType(int count) { COUNT_BY_TYPE = count; }

    // Fonctionnalités de base relatives
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int ID_ENR, QString NOM_ENR, QString TYPE_ENR, QString QUALITE_ENR, QString DUREE_ENR, int ID_EM_ENR);
    bool rechercherParNom(const QString &nom);
    bool trierParIdCroissant();
    bool trierParIdDecroissant();
    bool trierParNom(QSqlQueryModel *model);

    QSqlQueryModel* filtrerParType(QString type);
    QSqlQueryModel* filtrerParQualite(QString qualite);
  //  bool ajouterHistoriqueModification(int id_enr, const QString &utilisateur, const QString &description);
    QString recupererCoordonnees(int id_enr) const;
    void calculerStatistiquesParType(int &nombreEmissions, int &nombrePublicites);
    int getTotalEnregistrements();
    int getNombreParType(const QString &type);
};

#endif // ENREGISTREMENT_H
