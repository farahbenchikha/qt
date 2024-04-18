#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTimer>
#include<QDateTime>
#include "enregistrement.h"
#include <QMessageBox>
#include <QDebug>
#include <QVector>
#include<QSqlError>
#include<QTableView>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QTextStream>
#include<QPdfWriter>
#include <QPrinter>
#include<QPainter>
#include<QtCharts>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QBrush>
#include <QColor>

#include <QFileInfo>

class CustomDelegate : public QStyledItemDelegate {
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QVariant file = index.sibling(index.row(), 3).data(Qt::DisplayRole);
        QString absoluteFilePath = "C:/Users/farah/Downloads/2a11-cr-er-une-quipe-visiondesk_2a11-main/2a11-cr-er-une-quipe-visiondesk_2a11-main/interf/qt/build-untitled3-Desktop_Qt_5_9_9_MinGW_32bit-Debug/" + file.toString();

        QFileInfo fileInfo(absoluteFilePath);
        qint64 fileSize = fileInfo.size(); // Size of the file in bytes

        if (fileSize > 7 * 1024 * 1024) {
            painter->fillRect(option.rect, QColor(255, 200, 200)); // Red color
        } else {
                painter->fillRect(option.rect, QColor(200, 200, 255)); // Light blue color

        }

        QStyledItemDelegate::paint(painter, option, index);
    }
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Créer le bouton "Export PDF"
    QPushButton *exportPDFButton = new QPushButton("Export PDF", this);
    connect(ui->pushButton_30, SIGNAL(timeout()),this,SLOT(on_pushButton_30_clicked()));
    //connect(ui->pushButton_suppenr, SIGNAL(timeout()),this,SLOT(on_pushButton_suppenr_clicked()));
  //  connect(ui->pushButton_afficher_enr, SIGNAL(timeout()),this,SLOT(on_pushButton_afficher_enr_clicked()));
    //connect(ui->pushButton_64, SIGNAL(timeout()),this,SLOT(on_pushButton_64_clicked()));
    //connect(ui->lineEdit_modifid_enr, SIGNAL(editingFinished()), this, SLOT(on_lineEdit_modifid_enr_editingFinished()));
    connect(exportPDFButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_exportpdf_clicked);

    //showtime();
    QTimer *timer=new QTimer(this);
    connect(timer , SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start();
    QDateTime date=QDateTime::currentDateTime();
    QString datetext=date.toString();
    ui->date->setText(datetext);

    // init modification

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showtime()
{
    QTime time=QTime::currentTime();
    QString time_text =time.toString("hh : mm : ss");
    ui->clock->setText(time_text);
}
void MainWindow::showtab()
{
    ui->tableView_enr->verticalHeader()->hide();
    ui->tableView_enr->setSelectionBehavior(QAbstractItemView::SelectRows);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(enr.afficher());
            proxyModel->setSourceModel(enr.afficher());

            // Enable sorting in the proxy model
            proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive); // Set case sensitivity for sorting
            ui->tableView_enr->setSortingEnabled(true); // Enable sorting in the view
            ui->tableView_enr->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView_enr->setModel(proxyModel);
    ui->tableView_enr->setItemDelegate(new CustomDelegate);

    // Clear the existing items in the combo box
       ui->comboBox_modifIdenr->clear();

       // Fill the combo box with items from the model
       for (int row = 0; row < enr.afficher()->rowCount(); ++row) {
           QModelIndex index = enr.afficher()->index(row, 0); // Assuming the ID is in the first column
           QVariant data = enr.afficher()->data(index, Qt::DisplayRole);
           ui->comboBox_modifIdenr->addItem(data.toString());

       }

}
void MainWindow::on_pushButton_30_clicked()
{
    QString NOM_ENR = ui->lineEdit_nomenr->text();
    QString QUALITE_ENR = ui->comboBox_qualite_enr->currentText();
    int ID_ENR = ui->lineEdit_id_enr->text().toInt();
    int ID_EM_ENR = ui->lineEdit_id_em_enr->text().toInt();

    enregistrement enr(ID_ENR, NOM_ENR,QUALITE_ENR, ID_EM_ENR , newFilePath);

    bool test = enr.ajouter();

    if (test) {
        QMessageBox::information(this, "Succès", "L'enregistrement a été ajouté avec succès.");
        ui->tableView_enr->setModel(enr.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de l'ajout de l'enregistrement.");
    }
}

void MainWindow::on_pushButton_afficher_enr_clicked()
{
    // Récupérer les données de l'interface utilisateur
    QString NOM_ENR = ui->lineEdit_nomenr->text();
    QString QUALITE_ENR = ui->comboBox_qualite_enr->currentText();
    int ID_ENR = ui->lineEdit_id_enr->text().toInt();
    int ID_EM_ENR = ui->lineEdit_id_em_enr->text().toInt();

    // Créer une instance de la classe enregistrement
    enregistrement enr(ID_ENR, NOM_ENR,QUALITE_ENR, ID_EM_ENR , newFilePath);

    // Appeler la fonction d'affichage des enregistrements
    QAbstractItemModel *model = enr.afficher();

    // Vérifier si le modèle est valide
    if (model) {
        // Définir les noms de colonnes sur le modèle de données
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID Emission"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Path"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Qualité"));


        QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(model);
                proxyModel->setSourceModel(model);

                proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive); // Set case sensitivity for sorting
                ui->tableView_enr->setSortingEnabled(true); // Enable sorting in the view
                ui->tableView_enr->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableView_enr->setModel(proxyModel);

    } else {
        QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de la récupération des enregistrements.");
    }
}




