#ifndef INSCRIT_H
#define INSCRIT_H

#include <QDialog>
#include"personnels.h"
#include"mainwindow.h"
#include"login.h"
#include <QTableView>
#include<sms.h>

namespace Ui {
class inscrit;
}

class inscrit : public QDialog
{
    Q_OBJECT

public:
    explicit inscrit(QWidget *parent = nullptr);
    ~inscrit();
    QString generateConfirmationCode();
private slots:
    void on_retourner_clicked();
    void on_ajout_sinscrire_clicked();
    void on_supprimer_2_clicked();


    void on_pushButton_clicked();

    //void on_retourner_clicked();

    void on_sms_clicked();

private:
    Ui::inscrit *ui;
     //QTableView *m_tableau;
};

#endif // INSCRIT_H
