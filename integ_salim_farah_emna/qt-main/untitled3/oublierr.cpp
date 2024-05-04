#include "oublierr.h"
#include "ui_oublierr.h"

oublierr::oublierr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::oublierr)
{
    ui->setupUi(this);
}

oublierr::~oublierr()
{
    delete ui;
}