/*
void MainWindow::on_pushButton_64_clicked()
{
    int id_enr = ui->lineEdit_modifid_enr->text().toInt();

       // Récupérer les nouvelles données modifiées de l'interface utilisateur
       QString nouveau_nom_enr = ui->lineEdit_modifnom_enr->text();
       QString nouvelle_duree_enr = ui->timeEdit_modifduree_enr->text();
       QString nouveau_type_enr = ui->comboBox_modiftype_enr->currentText();
       QString nouvelle_qualite_enr = ui->comboBox_modifqualite_enr->currentText();
       int nouveau_id_em_enr = ui->lineEdit_modifid_emenr->text().toInt();

       // Modifier l'enregistrement avec les nouvelles données
       enregistrement enr;
       bool test = enr.modifier(id_enr, nouveau_nom_enr, nouvelle_qualite_enr, nouveau_id_em_enr);

       if (test) {
           QMessageBox::information(this, "Succès", "L'enregistrement a été modifié avec succès.");
           ui->tableView_enr->setModel(enr.afficher());

       } else {
           QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de la modification de l'enregistrement.");
       }
}

*/
void MainWindow::on_pushButton_rechEnreg_clicked()
{
    QString nom_enr = ui->lineEdit_idrecheng->text();

    enregistrement enr;
    bool resultatRecherche = enr.rechercherParNom(nom_enr);

    if (resultatRecherche) {
        QMessageBox::information(this, "Résultat de la recherche", "Le nom a été trouvé.");
    } else {
        QMessageBox::information(this, "Résultat de la recherche", "Le nom n'a pas été trouvé.");
    }
}

void MainWindow::on_pushButton_tricroisenreg_clicked()
{
    // Créer une instance de la classe enregistrement
    enregistrement enr;

    // Appeler la fonction de tri par ID croissant
    bool triReussi = enr.trierParIdCroissant();

    // Vérifier si le tri a réussi
    if (triReussi) {
        // Récupérer le modèle associé à la table view
        QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView_enr->model());

        // Tri par ID croissant dans le modèle (dans la requête SQL)
        model->setQuery("SELECT * FROM ENREGISTREMENT ORDER BY ID_ENR ASC");

        // Vérifier si une erreur s'est produite lors du tri
        if (model->lastError().isValid()) {
            QMessageBox::critical(this, "Erreur de tri", "Une erreur s'est produite lors du tri des enregistrements par ID croissant.");
            return;
        }

        // Actualiser la vue pour refléter les données triées
        ui->tableView_enr->setModel(model);

        QMessageBox::information(this, "Tri réussi", "Les enregistrements ont été triés par ID croissant.");
    } else {
        QMessageBox::critical(this, "Erreur de tri", "Une erreur s'est produite lors du tri des enregistrements par ID croissant.");
    }
}

void MainWindow::on_pushButton_tridecenreg_clicked()
{
    // Créer une instance de la classe enregistrement
        enregistrement enr;

        // Appeler la fonction de tri par ID décroissant
        bool triReussi = enr.trierParIdDecroissant();

        // Vérifier si le tri a réussi
        if (triReussi) {
            // Récupérer le modèle associé à la table view
            QSqlQueryModel *model = qobject_cast<QSqlQueryModel*>(ui->tableView_enr->model());

            // Tri par ID décroissant dans le modèle (dans la requête SQL)
            model->setQuery("SELECT * FROM ENREGISTREMENT ORDER BY ID_ENR DESC");

            // Vérifier si une erreur s'est produite lors du tri
            if (model->lastError().isValid()) {
                QMessageBox::critical(this, "Erreur de tri", "Une erreur s'est produite lors du tri des enregistrements par ID décroissant.");
                return;
            }

            // Actualiser la vue pour refléter les données triées
            ui->tableView_enr->setModel(model);

            QMessageBox::information(this, "Tri réussi", "Les enregistrements ont été triés par ID décroissant.");
        } else {
            QMessageBox::critical(this, "Erreur de tri", "Une erreur s'est produite lors du tri des enregistrements par ID décroissant.");
        }
}

