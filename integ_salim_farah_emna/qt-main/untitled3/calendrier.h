#ifndef CALENDRIER_H
#define CALENDRIER_H

#include <QMainWindow>

namespace Ui {
class calendrier;
}

class calendrier : public QMainWindow
{
    Q_OBJECT

public:
    explicit calendrier(QWidget *parent = nullptr);
    ~calendrier();

private slots:
    void on_pushButton_reservation_clicked();

private:
    Ui::calendrier *ui;
    void on_calendarWidget_clicked(const QDate&);
};

#endif // CALENDRIER_H
