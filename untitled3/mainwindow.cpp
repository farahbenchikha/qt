#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "inscrit.h"
#include "personnels.h"
#include "connection.h"
#include "enregistrement.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "arduino.h"
#include <QTimer>
#include <QString>
#include <QTextStream>
#include <QPdfWriter>
#include <QPrinter>
#include <QTextDocument>
#include <QDateTime>
#include <QMessageBox>
#include <QObject>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QWidget>
#include <QtWidgets>
#include <QPainter>
#include <QTextDocument>
#include <QFileDialog>
#include <QtCharts>
#include <QApplication>
#include <QIntValidator>
#include <QQuickWidget>
#include <QVector>
#include <QStyledItemDelegate>
#include <QBrush>
#include <QColor>
#include <QFileInfo>

class CustomDelegate : public QStyledItemDelegate
{
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QVariant file = index.sibling(index.row(), 3).data(Qt::DisplayRole);

        QString currentDir = QDir::currentPath(); // Get the current directory path

        QString absoluteFilePath = currentDir + "/" + file.toString();

        QFileInfo fileInfo(absoluteFilePath);
        qint64 fileSize = fileInfo.size(); // Size of the file in bytes

        if (fileSize > 7 * 1024 * 1024)
        {
            painter->fillRect(option.rect, QColor(255, 200, 200)); // Red color
        }
        else
        {
            painter->fillRect(option.rect, QColor(200, 200, 255)); // Light blue color
        }

        QStyledItemDelegate::paint(painter, option, index);
    }
};

Arduino *MainWindow::arduino = nullptr;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // affichage
    // ui->table1->setModel(p.afficher());
    //  Créer une instance de la classe Arduino
    arduino = new Arduino();

    // Connecter Arduino
    int connectResult = arduino->connect_arduino();
    if (connectResult == 0)
    {
        qDebug() << "Arduino connected successfully!";
    }
    else if (connectResult == 1)
    {
        qDebug() << "Failed to open serial port!";
    }
    else
    {
        qDebug() << "Arduino not found!";
    }

    //  ui->setupUi(this);
    connect(ui->statistique, SIGNAL(clicked()), this, SLOT(afficherStatistiques()));
    // connect(ui->ajout_sinscrire, SIGNAL(clicked()), this, SLOT(on_ajout_sinscrire_clicked()));
    connect(ui->modifier, SIGNAL(clicked()), this, SLOT(on_modifier_clicked()));
    connect(ui->afficher, SIGNAL(clicked()), this, SLOT(on_afficher_clicked()));
    // connect(ui->supprimer_2, SIGNAL(clicked()), this, SLOT(on_supprimer_2_clicked()));
    connect(ui->afficher_2, SIGNAL(clicked()), this, SLOT(on_afficher_2_clicked()));
    connect(ui->trier, SIGNAL(clicked()), this, SLOT(on_trier_clicked()));
    connect(ui->recherche, SIGNAL(clicked()), this, SLOT(on_recherche_clicked()));
    connect(ui->pdf_2, SIGNAL(clicked()), this, SLOT(on_pdf_2_clicked()));
    connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(on_pushButton_12_clicked()));
    connect(ui->scaner, SIGNAL(clicked()), this, SLOT(on_scaner_clicked()));
    QPushButton *exportPDFButton = new QPushButton("Export PDF", this);
    connect(ui->pushButton_30, SIGNAL(timeout()), this, SLOT(on_pushButton_30_clicked()));
    connect(exportPDFButton, SIGNAL(clicked()), this, SLOT(on_pushButton_exportpdf_clicked));
    connect(ui->pushButton_importvidenr, SIGNAL(clicked()), this, SLOT(on_pushButton_importvidenr_clicked));
    connect(ui->pushButton_statistiqueenr, SIGNAL(clicked()), this, SLOT(on_pushButton_statistiqueenr_clicked));
    connect(ui->pushButton_impEng_3, SIGNAL(clicked()), this, SLOT(on_pushButton_impEng_3_clicked));
    connect(ui->pushButton_32, SIGNAL(clicked()), this, SLOT(on_pushButton_32_clicked));
    connect(ui->pushButton_30, SIGNAL(clicked()), this, SLOT(on_pushButton_30_clicked));

    // showtime();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showtime()));
    timer->start();
    QDateTime date = QDateTime::currentDateTime();
    QString datetext = date.toString();
    ui->date->setText(datetext);
}

