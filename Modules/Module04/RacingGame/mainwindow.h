#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "car.h"
#include "racetrack.h"
#include "carthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startRace();
    void pauseRace();
    void exitGame();
    void updateCarPosition();

private:
    Ui::MainWindow *ui;
    RaceTrack *raceTrack;
    QList<Car*> carList;
    QList<CarThread*> threadList;
    QGraphicsScene *scene;
    QList<QGraphicsRectItem*> carGraphics;
};

#endif // MAINWINDOW_H
