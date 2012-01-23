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

void BrewTimer::on_actionOpen_triggered()
{
    QString name =  QFileDialog::getOpenFileName(this, tr("Open BeerXML File"), "$HOME", tr("BeerXML Files (*.xml)"));
    QFile xml_file(name);
    if (!xml_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QDomDocument *recipe = new QDomDocument("beerxml");
    recipe->setContent(&xml_file);
    xml_file.close();

}
