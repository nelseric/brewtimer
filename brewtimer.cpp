#include "brewtimer.h"
#include "ui_brewtimer.h"

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