MainWindow::~MainWindow()
{
    delete ui;
    arduino->close_arduino();
    delete arduino;
}

void MainWindow::showtime()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    ui->clock->setText(time_text);
}
void MainWindow::showtableau()
{
    ui->tableau->setModel(p.afficher());
}

/*void MainWindow::on_ajout_sinscrire_clicked()
{
    int ID_PERSO = ui->ID_Perso->text().toInt();
        QString ROLE_PERSO = ui->role->currentText();
        QString Nom_Perso = ui->Nom_Perso->text().trimmed();
        QString PRENOM_PERSO = ui->Prenom_Perso->text().trimmed();
        QString ADRESSE_PERSO = ui->Adresse->text().trimmed();
        QString TEL_PERSO = ui->Tel->text().trimmed();
        if (Nom_Perso.isEmpty() || PRENOM_PERSO.isEmpty() || ADRESSE_PERSO.isEmpty() || TEL_PERSO.isEmpty()) {
            QMessageBox::warning(this, tr("Champs manquants"), tr("Tous les champs doivent être remplis."));
            return;
        }
        personnels verifierID;
        if (verifierID.rechercher(ID_PERSO)) {
            QMessageBox::warning(this, tr("ID existant"), tr("L'ID saisi existe déjà."));
            return;
        }
         QRegExp regexTel("^\\d{8}$");
        if (!regexTel.exactMatch(TEL_PERSO)) {
            QMessageBox::warning(this, tr("Format téléphone invalide"), tr("Le téléphone doit contenir 8 chiffres."));
            return;
        }
        personnels p(ID_PERSO, ROLE_PERSO, Nom_Perso, PRENOM_PERSO, ADRESSE_PERSO, TEL_PERSO);
        bool test = p.ajouter();

        if (test) {
            // Refresh
            ui->tableau->setModel(p.afficher());
            QMessageBox::information(this, tr("Ok"), tr("Ajout effectué."), QMessageBox::Ok);
        } else {
            QMessageBox::critical(this, tr("Erreur"), tr("Ajout non effectué."), QMessageBox::Ok);
        }
}

*/

void MainWindow::on_modifier_clicked()
{
    int ID_PERSO = ui->perso->text().toInt();
    QString nv_nom = ui->nv_nom->text();
    QString nv_prenom = ui->nv_prenom->text();
    QString nv_addresse = ui->nv_adresse->text();
    QString nv_tel = ui->nv_tel->text();
    QString nv_role = ui->nv_role->currentText();
    QString nv_password = ui->nv_password->text();

    QRegExp regexTel("^\\+216\\d{8}$");
    if (!regexTel.exactMatch(nv_tel))
    {
        QMessageBox::warning(this, tr("Format téléphone invalide"), tr("Le téléphone doit contenir 8 chiffres."));
        return;
    }
    if (p.modifier(ID_PERSO, nv_nom, nv_prenom, nv_addresse, nv_tel, nv_role, nv_password))
    {
        ui->tableau->setModel(p.afficher());
        QMessageBox::information(this, "Modification réussie", "La modification a été effectuée avec succès.");
    }
    else
    {
        QMessageBox::warning(this, "Erreur de modification", "La modification a échoué.");
    }
}

void MainWindow::on_afficher_clicked()
{

    ui->tableau->setModel(p.afficher());
    // ui->tableau->resizeColumnsToContents();
    // pour la taille
    ui->tableau->setColumnWidth(0, 100);
    ui->tableau->setColumnWidth(1, 100);
    ui->tableau->setColumnWidth(2, 100);
    ui->tableau->setColumnWidth(3, 100);
    ui->tableau->setColumnWidth(4, 100);
    ui->tableau->setColumnWidth(5, 100);
    ui->tableau->setColumnWidth(5, 100);
}

/*void MainWindow::on_supprimer_2_clicked()
{

    int ID_PERSO=ui->ID_Perso->text().toInt();
    bool test=p.supprimer(ID_PERSO);
    if(test)
    {
        ui->tableau->setModel(p.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),QObject::tr("suppression effectuee\n""click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::information(nullptr, QObject::tr("not ok"),QObject::tr("suppression n'as pas effectuee\n""click cancel to exit."),QMessageBox::Cancel);
}
*/

