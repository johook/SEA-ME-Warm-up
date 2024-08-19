#include "carthread.h"
#include <QMutexLocker>
#include <QDebug>

CarThread::CarThread(Car *car, RaceTrack *track, QMutex *mutex)
    : car(car), raceTrack(track), mutex(mutex) {}

void CarThread::run() {
    while (!isInterruptionRequested() && car->getPosition() < raceTrack->getFinishLine()) {
        QMutexLocker locker(mutex); // 잠금 시작 -> 특정자동차가 이동하는동안 다른자동차가 동시에 움직이지않도록 동기화
        car->move();
        locker.unlock(); // 잠금 해제
//        msleep(1); // 속도를 조절하는 부분

        // 만약 자동차가 결승선에 도달하면 스레드를 종료
        if (car->getPosition() >= raceTrack->getFinishLine()) {
            qDebug() << "Car" << car->getid() << "finished the race!";
            return;
        }
    }
}