/*void MainWindow::on_pushButton_filtrerenregtype_clicked()
{
    QString type = ui->lineEdit_filterengtype->text(); // Récupérer le type spécifié par l'utilisateur depuis un lineEdit

    // Créer une instance de la classe enregistrement
    enregistrement enreg;

    // Appeler la fonction de filtrage par type de la classe enregistrement à partir de l'objet enreg
    QSqlQueryModel *filteredModel = enreg.filtrerParType(type);

    // Mettre à jour le modèle dans le view approprié (par exemple, un QTableView)
    ui->tableView_enr->setModel(filteredModel);
}
*/
/*
void MainWindow::on_pushButton_filtrerenregqualite_clicked()
{
    QString qualite = ui->lineEdit_filterenregqualite->text(); // Récupérer la qualité spécifiée par l'utilisateur depuis un lineEdit
    // Créer une instance de la classe enregistrement
    enregistrement enreg;

    // Appeler la fonction de filtrage par qualité de la classe enregistrement à partir de l'objet enreg
    QSqlQueryModel *filteredModel = enreg.filtrerParQualite(qualite);



        // Mettre à jour le modèle dans le view approprié (par exemple, un QTableView)
        ui->tableView_enr->setModel(filteredModel);
}
*/

/*void MainWindow::on_lineEdit_modifid_enr_editingFinished()
{
    int id_enr = ui->lineEdit_modifid_enr->text().toInt();

        // Récupérer les données de l'enregistrement correspondant à l'identifiant spécifié
        QSqlQuery query;
        query.prepare("SELECT NOM_ENR, DUREE_ENR, TYPE_ENR, QUALITE_ENR, ID_EM_ENR FROM ENREGISTREMENT WHERE ID_ENR = :id_enr");
        query.bindValue(":id_enr", id_enr);
        if (query.exec() && query.next()) {
            QString nom_enr = query.value(0).toString();
            QString duree_enr = query.value(1).toString();
            QString type_enr = query.value(2).toString();
            QString qualite_enr = query.value(3).toString();
            int id_em_enr = query.value(4).toInt();

            // Remplir les autres champs avec les données récupérées
            ui->lineEdit_modifnom_enr->setText(nom_enr);
            ui->timeEdit_modifduree_enr->setTime(QTime::fromString(duree_enr, "hh:mm:ss"));
            ui->comboBox_modiftype_enr->setCurrentText(type_enr);
            ui->comboBox_modifqualite_enr->setCurrentText(qualite_enr);
            ui->lineEdit_modifid_emenr->setText(QString::number(id_em_enr));
        }
}
*/
void MainWindow::on_pushButton_exportpdf_clicked()
{

    QString strStream;

                                     QTextStream out(&strStream);



                                     const int rowCount = ui->tableView_enr->model()->rowCount();

                                     const int columnCount = ui->tableView_enr->model()->columnCount();



                                     out <<  "<html>\n"

                                         "<head>\n"

                                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"

                                         <<  QString("<title>%1</title>\n").arg("strTitle")

                                         <<  "</head>\n"

                                         "<body bgcolor=#ffffff link=#5000A0>\n"



                                        //     "<align='right'> " << datefich << "</align>"

                                         "<center> <H1>Liste des Enregistrements </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";



                                     // headers

                                     out << "<thead><tr bgcolor=#f0f0f0>";

                                     for (int column = 0; column < columnCount; column++)

                                         if (!ui->tableView_enr->isColumnHidden(column))

                                             out << QString("<th>%1</th>").arg(ui->tableView_enr->model()->headerData(column, Qt::Horizontal).toString());

                                     out << "</tr></thead>\n";



                                     // data table

                                     for (int row = 0; row < rowCount; row++) {

                                         out << "<tr>";

                                         for (int column = 0; column < columnCount; column++) {

                                             if (!ui->tableView_enr->isColumnHidden(column)) {

                                                 QString data = ui->tableView_enr->model()->data(ui->tableView_enr->model()->index(row, column)).toString().simplified();

                                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));

                                             }

                                         }

                                         out << "</tr>\n";

                                     }

                                     out <<  "</table> </center>\n"

                                         "</body>\n"

                                         "</html>\n";



                               QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");

                                 if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }



                                QPrinter printer (QPrinter::PrinterResolution);

                                 printer.setOutputFormat(QPrinter::PdfFormat);

                                printer.setPaperSize(QPrinter::A4);

                               printer.setOutputFileName(fileName);



                                QTextDocument doc;

                                 doc.setHtml(strStream);

                                 doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number

                                 doc.print(&printer);

    }