void MainWindow::on_afficher_2_clicked()
{
    ui->tableau->setModel(p.afficher());
    // ui->tableau->resizeColumnsToContents();
    // pour la taille
    ui->tableau->setColumnWidth(0, 100);
    ui->tableau->setColumnWidth(1, 100);
    ui->tableau->setColumnWidth(2, 100);
    ui->tableau->setColumnWidth(3, 100);
    ui->tableau->setColumnWidth(4, 100);
    ui->tableau->setColumnWidth(5, 100);
    ui->tableau->setColumnWidth(5, 100);
}

void MainWindow::on_trier_clicked()
{
    bool ordreAscendant = true; // ou false, selon le besoin
    ui->tableau->setModel(p.TRIER(ordreAscendant));
}

void MainWindow::on_recherche_clicked()
{

    int idToSearch = ui->chercher->text().toInt();
    ;
    bool test = p.rechercher(idToSearch);
    if (test)
    {
        QStandardItemModel *searchResult = new QStandardItemModel();
        searchResult->setItem(0, 0, new QStandardItem(QString::number(idToSearch)));
        QMessageBox::warning(this, "success", "personne found");
        ui->tableau->setModel(searchResult);
        // ui->tableau->setModel(p.afficher());
        ui->tableau->setColumnWidth(0, 100);
        ui->tableau->setColumnWidth(1, 100);
        ui->tableau->setColumnWidth(2, 100);
        ui->tableau->setColumnWidth(3, 100);
        ui->tableau->setColumnWidth(4, 100);
        ui->tableau->setColumnWidth(5, 100);
        ui->tableau->setColumnWidth(5, 100);
    }
    else
    {
        QMessageBox::warning(this, "error", "personne not found");
    }
}

void MainWindow::on_pdf_2_clicked()
{

    QString strStream;

    QTextStream out(&strStream);

    const int rowCount = ui->tableau->model()->rowCount();

    const int columnCount = ui->tableau->model()->columnCount();

    out << "<html>\n"

           "<head>\n"

           "<meta Content=\"Text/html; charset=Windows-1251\">\n"

        << QString("<title>%1</title>\n").arg("strTitle")

        << "</head>\n"

           "<body bgcolor=#ffffff link=#5000A0>\n"

           //     "<align='right'> " << datefich << "</align>"

           "<center> <H1>Liste des staffs </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

    // headers

    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";

    for (int column = 0; column < columnCount; column++)

        if (!ui->tableau->isColumnHidden(column))

            out << QString("<th>%1</th>").arg(ui->tableau->model()->headerData(column, Qt::Horizontal).toString());

    out << "</tr></thead>\n";

    // data table

    for (int row = 0; row < rowCount; row++)
    {

        out << "<tr> <td bkcolor=0>" << row + 1 << "</td>";

        for (int column = 0; column < columnCount; column++)
        {

            if (!ui->tableau->isColumnHidden(column))
            {

                QString data = ui->tableau->model()->data(ui->tableau->model()->index(row, column)).toString().simplified();

                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }

        out << "</tr>\n";
    }

    out << "</table> </center>\n"

           "</body>\n"

           "</html>\n";

    QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), "*.pdf");

    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::PrinterResolution);

    printer.setOutputFormat(QPrinter::PdfFormat);

    printer.setPaperSize(QPrinter::A4);

    printer.setOutputFileName(fileName);

    QTextDocument doc;

    doc.setHtml(strStream);

    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number

    doc.print(&printer);
}
void MainWindow::afficherStatistiques()
{
    int totalPersonnes = p.getTotalPersonnes();
    int adminCount = p.getRoleCount("Admin");
    int ingenieurSonCount = p.getRoleCount("ingenieur son");
    int animateurCount = p.getRoleCount("Animateur");

    // Calcul des pourcentages
    qreal adminPercentage = (qreal)adminCount / totalPersonnes * 100;
    qreal ingenieurSonPercentage = (qreal)ingenieurSonCount / totalPersonnes * 100;
    qreal animateurPercentage = (qreal)animateurCount / totalPersonnes * 100;

    // Création du diagramme circulaire
    QPieSeries *series = new QPieSeries();
    series->append(QString("Admin (%1%)").arg(adminPercentage), adminPercentage);
    series->append(QString("Ingénieur Son (%1%)").arg(ingenieurSonPercentage), ingenieurSonPercentage);
    series->append(QString("Animateur (%1%)").arg(animateurPercentage), animateurPercentage);

    // Définition des couleurs pour chaque segment
    series->slices().at(0)->setColor(Qt::red);   // Admin en rouge
    series->slices().at(1)->setColor(Qt::blue);  // Ingénieur Son en bleu
    series->slices().at(2)->setColor(Qt::green); // Animateur en vert

    // Création du diagramme et de la vue du diagramme
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des rôles");

    // Création de la vue du diagramme
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Affichage de la vue du diagramme
    QMainWindow *statWindow = new QMainWindow();
    statWindow->setCentralWidget(chartView);
    statWindow->resize(400, 300);
    statWindow->show();
}

