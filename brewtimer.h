#ifndef BREWTIMER_H
#define BREWTIMER_H

#include <QMainWindow>

namespace Ui {
class BrewTimer;
}

class BrewTimer : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit BrewTimer(QWidget *parent = 0);
    ~BrewTimer();
    
private slots:
    void on_actionOpen_triggered();

private:
    Ui::BrewTimer *ui;
};

#endif // BREWTIMER_H
