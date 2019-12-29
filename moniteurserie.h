#ifndef MONITEURSERIE_H
#define MONITEURSERIE_H

#include <QWidget>

namespace Ui {
class MoniteurSerie;
}

class MoniteurSerie : public QWidget
{
    Q_OBJECT

public:
    explicit MoniteurSerie(QWidget *parent = nullptr);
    ~MoniteurSerie();

    void log(QString log);
    void setPort(QString port);
    void setVoies(int voies);

private slots:
    void on_affichage_textChanged();

private:
    Ui::MoniteurSerie *ui;
};

#endif // MONITEURSERIE_H