void MainWindow::showMainWindow()
{
}

void MainWindow::on_pushButton_12_clicked()
{

    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/QmlMap.qml")));
    ui->quickWidget->show();

    emit setCenterPosition(34.0, 9.0);
    emit setLocationMarking(34.0, 9.0);
    auto Obje = ui->quickWidget->rootObject();
    connect(this, SIGNAL(setCenterPosition(QVariant, QVariant)), Obje, SLOT(setCenterPosition(QVariant, QVariant)));
    connect(this, SIGNAL(setLocationMarking(QVariant, QVariant)), Obje, SLOT(setLocationMarking(QVariant, QVariant)));
}
bool MainWindow::checkRFIDInDatabase(const QString &idCarteRFID)
{
    // Créer une requête SQL pour vérifier si l'ID de carte RFID existe dans la base de données
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM PERSONNELS WHERE CARTE = :idCarte");
    query.bindValue(":idCarte", idCarteRFID);

    // Exécuter la requête
    if (query.exec() && query.next())
    {
        // Si le nombre de résultats retournés est supérieur à 0, cela signifie que l'ID de carte RFID existe dans la base de données
        int count = query.value(0).toInt();
        return count > 0;
    }
    else
    {
        // En cas d'erreur lors de l'exécution de la requête, affichez un message de débogage
        qDebug() << "Erreur lors de la vérification de l'ID de carte RFID dans la base de données:" << query.lastError().text();
        return false;
    }
}

void MainWindow::readRFID(const QString &idCarteRFID)
{
    // Vérifier si l'identifiant de la carte RFID est présent dans la base de données
    if (checkRFIDInDatabase(idCarteRFID))
    {
        // Si l'identifiant est trouvé, autoriser l'accès à l'application
        QMessageBox::information(this, "Accès autorisé", "Bienvenue dans l'application !");
        // Afficher l'interface principale de l'application
        this->showMainWindow();
    }
    else
    {
        // Si l'identifiant n'est pas trouvé, afficher un message d'erreur
        QMessageBox::warning(this, "Accès refusé", "Carte RFID non reconnue !");
    }
}

QString MainWindow::extractRFID(const QString &rfidData)
{
    // Ajoutez votre logique d'extraction de l'ID de carte RFID ici
    // Par exemple, si rfidData contient uniquement l'ID de la carte RFID, vous pouvez simplement le retourner
    return rfidData;
}
void MainWindow::processRFIDData(const QString &rfidData)
{
    // Extrayez l'ID de carte RFID des données reçues
    QString idCarteRFID = extractRFID(rfidData); // À remplacer par votre propre logique d'extraction

    // Vérifiez si l'ID de carte RFID existe dans la base de données
    if (checkRFIDInDatabase(idCarteRFID))
    {
        // Affichez un message indiquant que la carte RFID a été reconnue
        QMessageBox::information(this, "Carte RFID reconnue", "Bienvenue !");

        // Faites ce que vous devez faire après avoir reconnu la carte RFID, comme accéder à l'interface principale
        showMainWindow();
    }
    else
    {
        // Affichez un message indiquant que la carte RFID n'a pas été reconnue
        QMessageBox::warning(this, "Carte RFID non reconnue", "Carte RFID non reconnue !");
    }
}

