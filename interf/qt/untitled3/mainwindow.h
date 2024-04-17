#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMultimedia>
#include <QtMultimediaWidgets>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include"enregistrement.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showtab();
    enregistrement enr; //variable nekhdmou alihh les fcts
private slots:
    void showtime();


    void on_pushButton_30_clicked();

    void on_pushButton_afficher_enr_clicked();

    void on_pushButton_127_clicked();

    void on_pushButton_64_clicked();
    void on_pushButton_suppenr_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_rechEnreg_clicked();

    void on_pushButton_tricroisenreg_clicked();

    void on_pushButton_tridecenreg_clicked();

    void on_pushButton_filtrerenregtype_clicked();


    void on_pushButton_filtrerenregqualite_clicked();

    void on_lineEdit_filtrerenregdure_cursorPositionChanged(int arg1, int arg2);


    void on_lineEdit_modifid_enr_editingFinished();

    void on_pushButton_exportpdf_clicked();

    void on_pushButton_statistiqueenr_clicked();

    void on_pushButton_impEng_clicked();

    void on_lineEdit_idrecheng_textChanged(const QString &arg1);

    void on_pushButton_supenr_clicked();

private:
    Ui::MainWindow *ui;
      QString newFilePath;
};
#endif // MAINWINDOW_H
