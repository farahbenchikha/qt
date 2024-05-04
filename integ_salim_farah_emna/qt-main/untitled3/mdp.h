#ifndef MDP_H
#define MDP_H
#include"smtp.h"
#include <QDialog>
#include <QMessageBox>
#include "smtpp.h"
#include "smtp.h"


namespace Ui {
class mdp;
}

class mdp : public QDialog
{
    Q_OBJECT

public:
    explicit mdp(QWidget *parent = nullptr);
    ~mdp();
private slots:
    void on_envoyer_clicked();
    void sendMail(QString email);
    void mailSent(QString);
    void sendMaile();
    void mailSente(QString);


    //void on_reset_clicked();



private:
    Ui::mdp *ui;

    //void sendResetEmail(const QString& emailAddress, const QString& resetToken);
    //void resetPassword(const QString& emailAddress, const QString& newPassword);
        QString generateToken();
    //QString getTelPersoFromDatabase(const QString& idPerso);
    //void sendResetEmail(const QString& emailAddress, const QString& resetToken);
       // void resetPassword(const QString& emailAddress, const QString& newPassword);
        //QString generateToken();
        //bool mdp::emailExistsInDatabase(const QString& email)
 bool emailExistsInDatabase(const QString& email);
};

#endif // MDP_H

