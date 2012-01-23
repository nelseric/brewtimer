#include <QtGui/QApplication>
#include "brewtimer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BrewTimer w;
    w.show();
    
    return a.exec();
}
