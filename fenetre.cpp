#include "fenetre.h"
#include "ui_fenetre.h"


int min = 695;
int max = 1490;
struct gamepadUinput::input_event evt;

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
//    connect(pad1,SIGNAL(newJoypadValues(float,float)),this,SLOT(setVjoy()));
//    connect(pad2,SIGNAL(newJoypadValues(float,float)),this,SLOT(setVjoy()));

    getPorts();//récupération des ports série actuelements disponibles
    connect(ui->actionActualiser,SIGNAL(triggered()),this,SLOT(on_actualiser_clicked()));
    moniteur = new MoniteurSerie; // initialisation du moniteur série

    mode = '1'; // le mode de vol
    inituInput();


    //initialisation des QAction
    connect(ui->actionMode_1,SIGNAL(triggered()),this,SLOT(setMode()));
    connect(ui->actionMode_2,SIGNAL(triggered()),this,SLOT(setMode()));
}

fenetre::~fenetre()
{
    if(gamepadUinput::ioctl(fd, UI_DEV_DESTROY) < 0)
    {
        printf("error: ioctl");
    }
    gamepadUinput::close(fd);
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
        connect(port, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this,SLOT(erreur(QSerialPort::SerialPortError))); //si il y a une erreur

        connectGui(true);//actualiser l'interface graphique pour s'adapter au fait que la carte soit conecté
    }
    else {
        qDebug()<<"Erreur de connexion: "<<port->error();
          QMessageBox::warning(this,"Ouverture","Erreur de l'ouverture du port "+port->portName()+"\n"+port->errorString()); // erreur
    }
}

void fenetre::getPorts()
{

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) { //pour touts les ports
        qDebug()<<"Port: "<<info.portName();

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

        y = map(voies[0].toInt(),min,max,-100,100); //on mape les valeurs pour les aficher
        x = map(voies[1].toInt(),min,max,-100,100);
        Ry = map(voies[2].toInt(),min,max,-100,100);
        Rx = map(voies[3].toInt(),min,max,-100,100);
        setVjoy();
        if (s>=5) // si les voies sont disponibles on les mape
            sl01 = map(voies[4].toInt(),695,1490,-100,100);
        if (s>=6)
            sl02 = map(voies[5].toInt(),695,1490,-100,100);

        txtTotal = QString();
    }

    actualiserSlider(); // on actualise l'afichage
}

void fenetre::erreur(QSerialPort::SerialPortError err) // si il y a une erreur
{
    qDebug()<<"erreur";
    if (err == QSerialPort::ResourceError) {
            QMessageBox::critical(this, "Erreur critique", port->errorString());
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
void fenetre::inituInput() // initialisation de uinput
{
    this->fd = gamepadUinput::open("/dev/uinput",O_WRONLY | O_NONBLOCK);
    if (fd < 0)
    {
        QMessageBox::warning(this,"Erreur","Echec de l'ouverture de uinput");
        this->close();
    }
    gamepadUinput::ioctl(fd, UI_SET_EVBIT, EV_KEY);
    gamepadUinput::ioctl(fd, UI_SET_KEYBIT, BTN_A);
    gamepadUinput::ioctl(fd, UI_SET_KEYBIT, BTN_B);
    gamepadUinput::ioctl(fd, UI_SET_KEYBIT, BTN_DPAD_RIGHT);
    gamepadUinput::ioctl(fd, UI_SET_EVBIT, EV_ABS);
    gamepadUinput::ioctl(fd, UI_SET_ABSBIT, ABS_X);
    gamepadUinput::ioctl(fd, UI_SET_ABSBIT, ABS_Y);
    gamepadUinput::ioctl(fd, UI_SET_ABSBIT, ABS_RX);
    gamepadUinput::ioctl(fd, UI_SET_ABSBIT, ABS_RY);

    struct gamepadUinput::uinput_user_dev uidev; //set des parametres de la manette
    memset(&uidev, 0, sizeof(uidev));
    uidev.id.bustype = BUS_USB;
    uidev.id.vendor  = 0x1234;
    uidev.id.product = 0x5678;
    snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "Uinput RC"); //Nom de la radio

    uidev.absmax[ABS_X] = 512; //Parameters of thumbsticks
    uidev.absmin[ABS_X] = -512;
    uidev.absfuzz[ABS_X] = 0;
    uidev.absflat[ABS_X] = 15;
    uidev.absmax[ABS_Y] = 512;
    uidev.absmin[ABS_Y] = -512;
    uidev.absfuzz[ABS_Y] = 0;
    uidev.absflat[ABS_Y] = 15;
    uidev.absmax[ABS_RX] = 512;
    uidev.absmin[ABS_RX] = -512;
    uidev.absfuzz[ABS_RX] = 0;
    uidev.absflat[ABS_RX] = 16;
    uidev.absmax[ABS_RY] = 512;
    uidev.absmin[ABS_RY] = -512;
    uidev.absfuzz[ABS_RY] = 0;
    uidev.absflat[ABS_RY] = 16;

    if(gamepadUinput::write(fd, &uidev, sizeof(uidev)) < 0) //ecriture des parametres
    {
        QMessageBox::warning(this,"erreur","error: write");//si erreur
        this->close();
    }

    if(gamepadUinput::ioctl(fd, UI_DEV_CREATE) < 0) //ecriture du périférique que l'on vien de créer
    {
        QMessageBox::warning(this,"erreur","error: ui_dev_create");
        this->close();
    }
}


int fenetre::map(int x, int in_min, int in_max, int out_min, int out_max) // fonction de mapage
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void fenetre::on_actionQuiter_triggered()
{
    this->close();
}

void fenetre::setVjoy(){
    setAxis(EV_ABS,int(map(this->x,-100,100,0,256)),ABS_X);
    setAxis(EV_ABS,int(map(this->y,-100,100,0,256)),ABS_Y);
    setAxis(EV_ABS,int(map(this->Rx,-100,100,0,256)),ABS_RX);
    setAxis(EV_ABS,int(map(this->Ry,-100,100,0,256)),ABS_RY);
    setAxis(EV_KEY,int(map(this->sl01+5,-100,100,0,1)),BTN_A);
    setAxis(EV_KEY,int(map(this->sl02+5,-100,100,0,1)),BTN_B);
    setAxis(EV_SYN, SYN_REPORT,0);
}
void fenetre::setAxis(int type, int value,int code){
    //qDebug()<<code<<value<<ABS_X;
    struct gamepadUinput::input_event ie;
    ie.type=type;
    ie.code=code;
    ie.value=value;
    ie.time.tv_sec=0;
    ie.time.tv_usec=0;
    gamepadUinput::write(this->fd,&ie,sizeof(ie));
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
