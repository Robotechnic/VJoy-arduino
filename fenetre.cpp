#include "fenetre.h"
#include "ui_fenetre.h"


#include <Windows.h>

const qint32 min = 0x1;
const qint32 max = 0x8000;

fenetre::fenetre(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fenetre)
{
    ui->setupUi(this);
    //initialisation de l'afichage des commandes
    pad1 = new QJoypad(this);
    pad2 = new QJoypad(this);
    ui->rcJoypad->addWidget(pad1);
    ui->rcJoypad->addWidget(pad2);
    connect(pad1,SIGNAL(newJoypadValues(float,float)),this,SLOT(setVjoy(float,float)));
    connect(pad2,SIGNAL(newJoypadValues(float,float)),this,SLOT(setVjoy(float,float)));

    getPorts();//récupération des ports série actuelements disponibles
    connect(ui->actionActualiser,SIGNAL(triggered()),this,SLOT(on_actualiser_clicked()));
    moniteur = new MoniteurSerie; // initialisation du moniteur série

    mode = '1'; // le mode de vol



    //initialisation des QAction
    connect(ui->actionMode_1,SIGNAL(triggered()),this,SLOT(setMode()));
    connect(ui->actionMode_2,SIGNAL(triggered()),this,SLOT(setMode()));
}

fenetre::~fenetre()
{
    delete ui;
}

void fenetre::on_connectButton_clicked() // connexion a la carte arduino
{
    port = new QSerialPort(QSerialPortInfo::availablePorts().at(ui->port->currentIndex()),this);//initialisation du port selectionnée
    port->setBaudRate(QSerialPort::Baud9600);

    if (port->open(QIODevice::ReadOnly)) // ouverture du serial port
    {
        QMessageBox::information(this,"Ouverture","Port série ouvert avec succés");

        connect(port,SIGNAL(readyRead()),this,SLOT(textRessus())); //texte dasn le moniteur série
        connect(port, SIGNAL(error(QSerialPort::SerialPortError)), this,SLOT(handleError(QSerialPort::SerialPortError))); //si il y a une erreur


        connectGui(true);//actualiser l'interface graphique pour s'adapter au fait que la carte soit conecté
    }
    else {
          QMessageBox::warning(this,"Ouverture","Erreur de l'ouverture du port"+port->portName()); // erreur
    }
}

void fenetre::getPorts()
{

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) { //pour touts les ports
        qDebug()<<info.portName();

        ui->port->clear();
        ui->port->addItem(info.portName()); // on ajoute au combobox pour que l'utilisateur puisse choisir
    }
}

void fenetre::on_actualiser_clicked()
{
    getPorts(); // actualisation des ports disponbles (pas encore automatique)
}


void fenetre::on_disconnect_clicked()// on se déconecte de l'arduino
{
    connectGui(false); // actualisation de la fenetre
    port->close(); // fermeture du port serie
}

void fenetre::on_actionOuvrir_le_moniteur_s_rie_triggered()
{
    moniteur->show(); // ouverture du moniteur série

    moniteur->setPort(port->portName());
}

void fenetre::textRessus() // reception de texte via le Serial Port
{
    txt = port->readAll();
    txtTotal += txt;
    if (txtTotal.right(2) == "\r\n")
    {
        moniteur->log(txtTotal);

        QStringList voies = txtTotal.split(":");

        int s = voies.size();

        moniteur->setVoies(s);

        y = map(voies[0].toInt(),695,1494,-100,100); //on mape les valeurs pour les aficher
        x = map(voies[1].toInt(),695,1494,-100,100);
        Ry = map(voies[2].toInt(),695,1494,-100,100);
        Rx = map(voies[3].toInt(),695,1494,-100,100);
        if (s>=5) // si les voies sont disponibles on les mape
            sl01 = map(voies[4].toInt(),695,1494,-100,100);
        if (s>=6)
            sl02 = map(voies[5].toInt(),695,1494,-100,100);

        txtTotal = QString();
    }

    actualiserSlider(); // on actualise l'afichage
}

void fenetre::erreur(QSerialPort::SerialPortError err) // si il y a une erreur
{
    qDebug()<<"erreur";
    if (err == QSerialPort::ResourceError) {
            QMessageBox::critical(this, tr("Erreur critique"), port->errorString());
            port->close();
    }
}
void fenetre::actualiserSlider()
{
    switch (mode) { // on afiche les valeurs selon le mode selectionnée
        case '1':
            pad1->setJoypadValues(-Rx,-Ry);
            pad2->setJoypadValues(-x,-y);
        break;
        case '2':
            pad1->setJoypadValues(-Rx,-y);
            pad2->setJoypadValues(-x,-Ry);
        break;
    }
}
void fenetre::connectGui(bool connect) // actualiser le gui
{
    if (connect){
        ui->connectButton->setMaximumWidth(0);
        ui->disconnect->setMaximumWidth(16777215);
        pad1->setMouse(false);
        pad2->setMouse(false);

        ui->menuCarte->setEnabled(true);
    }
    else{
        ui->connectButton->setMaximumWidth(16777215);
        ui->disconnect->setMaximumWidth(0);

        pad1->setMouse(true);
        pad2->setMouse(true);
        moniteur->hide();
        ui->menuCarte->setEnabled(false);
    }
}
void fenetre::initVjoy() // initialisation de VJoy
{

}


int fenetre::map(int x, int in_min, int in_max, int out_min, int out_max) // fonction de mapage
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void fenetre::on_actionQuiter_triggered()
{
    this->close();
}

void fenetre::setVjoy(float xs, float ys)
{
//    SetAxis(map(x,-100,100,min,max),VJoyInterface,HID_USAGE_X);
//    SetAxis(map(y,-100,100,min,max),VJoyInterface,HID_USAGE_Y);
//    SetAxis(map(Rx,-100,100,min,max),VJoyInterface,HID_USAGE_Z);
//    SetAxis(map(Ry,-100,100,min,max),VJoyInterface,HID_USAGE_RX);
//    SetAxis(map(sl01,-100,100,min,max),VJoyInterface,HID_USAGE_RY);
//    SetAxis(map(sl02,-100,100,min,max),VJoyInterface,HID_USAGE_RZ);
}
void fenetre::setMode(){
    QAction* envoyeur = qobject_cast<QAction*>(sender());

    if(envoyeur->text() == "Mode 1")
    {
        mode = '1';
    }
    else if(envoyeur->text() == "Mode 2")
    {
        mode = '2';
    }
}

void fenetre::on_actionD_conecter_triggered()
{
    port->close();
    this->connectGui(false);
}