/*void MainWindow::on_pushButton_statistiqueenr_clicked()
{
    int nombreEmissions = 0;
    int nombrePublicites = 0;

    // Assurez-vous d'avoir une instance valide de la classe enregistrement
    enregistrement enreg;

    // Calculer les statistiques par type en utilisant la fonction de la classe enregistrement
    enreg.calculerStatistiquesParType(nombreEmissions, nombrePublicites);

    // Afficher les statistiques dans une boîte de dialogue ou dans l'interface utilisateur
    QMessageBox::information(this, "Statistiques par Type",
                             QString("Nombre d'émissions : %1\nNombre de publicités : %2")
                             .arg(nombreEmissions).arg(nombrePublicites));
}
*/

void MainWindow::on_pushButton_statistiqueenr_clicked()
{
    int totalEnregistrements = enr.getTotalEnregistrements();
    int nombreEmissions = 0;
    int nombrePublicites = 0;

    for (int row = 0; row < enr.afficher()->rowCount(); ++row) {
        QModelIndex index = enr.afficher()->index(row, 0);

            QVariant file = index.sibling(index.row(), 3).data(Qt::DisplayRole);
            QString absoluteFilePath = "C:/Users/farah/Downloads/2a11-cr-er-une-quipe-visiondesk_2a11-main/2a11-cr-er-une-quipe-visiondesk_2a11-main/interf/qt/build-untitled3-Desktop_Qt_5_9_9_MinGW_32bit-Debug/" + file.toString();

            QFileInfo fileInfo(absoluteFilePath);
            qint64 fileSize = fileInfo.size(); // Size of the file in bytes

            if (fileSize > 7 * 1024 * 1024 ) {
                nombreEmissions++;
            }else{
                nombrePublicites++;
            }

        }


    // Calcul des pourcentages
    qreal pourcentageEmissions = (qreal)nombreEmissions / totalEnregistrements * 100;
    qreal pourcentagePublicites = (qreal)nombrePublicites / totalEnregistrements * 100;

    // Création du diagramme circulaire
    QPieSeries *series = new QPieSeries();
    series->append(QString("Émissions (%1%)").arg(pourcentageEmissions), pourcentageEmissions);
    series->append(QString("Publicités (%1%)").arg(pourcentagePublicites), pourcentagePublicites);

    // Définition des couleurs pour chaque segment
    series->slices().at(0)->setColor(Qt::blue); // Émissions en bleu
    series->slices().at(1)->setColor(Qt::green); // Publicités en vert

    // Création du diagramme et de la vue du diagramme
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des enregistrements par type");

    // Création de la vue du diagramme
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Affichage de la vue du diagramme
    QMainWindow *statWindow = new QMainWindow();
    statWindow->setCentralWidget(chartView);
    statWindow->resize(400, 300);
    statWindow->show();
}

void MainWindow::on_pushButton_impEng_clicked()
{
    QString originalFilePath = QFileDialog::getOpenFileName(this, tr("Selectionner le fichier de la video"), "", tr("MP4 Files (*.MP4)"));
    QString newDirectory = "videos/";

    if (!originalFilePath.isEmpty()) {
        QFileInfo originalFileInfo(originalFilePath);
        QString newFileName = newDirectory + originalFileInfo.fileName();
        if (QFile::copy(originalFilePath, "./"+newFileName)) {
            newFilePath = newFileName;
        } else {
            qDebug() << "Failed to copy file.";
        }
        ui->lineEdit_cheminEnr->setText(newFilePath);
    }

}

void MainWindow::on_lineEdit_idrecheng_textChanged(const QString &arg1)
{
    QString filterText = arg1.trimmed();

        enregistrement enreg;
        //recherche
        QSqlQueryModel *filteredModel = enreg.filtrerParNom(arg1);
        //tri
        QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(filteredModel);
        proxyModel->setSourceModel(filteredModel);
                proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
                ui->tableView_enr->setSortingEnabled(true);

                //Selection unique
                ui->tableView_enr->setSelectionMode(QAbstractItemView::SingleSelection);

        ui->tableView_enr->setModel(proxyModel);

}

