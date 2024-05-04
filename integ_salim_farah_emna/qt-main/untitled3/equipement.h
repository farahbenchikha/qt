#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H


#include <QSqlQueryModel>
#include <QString>

class equipement {
    QString NOM_EQ, DISCREPTION_EQ;
    int ID_EQ;
    int ID_STUDIO;


public:
    //constructeurs
    equipement();
    equipement(int, QString, QString,int);

    //getters
    QString getNOM_EQ() const { return NOM_EQ; };
    QString getDISCREPTION_EQ() const { return DISCREPTION_EQ; };
    int getID_EQ() const { return ID_EQ; }
     int getID_S() const { return ID_STUDIO; }

    //setters
    void setNOM_EQ(const QString &n) { NOM_EQ = n; }
    void setDISCREPTION_EQ(const QString &d) { DISCREPTION_EQ = d; }
    void setID_EQ(int id) { ID_EQ = id; }
    void setID_Studio(int ids) { ID_STUDIO = ids; }

    // fonctionnalites
    QString ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    QString getLastErrorMessage() const { return lastErrorMessage; }
    QString modifier(int id);
    QSqlQueryModel *chercher(const QString &searchText);
    QSqlQueryModel *trierParNom();
    QString ajouterHistoriqueAjoutEquipement(int idEquipement, const QDateTime& dateAjout, const QString& description);
private:
    QString lastErrorMessage;
};


#endif // EQUIPEMENT_H