// Supposons que vous ayez une fonction dans votre application Qt pour gérer la réception de données d'Arduino
void MainWindow::handleArduinoData()
{
    // Lire les données depuis Arduino
    QByteArray dataFromArduino = arduino->read_from_arduino();

    // Convertir les données en QString si nécessaire
    QString dataStringFromArduino = QString::fromLatin1(dataFromArduino);

    // Traiter les données reçues, par exemple, les afficher dans la console
    qDebug() << "Data received from Arduino:" << dataStringFromArduino;

    // Envoyer les données à la fonction processRFIDData de votre classe MainWindow
    this->processRFIDData(dataStringFromArduino);
}

void MainWindow::on_scaner_clicked()
{
    QByteArray dataFromArduino = arduino->read_from_arduino();

    // Convertir les données en QString si nécessaire
    QString dataStringFromArduino = QString::fromLatin1(dataFromArduino);

    // Traiter les données reçues, par exemple, les afficher dans la console
    qDebug() << "Data received from Arduino:" << dataStringFromArduino;

    // Envoyer les données à la fonction processRFIDData de votre classe MainWindow
    this->processRFIDData(dataStringFromArduino);
}

// farah
void MainWindow::showtab()
{
    ui->tableView_enr->verticalHeader()->hide();
    ui->tableView_enr->setSelectionBehavior(QAbstractItemView::SelectRows);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(enr.afficher());
    proxyModel->setSourceModel(enr.afficher());

    // Enable sorting in the proxy model
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive); // Set case sensitivity for sorting
    ui->tableView_enr->setSortingEnabled(true);              // Enable sorting in the view
    ui->tableView_enr->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView_enr->setModel(proxyModel);
    ui->tableView_enr->setItemDelegate(new CustomDelegate);

    // Clear the existing items in the combo box
    ui->comboBox_modifIdenr->clear();

    // Fill the combo box with items from the model
    for (int row = 0; row < enr.afficher()->rowCount(); ++row)
    {
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

    enregistrement enr(ID_ENR, NOM_ENR, QUALITE_ENR, ID_EM_ENR, newFilePath);

    bool test = enr.ajouter();

    if (test)
    {
        QMessageBox::information(this, "Succès", "L'enregistrement a été ajouté avec succès.");
        ui->tableView_enr->setModel(enr.afficher());
    }
    else
    {
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
    enregistrement enr(ID_ENR, NOM_ENR, QUALITE_ENR, ID_EM_ENR, newFilePath);

    // Appeler la fonction d'affichage des enregistrements
    QAbstractItemModel *model = enr.afficher();

    // Vérifier si le modèle est valide
    if (model)
    {
        // Définir les noms de colonnes sur le modèle de données
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID Emission"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Path"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Qualité"));

        QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(model);
        proxyModel->setSourceModel(model);

        proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive); // Set case sensitivity for sorting
        ui->tableView_enr->setSortingEnabled(true);              // Enable sorting in the view
        ui->tableView_enr->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableView_enr->setModel(proxyModel);
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de la récupération des enregistrements.");
    }
}

