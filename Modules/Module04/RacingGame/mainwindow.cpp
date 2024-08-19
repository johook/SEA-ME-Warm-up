#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "car.h"
#include "carthread.h"
#include "racetrack.h"

#include <QDebug>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , raceTrack(new RaceTrack(500))
{
    ui->setupUi(this);

    scene = new QGraphicsScene(0,0,500,300);
    ui->graphicsView->setScene(scene);

    // 임의로 자동차 추가
    carList.append(new Car(1, 10, this));
    carList.append(new Car(2, 11, this));
    carList.append(new Car(3, 12, this));

    for (int i=0;i<carList.size();i++) {
        QGraphicsRectItem *carItem = new QGraphicsRectItem(0, 0, 40, 20); // 자동차를 나타내는 직사각형
        QColor color(QRandomGenerator::global()->bounded(256),
                     QRandomGenerator::global()->bounded(256),
                     QRandomGenerator::global()->bounded(256));
            carItem->setBrush(QBrush(color));


        carItem->setPos(0, i * 40 + 100);
        scene->addItem(carItem);
        carGraphics.append(carItem);
        connect(carList[i], &Car::positionChanged, this, &MainWindow::updateCarPosition);
    }
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startRace);
    connect(ui->pauseButton, &QPushButton::clicked, this, &MainWindow::pauseRace);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::exitGame);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete raceTrack;
    for (CarThread *thread : threadList) {
        thread->quit();
        thread->wait();
        delete thread;
    }
}

QMutex mutex;

void MainWindow::startRace()
{
    qDebug() << "Race started!";
    for (Car *car : carList) {
        CarThread *carThread = new CarThread(car, raceTrack, &mutex);
        threadList.append(carThread);

        // 우선순위 설정
        if (car->getid() == 1) {
            carThread->setPriority(QThread::HighPriority); // 자동차 1에게 높은 우선순위 부여
        } else if (car->getid() == 2) {
            carThread->setPriority(QThread::NormalPriority); // 자동차 2에게 보통 우선순위 부여
        } else {
            carThread->setPriority(QThread::LowPriority); // 자동차 3에게 낮은 우선순위 부여
        }

        carThread->start(); //멀티스레드를 위해서
    }
}

void MainWindow::pauseRace() {
    qDebug() << "Race paused!";
    for (CarThread *carThread : threadList) {
        carThread->requestInterruption(); // 스레드를 중단하도록 요청
    }
}

void MainWindow::exitGame() {
    qDebug() << "Exiting game!";
    for (CarThread *carThread : threadList) {
        carThread->quit();
        carThread->wait();
    }
    close(); // 창을 닫습니다.
}


void MainWindow::updateCarPosition()
{
    for (int i = 0; i < carList.size(); ++i) {
            QGraphicsRectItem *carItem = carGraphics[i];
            carItem->setPos(carList[i]->getPosition(), i * 40+100); // y 좌표를 다르게 하여 자동차를 세로로 배치
        }
}
