// studio.h
#ifndef STUDIO_H
#define STUDIO_H

#include <QSqlQueryModel>
#include <QString>
#include <QSortFilterProxyModel>
#include <QString>
#include <QList>
#include <QPair>
class studio {
    QString NOM_S, DESCRIPTION_S;
    int ID_S;
    int ETAT_S;

public:
    //constructeurs
    studio();
    studio(int, QString, QString,int);
    studio(int id);

    //getters
    QString getNOM_S() const { return NOM_S; };
    QString getDESCREPTION_S() const { return DESCRIPTION_S; };
    int getNUM_S() const { return ID_S; }

    //setters
    void setNOM_S(const QString &n) { NOM_S = n; }
    void setDESCREPTION_S(const QString &d) { DESCRIPTION_S = d; }
    void setNUM_S(int num) { ID_S = num; }

    // fonctionnalites
    QString ajouter();

    QSqlQueryModel *afficher();
    bool supprimer(int);
    QString getLastErrorMessage() const { return lastErrorMessage; }
     QString modifier(int id);
     QSqlQueryModel *chercher(const QString &searchText);
     QString ajouterHistoriqueAjoutStudio(int idStudio, const QDateTime& dateAjout, const QString& description);
     QSqlQueryModel *trierParId();
     QSqlQueryModel *afficherStudiosNonOccupes();
     bool reserverStudio(const QString& date);
QList<QPair<QString, QString>> afficherStudiosReserves();
QString ajouterHistoriqueStudio(const QString& typeAction, int idStudio, const QDateTime& dateAction, const QString& description);


private:
    QString lastErrorMessage;

};

#endif // STUDIO_H