void MainWindow::on_pushButton_rechEnreg_clicked()
{
    QString nom_enr = ui->lineEdit_idrecheng->text();

    enregistrement enr;
    bool resultatRecherche = enr.rechercherParNom(nom_enr);

    if (resultatRecherche)
    {
        QMessageBox::information(this, "Résultat de la recherche", "Le nom a été trouvé.");
    }
    else
    {
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
    if (triReussi)
    {
        // Récupérer le modèle associé à la table view
        QSqlQueryModel *model = qobject_cast<QSqlQueryModel *>(ui->tableView_enr->model());

        // Tri par ID croissant dans le modèle (dans la requête SQL)
        model->setQuery("SELECT * FROM ENREGISTREMENT ORDER BY ID_ENR ASC");

        // Vérifier si une erreur s'est produite lors du tri
        if (model->lastError().isValid())
        {
            QMessageBox::critical(this, "Erreur de tri", "Une erreur s'est produite lors du tri des enregistrements par ID croissant.");
            return;
        }

        // Actualiser la vue pour refléter les données triées
        ui->tableView_enr->setModel(model);

        QMessageBox::information(this, "Tri réussi", "Les enregistrements ont été triés par ID croissant.");
    }
    else
    {
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
    if (triReussi)
    {
        // Récupérer le modèle associé à la table view
        QSqlQueryModel *model = qobject_cast<QSqlQueryModel *>(ui->tableView_enr->model());

        // Tri par ID décroissant dans le modèle (dans la requête SQL)
        model->setQuery("SELECT * FROM ENREGISTREMENT ORDER BY ID_ENR DESC");

        // Vérifier si une erreur s'est produite lors du tri
        if (model->lastError().isValid())
        {
            QMessageBox::critical(this, "Erreur de tri", "Une erreur s'est produite lors du tri des enregistrements par ID décroissant.");
            return;
        }

        // Actualiser la vue pour refléter les données triées
        ui->tableView_enr->setModel(model);

        QMessageBox::information(this, "Tri réussi", "Les enregistrements ont été triés par ID décroissant.");
    }
    else
    {
        QMessageBox::critical(this, "Erreur de tri", "Une erreur s'est produite lors du tri des enregistrements par ID décroissant.");
    }
}
void MainWindow::on_pushButton_exportpdf_clicked()
{

    QString strStream;

    QTextStream out(&strStream);

    const int rowCount = ui->tableView_enr->model()->rowCount();

    const int columnCount = ui->tableView_enr->model()->columnCount();

    out << "<html>\n"

           "<head>\n"

           "<meta Content=\"Text/html; charset=Windows-1251\">\n"

        << QString("<title>%1</title>\n").arg("strTitle")

        << "</head>\n"

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

    for (int row = 0; row < rowCount; row++)
    {

        out << "<tr>";

        for (int column = 0; column < columnCount; column++)
        {

            if (!ui->tableView_enr->isColumnHidden(column))
            {

                QString data = ui->tableView_enr->model()->data(ui->tableView_enr->model()->index(row, column)).toString().simplified();

                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }

        out << "</tr>\n";
    }

    out << "</table> </center>\n"

           "</body>\n"

           "</html>\n";

    QString fileName = QFileDialog::getSaveFileName((QWidget *)0, "Sauvegarder en PDF", QString(), "*.pdf");

    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::PrinterResolution);

    printer.setOutputFormat(QPrinter::PdfFormat);

    printer.setPaperSize(QPrinter::A4);

    printer.setOutputFileName(fileName);

    QTextDocument doc;

    doc.setHtml(strStream);

    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number

    doc.print(&printer);
}
void MainWindow::on_pushButton_statistiqueenr_clicked()
{
    int totalEnregistrements = enr.getTotalEnregistrements();
    int nombreEmissions = 0;
    int nombrePublicites = 0;

    for (int row = 0; row < enr.afficher()->rowCount(); ++row)
    {
        QModelIndex index = enr.afficher()->index(row, 0);

        QVariant file = index.sibling(index.row(), 3).data(Qt::DisplayRole);
        QString currentDir = QDir::currentPath();
        QString absoluteFilePath = currentDir + "/" + file.toString();

        QFileInfo fileInfo(absoluteFilePath);
        qint64 fileSize = fileInfo.size(); // Size of the file in bytes

        if (fileSize > 7 * 1024 * 1024)
        {
            nombreEmissions++;
        }
        else
        {
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
    series->slices().at(0)->setColor(Qt::blue);  // Émissions en bleu
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

void MainWindow::on_lineEdit_idrecheng_textChanged(const QString &arg1)
{
    QString filterText = arg1.trimmed();

    enregistrement enreg;
    // recherche
    QSqlQueryModel *filteredModel = enreg.filtrerParNom(arg1);
    // tri
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(filteredModel);
    proxyModel->setSourceModel(filteredModel);
    proxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    ui->tableView_enr->setSortingEnabled(true);

    // Selection unique
    ui->tableView_enr->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView_enr->setModel(proxyModel);
}

void MainWindow::on_pushButton_supenr_clicked()
{
    QItemSelectionModel *select = ui->tableView_enr->selectionModel();
    QModelIndexList selectedRows = select->selectedRows();
    foreach (const QModelIndex &index, selectedRows)
    {
        QVariant idVariant = ui->tableView_enr->model()->data(ui->tableView_enr->model()->index(index.row(), 0));
        QVariant pathVariant = ui->tableView_enr->model()->data(ui->tableView_enr->model()->index(index.row(), 3));
        int id_enr = idVariant.toInt();
        QString path_enr = pathVariant.toString();
        enregistrement enr;
        bool test = enr.supprimer(id_enr, path_enr);
        if (test)
        {
            QMessageBox::information(this, "Succès", "L'enregistrement a été supprimé avec succès.");
            ui->tableView_enr->setModel(enr.afficher());
        }
        else
        {
            QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de la suppression de l'enregistrement.");
        }
    }
}

void MainWindow::on_pushButton_modifenr_clicked()
{
    QModelIndex selectedIndex = ui->tableView_enr->selectionModel()->currentIndex();
    if (selectedIndex.isValid())
    {
        QVariant data = ui->tableView_enr->model()->data(selectedIndex, Qt::DisplayRole);
    }
    else
    {
        qDebug() << "No item selected.";
    }
}

void MainWindow::on_comboBox_modifIdenr_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;
    query.prepare("SELECT ID_ENR, NOM_ENR, QUALITE_ENR, ID_EM_ENR, PATH_ENR FROM ENREGISTREMENT WHERE ID_ENR = ?");
    query.bindValue(0, arg1);
    if (query.exec() && query.next())
    {
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

    if (!originalFilePath.isEmpty())
    {
        QFileInfo originalFileInfo(originalFilePath);
        QString newFileName = newDirectory + originalFileInfo.fileName();
        if (QFile::copy(originalFilePath, "./" + newFileName))
        {
            newFilePath = newFileName;
        }
        else
        {
            qDebug() << "Failed to copy file.";
        }
        ui->lineEdit_modifcheminEnr->setText(newFilePath);
    }
}

void MainWindow::on_pushButton_32_clicked()
{
    QString NOM_ENR = ui->lineEdit_modifnomenr->text();
    QString QUALITE_ENR = ui->comboBox_modifqualite_enr->currentText();
    int ID_ENR = ui->comboBox_modifIdenr->currentText().toInt();
    int ID_EM_ENR = ui->lineEdit_modifidenrEm->text().toInt();
    QString PATH_ENR = ui->lineEdit_modifcheminEnr->text();

    bool test = enr.modifier(ID_ENR, NOM_ENR, QUALITE_ENR, ID_EM_ENR, PATH_ENR);

    if (test)
    {
        QMessageBox::information(this, "Succès", "L'enregistrement a été modifié avec succès.");
        ui->tableView_enr->setModel(enr.afficher());
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de la modification de l'enregistrement.");
    }
}

void MainWindow::on_pushButton_lecEnr_clicked()
{
    QItemSelectionModel *select = ui->tableView_enr->selectionModel();
    QModelIndexList selectedRows = select->selectedRows();
    foreach (const QModelIndex &index, selectedRows)
    {
        QVariant pathVariant = ui->tableView_enr->model()->data(ui->tableView_enr->model()->index(index.row(), 3));
        QString currentDir = QDir::currentPath();
        QString absoluteFilePath = currentDir + "/" + pathVariant.toString();
        QMediaPlayer *player = new QMediaPlayer();
        QVideoWidget *video = new QVideoWidget();
        video->setGeometry(20, 20, 640, 480);
        player->setVideoOutput(video);
        player->setMedia(QUrl(absoluteFilePath));
        video->show();
        player->play();
    }
}

void MainWindow::on_pushButton_importvidenr_clicked()
{
    QString originalFilePath = QFileDialog::getOpenFileName(this, tr("Selectionner le fichier de la video"), "", tr("MP4 Files (*.MP4)"));
    QString newDirectory = "videos/";

    if (!originalFilePath.isEmpty())
    {
        QFileInfo originalFileInfo(originalFilePath);
        QString newFileName = newDirectory + originalFileInfo.fileName();
        if (QFile::copy(originalFilePath, "./" + newFileName))
        {
            newFilePath = newFileName;
        }
        else
        {
            qDebug() << "Failed to copy file.";
        }
        ui->lineEdit_cheminEnr->setText(newFilePath);
    }
}
