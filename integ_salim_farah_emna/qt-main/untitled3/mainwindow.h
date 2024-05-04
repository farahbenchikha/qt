#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"personnels.h"
#include <QMainWindow>
#include"login.h"
#include <QQuickWidget>
#include<QVariant>
#include<QtCore>
#include<QtGui>
#include<QtQuick>
#include<arduino.h>
#include<enregistrement.h>
#include <QMultimedia>
#include <QtMultimediaWidgets>
#include "studio.h"
#include "equipement.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
 QString extractRFID(const QString &rfidData);
    void showtableau();
      void showMainWindow();
      void showtab();
         enregistrement enr; //variable nekhdmou alihh les fcts
         void   afficherS();
         int getTotalStudiosCount();
          int getStudiosCountByType(int type);
      int getOccupiedStudiosCount();
       void afficherNotification(const QString& titre, const QString& message);
      QByteArray data;
private slots:
    //void on_pushButton_12_clicked();
    void showtime();
    //void on_ajout_sinscrire_clicked();
    //void on_supprimer_clicked();
    //void on_pushButton_55_clicked();
    void on_modifier_clicked();
    void on_afficher_clicked();
   // void on_supprimer_2_clicked();
    void on_afficher_2_clicked();
    void on_trier_clicked();
    void on_recherche_clicked();
    //void on_pdf_clicked();
    void on_pdf_2_clicked();
    void afficherStatistiques();
 bool checkRFIDInDatabase(const QString &idCarteRFID);
      void on_pushButton_12_clicked();
      void readRFID(const QString &idCarteRFID);
         void processRFIDData(const QString &rfidData);
         void handleArduinoData();

         void on_scaner_clicked();

         void on_pushButton_30_clicked();

             void on_pushButton_afficher_enr_clicked();

             void on_pushButton_rechEnreg_clicked();

             void on_pushButton_tricroisenreg_clicked();

             void on_pushButton_tridecenreg_clicked();

             void on_pushButton_exportpdf_clicked();

             void on_pushButton_statistiqueenr_clicked();

             void on_lineEdit_idrecheng_textChanged(const QString &arg1);

             void on_pushButton_supenr_clicked();

             void on_pushButton_modifenr_clicked();

             void on_comboBox_modifIdenr_currentIndexChanged(const QString &arg1);

             void on_pushButton_impEng_3_clicked();

             void on_pushButton_32_clicked();

             void on_pushButton_lecEnr_clicked();


             void on_pushButton_importvidenr_clicked();
             void on_AjouterS_clicked();

             void on_Afficher_S_clicked();

             void on_Supprimer_S_clicked();

             void on_Modifier_S_clicked();

             void on_lineEdit_RchS_textChanged(const QString &arg1);

             void on_Ajouter_E_clicked();



             void on_Afficher_E_clicked();

             void on_Supprimer_E_clicked();

             void on_Modifier_E_clicked();

             void on_lineEdit_RechE_textChanged(const QString &arg1);

             void on_pushButton_EXS_clicked();

             void on_pushButton_EXE_clicked();



             void on_stat_clicked();


             void afficherHistorique();
             void afficherHistorique_E();



             void on_historique_clicked();

             void on_trier_clicked1();



             void on_pushButton_7_clicked();//tri pour  equipement

             void on_Reservation_clicked();

             void on_his_E_clicked();

            // void on_tableWidget_S_cellChanged(int row, int column);
          void surveillerOccupationStudios();
          void processFlameSignal();
          int readFromDatabase();
           void envoieard();

           void on_urgence_clicked();


private:
    Ui::MainWindow *ui;
    static Arduino *arduino;
    personnels p;
    QString newFilePath;
    int selectedEnrId;
    studio newStudio;
     QSqlQueryModel *mod;
         equipement newEquipement;
signals:
    void setCenterPosition(QVariant, QVariant);
    void setLocationMarking(QVariant latitude, QVariant longitude);

};
#endif // MAINWINDOW_H
