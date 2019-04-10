#ifndef FENETRE_H
#define FENETRE_H

#include <QMainWindow>
#include "joypad/qjoypad.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
#include <QMessageBox>
#include "moniteurserie.h"


namespace Ui {
class fenetre;
}

class fenetre : public QMainWindow
{
    Q_OBJECT

public:
    explicit fenetre(QWidget *parent = nullptr);
    ~fenetre();
    void getPorts();

private slots:
    void on_connectButton_clicked();
    void on_actualiser_clicked();
    void on_disconnect_clicked();
    void on_actionOuvrir_le_moniteur_s_rie_triggered();
    void textRessus();
    void erreur(QSerialPort::SerialPortError err);

    void on_actionQuiter_triggered();

private:
    void actualiserSlider();
    void connectGui(bool connect);
    int map(int x, int in_min, int in_max, int out_min, int out_max);
    void initVjoy();
    Ui::fenetre *ui;
    QJoypad *pad1;
    QJoypad *pad2;
    QSerialPort *port;
    MoniteurSerie *moniteur;
    int x,y,Rx,Ry,sl01,sl02;
    char mode;
};

#endif // FENETRE_H
