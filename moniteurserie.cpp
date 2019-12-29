#include "moniteurserie.h"
#include "ui_moniteurserie.h"

MoniteurSerie::MoniteurSerie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MoniteurSerie)
{
    ui->setupUi(this);
}

MoniteurSerie::~MoniteurSerie()
{
    delete ui;
}
void MoniteurSerie::log(QString log) // ajoute une ligne dans les log
{
    ui->affichage->appendPlainText(log);
}
void MoniteurSerie::setPort(QString port) // set le prot serie atuelement utilisé
{
    ui->port->setText(QString("Port: "+port));
}
void MoniteurSerie::setVoies(int voies) // set l'affichage du nombre de voies detectées
{
    ui->voies->setText(QString("Nombre de voies: "+QString::number(voies)));
}

void MoniteurSerie::on_affichage_textChanged()//défilement automatique
{

}
