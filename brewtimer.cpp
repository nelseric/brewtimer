#include "brewtimer.h"
#include "ui_brewtimer.h"
#include <QFileDialog>
#include <QDebug>
#include <QtXml>
#include <QDomDocument>
#include <QMessageBox>


BrewTimer::BrewTimer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BrewTimer)
{
    ui->setupUi(this);

    //timer stuff
    iTimer = new QTimer(this);
    QObject::connect(iTimer, SIGNAL(timeout()), this, SLOT(showcurrentTime()));

    //audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);

    mediaObject->setCurrentSource(Phonon::MediaSource("alarm.mp3"));
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    Phonon::createPath(mediaObject, audioOutput);

}

BrewTimer::~BrewTimer()
{
    delete ui;
}


void BrewTimer::showcurrentTime()
{
    QTime times = (QTime::currentTime());
    QString currentTime=times.toString("mm:ss");
    ui->event_done_time->setText(currentTime);
    ui->event_next_time->setText(currentTime);
}

void printNode(QDomNode *node);
void BrewTimer::on_actionOpen_triggered()
{
    QString name =  QFileDialog::getOpenFileName(this, tr("Open BeerXML File"), "$HOME", tr("BeerXML Files (*.xml)"));
    QFile xml_file(name);
    if (!xml_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QDomDocument *recipe = new QDomDocument("beerxml");
    recipe->setContent(&xml_file);
    printNode(recipe);


}
int ilvl = 0;
void printNode(QDomNode *node) {
    QString indent("");
    for(int i = 0; i < ilvl; i ++) {
        indent += "\t";
    }
    QString name = node->nodeName();
    QString value = node->nodeValue();
    if(node->childNodes().count() == 1) {
        value = node->childNodes().item(1).nodeValue();
        qDebug() << indent << "<" << name << ">={" << value << "}";
    } else {
        qDebug() << indent << "<" << name << ">={" << value << "}";
        ilvl++;
        for(int i = 0;  i < node->childNodes().count(); i++) {
            QDomNode item = node->childNodes().item(i);
            printNode(&item);
        }
        ilvl--;
    }
}

void BrewTimer::on_actionRecipe_triggered()
{
    if (ui->stackedWidget->currentIndex() == 0) {
        ui->stackedWidget->setCurrentIndex(1);
    } else {
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void BrewTimer::on_actionQuit_triggered()
{
    exit(3);
}

void BrewTimer::on_actionFullscreen_triggered()
{
    if (this->isFullScreen()) {
        this->showNormal();
    } else {
        this->showFullScreen();
    }
}

void BrewTimer::on_actionStart_triggered()
{
    iTimer->start();

}

void BrewTimer::on_actionStop_triggered()
{
    iTimer->stop();
}


void BrewTimer::on_actionAbout_triggered()
{
    mediaObject->play();
    QMessageBox::information(this, tr("About Brew Timer"),
                             tr("A Simple Home Brew Beer Timer - helps"
                                " in the task of timing each process of homebrewing."));

}



