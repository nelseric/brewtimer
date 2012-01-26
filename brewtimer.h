#ifndef BREWTIMER_H
#define BREWTIMER_H

#include <QMainWindow>
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <phonon/path.h>
#include <phonon/backendcapabilities.h>
#include <QTimer>
#include <QTime>
#include <QList>


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

    void on_actionRecipe_triggered();

    void on_actionQuit_triggered();

    void on_actionFullscreen_triggered();

    void on_actionStart_triggered();

    void on_actionStop_triggered();

    void showcurrentTime();

    void on_actionAbout_triggered();

private:
    Ui::BrewTimer *ui;

    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;

    QTimer *iTimer;
};

#endif // BREWTIMER_H