void MainWindow::on_pushButton_supenr_clicked()
{
    QItemSelectionModel *select = ui->tableView_enr->selectionModel();
    QModelIndexList selectedRows = select->selectedRows();
    foreach(const QModelIndex &index, selectedRows) {
        QVariant idVariant = ui->tableView_enr->model()->data(ui->tableView_enr->model()->index(index.row(), 0));
        QVariant pathVariant = ui->tableView_enr->model()->data(ui->tableView_enr->model()->index(index.row(), 3));
        int id_enr = idVariant.toInt();
        QString path_enr = pathVariant.toString();
        enregistrement enr;
        bool test = enr.supprimer(id_enr, path_enr);
        if (test) {
            QMessageBox::information(this, "Succès", "L'enregistrement a été supprimé avec succès.");
            ui->tableView_enr->setModel(enr.afficher());
        } else {
            QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de la suppression de l'enregistrement.");
        }
    }
}


void MainWindow::on_pushButton_modifenr_clicked()
{
    QModelIndex selectedIndex =  ui->tableView_enr->selectionModel()->currentIndex();
       if (selectedIndex.isValid()) {
           QVariant data = ui->tableView_enr->model()->data(selectedIndex, Qt::DisplayRole);

       } else {
           qDebug() << "No item selected.";
       }
}


void MainWindow::on_comboBox_modifIdenr_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;
    query.prepare("SELECT ID_ENR, NOM_ENR, QUALITE_ENR, ID_EM_ENR, PATH_ENR FROM ENREGISTREMENT WHERE ID_ENR = ?");
    query.bindValue(0, arg1);
    if (query.exec() && query.next()) {
        QString NOM_ENR = query.value(1).toString();
        QString QUALITE_ENR = query.value(2).toString();
        QString ID_EM_ENR = query.value(3).toString();
        QString PATH_ENR = query.value(4).toString();
        ui->lineEdit_modifnomenr->setText(NOM_ENR);
        ui->lineEdit_modifidenrEm->setText(ID_EM_ENR);
        ui->lineEdit_modifcheminEnr->setText(PATH_ENR);
    }
}

void MainWindow::on_pushButton_impEng_3_clicked()
{
    QString originalFilePath = QFileDialog::getOpenFileName(this, tr("Selectionner le fichier de la video"), "", tr("MP4 Files (*.MP4)"));
    QString newDirectory = "videos/";

    if (!originalFilePath.isEmpty()) {
        QFileInfo originalFileInfo(originalFilePath);
        QString newFileName = newDirectory + originalFileInfo.fileName();
        if (QFile::copy(originalFilePath, "./"+newFileName)) {
            newFilePath = newFileName;
        } else {
            qDebug() << "Failed to copy file.";
        }
        ui->lineEdit_modifcheminEnr->setText(newFilePath);
    }
}

void MainWindow::on_pushButton_32_clicked()
{
    QString NOM_ENR = ui->lineEdit_modifnomenr->text();
    QString QUALITE_ENR = ui->comboBox_modifqualite_enr_2->currentText();
    int ID_ENR = ui->comboBox_modifIdenr->currentText().toInt();
    int ID_EM_ENR = ui->lineEdit_modifidenrEm->text().toInt();
    QString PATH_ENR = ui->lineEdit_modifcheminEnr->text();


    bool test = enr.modifier( ID_ENR, NOM_ENR,  QUALITE_ENR, ID_EM_ENR,  PATH_ENR);

    if (test) {
        QMessageBox::information(this, "Succès", "L'enregistrement a été ajouté avec succès.");
        ui->tableView_enr->setModel(enr.afficher());
    } else {
        QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de l'ajout de l'enregistrement.");
    }
}

void MainWindow::on_pushButton_lecEnr_clicked()
{
    QItemSelectionModel *select = ui->tableView_enr->selectionModel();
    QModelIndexList selectedRows = select->selectedRows();
    foreach(const QModelIndex &index, selectedRows) {
        QVariant pathVariant = ui->tableView_enr->model()->data(ui->tableView_enr->model()->index(index.row(), 3));
        QString absoluteFilePath = "C:/Users/farah/Downloads/2a11-cr-er-une-quipe-visiondesk_2a11-main/2a11-cr-er-une-quipe-visiondesk_2a11-main/interf/qt/build-untitled3-Desktop_Qt_5_9_9_MinGW_32bit-Debug/" + pathVariant.toString();
        QMediaPlayer *player = new QMediaPlayer();
            QVideoWidget *video =new QVideoWidget();
            video->setGeometry(20,20,640,480);
            player->setVideoOutput(video);
            player->setMedia(QUrl(absoluteFilePath));
            video->show();
            player->play();

    }
}


