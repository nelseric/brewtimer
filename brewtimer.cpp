#include "brewtimer.h"
#include "ui_brewtimer.h"
#include <QFileDialog>
#include <QDebug>
#include <QtXml>
#include <QDomDocument>

BrewTimer::BrewTimer(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::BrewTimer)
{
    ui->setupUi(this);
}

BrewTimer::~BrewTimer()
{
    delete ui;
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
void printNode(QDomNode *node){
    QString indent("");
    for(int i = 0; i < ilvl; i ++){
        indent += "\t";
    }
    QString name = node->nodeName();
    QString value = node->nodeValue();
    if(node->childNodes().count() == 1){
        value = node->childNodes().item(1).nodeValue();
        qDebug() << indent << "<" << name << ">={" << value << "}";
    } else {
        qDebug() << indent << "<" << name << ">={" << value << "}";
        ilvl++;
        for(int i = 0;  i < node->childNodes().count(); i++){
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
    }else {
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
    brewTimer = new QTimer(this);
    brewTimer->setInterval(1000);
    brewTimer->start();
    QObject::connect(brewTimer, SIGNAL(timeout()), this, SLOT(TimeOut()));

}

void BrewTimer::on_actionStop_triggered()
{
    brewTimer->stop();
}

void TimeOut() {

}
